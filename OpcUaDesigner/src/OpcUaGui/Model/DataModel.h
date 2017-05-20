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

#ifndef __OpcUaGui_DataModel_h__
#define __OpcUaGui_DataModel_h__

#include "OpcUaGui/Model/ProjectData.h"

namespace OpcUaGui
{
	class DataModel
	{
	  public:
		DataModel(void);
		~DataModel(void);

		void clear(void);
		std::string& fileName(void);
		bool existProjectData(const std::string& name);
		bool getProjectData(const std::string& name, ProjectData::SPtr& projectData);
		bool setProjectData(const std::string& name, ProjectData::SPtr& projectData);
		bool delProjectData(const std::string& name);
		void getProjectNameVec(std::vector<std::string>& projectNameVec);

		bool create(const std::string& fileName);
		bool open(const std::string& fileName);
		bool save(void);
		bool saveAs(const std::string& fileName);

	  private:
		std::string fileName_;
		ProjectData::Map projectDataMap_;
	};

}

#endif
