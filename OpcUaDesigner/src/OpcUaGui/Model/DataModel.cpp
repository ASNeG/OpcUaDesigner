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

#include "OpcUaGui/Model/DataModel.h"

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
		// FIXME: todo
		return true;
	}

	bool
	DataModel::open(const std::string& fileName)
	{
		// FIXME: todo
		return true;
	}

	bool
	DataModel::save(void)
	{
		// FIXME: todo
		return true;
	}

	bool
	DataModel::saveAs(const std::string& fileName)
	{
		// FIXME: todo
		return true;
	}

}


