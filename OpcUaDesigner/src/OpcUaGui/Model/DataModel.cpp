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

#include <boost/make_shared.hpp>
#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaStackCore/Base/Config.h"
#include "OpcUaStackCore/Base/ConfigXml.h"
#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaGui/Model/DataModel.h"

using namespace OpcUaStackCore;

namespace OpcUaGui
{

	DataModel::DataModel(void)
	: fileName_("")
	, applicationDataMap_()
	{
	}

	DataModel::~DataModel(void)
	{
	}

	void
	DataModel::clear(void)
	{
		fileName_ = "";
		applicationDataMap_.clear();
	}

	std::string&
	DataModel::fileName(void)
	{
		return fileName_;
	}

	bool
	DataModel::existApplicationData(const std::string& name)
	{
		auto it = applicationDataMap_.find(name);
		if (it == applicationDataMap_.end()) return false;
		return true;
	}

	bool
	DataModel::getApplicationData(const std::string& name, ApplicationData::SPtr& applicationData)
	{
		auto it = applicationDataMap_.find(name);
		if (it == applicationDataMap_.end()) return false;
		applicationData = it->second;
		return true;
	}

	bool
	DataModel::setApplicationData(const std::string& name, ApplicationData::SPtr& applicationData)
	{
		auto it = applicationDataMap_.find(name);
		if (it != applicationDataMap_.end()) return false;
		applicationDataMap_.insert(std::make_pair(name, applicationData));
		return true;
	}

	bool
	DataModel::delApplicationData(const std::string& name)
	{
		auto it = applicationDataMap_.find(name);
		if (it == applicationDataMap_.end()) return false;
		applicationDataMap_.erase(it);
		return true;
	}

	void
	DataModel::getApplicationNameVec(std::vector<std::string>& applicationNameVec)
	{
		for (auto it = applicationDataMap_.begin(); it != applicationDataMap_.end(); it++) {
			applicationNameVec.push_back(it->first);
		}
	}

	bool
	DataModel::create(const std::string& fileName)
	{
		fileName_ = fileName;
		applicationDataMap_.clear();
		return true;
	}

	bool
	DataModel::open(const std::string& fileName)
	{
		fileName_ = fileName;

		// read application file
		Config config;
		ConfigXml configXml;
		if (!configXml.read(fileName)) {
			Log(Error, "read application file error")
				.parameter("FileName", fileName_)
				.parameter("ErrorMessage", configXml.errorMessage());
			return false;
		}
		config.child(configXml.ptree());

		// decode project configuration
		boost::optional<Config> cfg = config.getChild("OpcUaDesigner");
		if (!cfg) {
			Log(Error, "element missing in application file")
				.parameter("Element", "OpcUaDesigner")
				.parameter("FileName", fileName_);
			return false;
		}

		std::vector<Config> projectConfigVec;
		config.getChilds("OpcUaDesigner.Application", projectConfigVec);
		for (auto it = projectConfigVec.begin(); it != projectConfigVec.end(); it++) {
			auto applicationData = boost::make_shared<ApplicationData>();
			if (!applicationData->decode(*it)) {
				Log(Error, "decode application file error")
					.parameter("FileName", fileName_);
				return false;
			}
			setApplicationData(applicationData->applicationName(), applicationData);
		}

		return true;
	}

	bool
	DataModel::save(void)
	{
		Config tmpConfig;
		Config config;

		config.addChild("OpcUaDesigner", tmpConfig);

		// encode project configuration
		for (auto it = applicationDataMap_.begin(); it != applicationDataMap_.end(); it++) {
			auto applicationData = it->second;
			Config applicationDataConfig;

			 if (!applicationData->encode(applicationDataConfig)) {
				Log(Error, "decode application file error")
					.parameter("FileName", fileName_);
				return false;
			 }

			 config.addChild("OpcUaDesigner.Application", applicationDataConfig);
		}

		// write data
		ConfigXml configXml;
		configXml.ptree(config.child());
		if (!configXml.write(fileName_)) {
			Log(Error, "write application file error")
				.parameter("FileName", fileName_)
				.parameter("ErrorMessage", configXml.errorMessage());
			return false;
		}

		return true;
	}

	bool
	DataModel::saveAs(const std::string& fileName)
	{
		std::string oldFileName = fileName_;
		fileName_ = fileName;
		if (!save()) {
			fileName_ = oldFileName;
			return false;
		}
		return true;
	}

}


