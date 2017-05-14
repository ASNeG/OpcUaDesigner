/*
   Copyright 2016-2017 Kai Huebl (kai@huebl-sgh.de)

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
	, projectDataMap_()
	{
	}

	DataModel::~DataModel(void)
	{
	}

	std::string&
	DataModel::fileName(void)
	{
		return fileName_;
	}

	bool
	DataModel::existProjectData(const std::string& name)
	{
		ProjectData::Map::iterator it;
		it = projectDataMap_.find(name);
		if (it == projectDataMap_.end()) return false;
		return true;
	}

	bool
	DataModel::getProjectData(const std::string& name, ProjectData::SPtr& projectData)
	{
		ProjectData::Map::iterator it;
		it = projectDataMap_.find(name);
		if (it == projectDataMap_.end()) return false;
		projectData = it->second;
		return true;
	}

	bool
	DataModel::setProjectData(const std::string& name, ProjectData::SPtr& projectData)
	{
		ProjectData::Map::iterator it;
		it = projectDataMap_.find(name);
		if (it != projectDataMap_.end()) return false;
		projectDataMap_.insert(std::make_pair(name, projectData));
		return true;
	}

	void
	DataModel::getProjectNameVec(std::vector<std::string>& projectNameVec)
	{
		ProjectData::Map::iterator it;
		for (it = projectDataMap_.begin(); it != projectDataMap_.end(); it++) {
			projectNameVec.push_back(it->first);
		}
	}

	bool
	DataModel::create(const std::string& fileName)
	{
		fileName_ = fileName;
		projectDataMap_.clear();
		return true;
	}

	bool
	DataModel::open(const std::string& fileName)
	{
		fileName_ = fileName;

		// read project file
		Config config;
		ConfigXml configXml;
		if (!configXml.read(fileName)) {
			Log(Error, "read project file error")
				.parameter("FileName", fileName_)
				.parameter("ErrorMessage", configXml.errorMessage());
			return false;
		}
		config.child(configXml.ptree());

		// decode project configuration
		boost::optional<Config> cfg = config.getChild("OpcUaDesigner");
		if (!cfg) {
			Log(Error, "element missing in project file")
				.parameter("Element", "OpcUaDesigner")
				.parameter("FileName", fileName_);
			return false;
		}

		std::vector<Config>::iterator it;
		std::vector<Config> projectConfigVec;
		config.getChilds("OpcUaDesigner.Project", projectConfigVec);
		for (it = projectConfigVec.begin(); it != projectConfigVec.end(); it++) {
			ProjectData::SPtr projectData = constructSPtr<ProjectData>();
			if (!projectData->decode(*it)) {
				Log(Error, "decode project file error")
					.parameter("FileName", fileName_);
				return false;
			}
			setProjectData(projectData->projectName(), projectData);
		}

		return true;
	}

	bool
	DataModel::save(void)
	{
		Config config;

		// encode project configuration
		ProjectData::Map::iterator it;
		for (it = projectDataMap_.begin(); it != projectDataMap_.end(); it++) {
			ProjectData::SPtr projectData = it->second;
			Config projectDataConfig;

			 if (!projectData->encode(projectDataConfig)) {
				Log(Error, "decode project file error")
					.parameter("FileName", fileName_);
				return false;
			 }

			 config.addChild("OpcUaDesigner.Project", projectDataConfig);
		}

		// write data
		ConfigXml configXml;
		configXml.ptree(config.child());
		if (!configXml.write(fileName_)) {
			Log(Error, "write project file error")
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


