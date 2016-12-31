/*
   Copyright 2016 Kai Huebl (kai@huebl-sgh.de)

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
#include <iostream>

#include "OpcUaGui/Application/Modul.h"

#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/Config.h"
#include "OpcUaStackCore/Base/ConfigXml.h"
#include "OpcUaStackCore/Utility/Environment.h"

using namespace OpcUaStackCore;

namespace OpcUaGui
{

	Modul::Modul(void)
	: modulConfigSet_()
	{
	}

	Modul::~Modul(void)
	{
	}

	ModulConfig::Set&
	Modul::modulConfigSet(void)
	{
		return modulConfigSet_;
	}

	bool
	Modul::initModuls(const std::string& modulDirectory)
	{
		// read modul configuration from modul directory
		if (!readModulConfig(modulDirectory)) {
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
		    	std::string modulConfigFileName = (*it).path().string();

		    	// parse modul configuration
		    	ModulConfig::SPtr modulConfig = constructSPtr<ModulConfig>();
		    	if (parseModulConfig(modulConfigFileName, modulConfig)) {
		    		continue;
		    	}
		    	modulConfigSet_.insert(modulConfig);
		    }
		}
		catch (...)
		{
			Log(Error, "modul configuration directory error")
				.parameter("ModulDirectory", modulDirectory);
			return false;
		}
	}

	bool
	Modul::parseModulConfig(const std::string& modulConfigFileName, ModulConfig::SPtr& modulConfig)
	{
		Log(Info, "read modul config file")
			.parameter("ModulConfigFileName", modulConfigFileName);

		// parse configuration file
		Config* config = Config::instance();
		config->alias("@CONF_DIR@", Environment::confDir());
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

		return true;
	}

}

