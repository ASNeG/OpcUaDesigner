/*
   Copyright 2016-2019 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#include <boost/filesystem.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

#include "OpcUaGui/Application/Modul.h"
#include "OpcUaGui/Application/DynamicLibrary.h"

#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/Config.h"
#include "OpcUaStackCore/Base/ConfigXml.h"
#include "OpcUaStackCore/Utility/Environment.h"

using namespace OpcUaStackCore;

namespace OpcUaGui
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// ModulConfig
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	ModulConfig::ModulConfig(void)
	: dynamicLibrary_(new DynamicLibrary())
	, modulLibraryInterface_(NULL)
	, modulChilds_()
	, config_(NULL)
	{
	}

	ModulConfig::~ModulConfig(void)
	{
		delete dynamicLibrary_;
	}

	void
	ModulConfig::addChild(const std::string& modulName)
	{
		// check if the child modul already exist
		ModulChilds::iterator it;
		for (it = modulChilds_.begin(); it != modulChilds_.end(); it++) {
			if (*it == modulName) return;
		}

		// add child name to modul child list
		modulChilds_.push_back(modulName);
	}



	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// Modul
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	Modul::Modul(void)
	: QObject()
	, modulConfigMap_()
	, modulNames_()
	, modulDirectory_("")
	, mainWindow_(NULL)
	{
	}

	Modul::~Modul(void)
	{
	}

	bool
	Modul::startup(void)
	{
		if (!initModuls()) {
			return false;
		}

		// startup all moduls
		emit startupSignal();

		return true;
	}

	bool
	Modul::shutdown(void)
	{
		// shutdown all moduls
		emit shutdownSignal();

		return true;
	}

	void
	Modul::modulDirectory(const std::string& modulDirectory)
	{
		modulDirectory_ = modulDirectory;
	}

	void
	Modul::mainWindow(QMainWindow* mainWindow)
	{
		mainWindow_ = mainWindow;
	}

	QMainWindow*
	Modul::mainWindow(void)
	{
		return mainWindow_;
	}

	ModulConfig::Map&
	Modul::modulConfigMap(void)
	{
		return modulConfigMap_;
	}

	Modul::ModulNames&
	Modul::moduleNames(void)
	{
		return modulNames_;
	}

	ModulConfig::SPtr
	Modul::getModulConfig(const std::string& modulName)
	{
		ModulConfig::SPtr modulConfig;

		auto it = modulConfigMap_.find(modulName);
		if (it != modulConfigMap_.end()) {
			modulConfig = it->second;
		}
		return modulConfig;
	}

	bool
	Modul::initModuls(void)
	{
		// read modul configuration from modul directory
		if (!readModulConfig(modulDirectory_)) {
			return false;
		}

		// load moduls
		if (!loadModul()) {
			return false;
		}

		// added modul child dependencies into modul config
		addRootModul();
		if (!addModulChilds()) {
			return false;
		}

		return true;
	}

	bool
	Modul::readModulConfig(const std::string& modulDirectory)
	{
		// read all files in directory
		try {
		    boost::filesystem::directory_iterator endIt;
		    for (boost::filesystem::directory_iterator it(modulDirectory); it != endIt; it++) {
		    	auto modulConfigFileName = (*it).path().string();

		    	// parse modul configuration
		    	auto modulConfig = boost::make_shared<ModulConfig>();
		    	if (!parseModulConfig(modulConfigFileName, modulConfig)) {
		    		continue;
		    	}
		    	modulNames_.push_back(modulConfig->modulName_);
		    	modulConfigMap_.insert(std::make_pair(modulConfig->modulName_, modulConfig));
		    }
		}
		catch (...)
		{
			Log(Error, "modul configuration directory error")
				.parameter("ModulDirectory", modulDirectory);
			return false;
		}

		return true;
	}

	bool
	Modul::parseModulConfig(const std::string& modulConfigFileName, ModulConfig::SPtr& modulConfig)
	{
		Log(Info, "read modul config file")
			.parameter("ModulConfigFileName", modulConfigFileName);

		// parse configuration file
		auto config = Config::instance();
		modulConfig->config_ = config;
		ConfigXml configXml;
		if (!configXml.parse(modulConfigFileName, true)) {
			Log(Error, "parse modul config file error")
				.parameter("ModulConfigFileName", modulConfigFileName)
				.parameter("Reason", configXml.errorMessage());
			return false;
		}

		// read modul name
		if (!config->getConfigParameter("OpcUaModul.Name", modulConfig->modulName_)) {
			Log(Error, "parameter missing in modul config file")
				.parameter("ModulConfigFileName", modulConfigFileName)
				.parameter("Parameter", "OpcUaModul.Name");
			return false;
		}

		// read library name
		if (!config->getConfigParameter("OpcUaModul.Library", modulConfig->modulLibrary_)) {
			Log(Error, "parameter missing in modul config file")
				.parameter("ModulConfigFileName", modulConfigFileName)
				.parameter("Parameter", "OpcUaModul.Library");
			return false;
		}

		// read modul dependencies
		config->getValues("OpcUaModul.ModulParents.Modul", modulConfig->modulParents_);
		if (modulConfig->modulParents_.empty()) {
			Log(Error, "parameter missing in modul config file")
				.parameter("ModulConfigFileName", modulConfigFileName)
				.parameter("Parameter", "OpcUaModul.ModulParents.Modul");
			return false;
		}

		return true;
	}

	bool
	Modul::loadModul(void)
	{
		for (auto it = modulConfigMap_.begin(); it != modulConfigMap_.end(); it++) {
			auto modulConfig = it->second;
			auto dynamicLibrary = modulConfig->dynamicLibrary_;

			Log(Info, "open dynamic library")
				.parameter("ModulName", modulConfig->modulName_)
				.parameter("ModulLibrary", modulConfig->modulLibrary_);

			// load library
			if (!dynamicLibrary->open(modulConfig->modulName_)) {
				Log(Error, "open dynamic library error")
					.parameter("ModulName", modulConfig->modulName_)
					.parameter("ModulLibrary", modulConfig->modulLibrary_);
				continue;
			}

			// load init function
			typedef void InitFunction(OpcUaGui::ModulLibraryInterface**);
			InitFunction* initFunction;
			if (!dynamicLibrary->get("init", (void**)&initFunction)) {
				Log(Error, "get init function error")
					.parameter("ModulName", modulConfig->modulName_)
					.parameter("ModulLibrary", modulConfig->modulLibrary_);
				continue;
			}

			// call init function in library
			(*initFunction)(&modulConfig->modulLibraryInterface_);
			if (modulConfig->modulLibraryInterface_ == NULL) {
				Log(Error, "init function library error")
					.parameter("ModulName", modulConfig->modulName_)
					.parameter("ModulLibrary", modulConfig->modulLibrary_);
				return false;
			}

			// set values
			modulConfig->modulLibraryInterface_->parentMainWindow(mainWindow_);
			modulConfig->modulLibraryInterface_->config(modulConfig->config_);

			// connect startup and shutdown signals
			connect(
			    this, SIGNAL(startupSignal(void)),
			    modulConfig->modulLibraryInterface_, SLOT(startupSlot(void))
			);
			connect(
			    this, SIGNAL(shutdownSignal(void)),
			    modulConfig->modulLibraryInterface_, SLOT(shutdownSlot(void))
			);
		}

		return true;
	}

	void
	Modul::addRootModul(void)
	{
		auto modulConfig = constructSPtr<ModulConfig>();
		modulConfig->modulName_ = "Project";
		modulConfigMap_.insert(std::make_pair("Project", modulConfig));
	}

	bool
	Modul::addModulChilds(void)
	{
		// read all moduls
		for (auto it1 = modulConfigMap_.begin(); it1 != modulConfigMap_.end(); it1++) {
			auto modulConfig = it1->second;

			// read all parents names
			for (auto it2 = modulConfig->modulParents_.begin(); it2 != modulConfig->modulParents_.end(); it2++) {
				std::string modulParent = *it2;

				// find parent object
				auto it3 = modulConfigMap_.find(modulParent);
				if (it3 == modulConfigMap_.end()) {
					Log(Error, "library configuration for dependency modul name not exist")
						.parameter("ModulName", it1->first)
						.parameter("DependencyModulName", modulParent);
					return false;
				}
				auto modulConfigParent = it3->second;

				// insert child into parent object
				modulConfigParent->addChild(it1->first);
			}
		}

		return true;
	}

}

