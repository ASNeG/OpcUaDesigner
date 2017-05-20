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

#ifndef __OpcUaGui_ProjectData_h__
#define __OpcUaGui_ProjectData_h__

#include <boost/shared_ptr.hpp>
#include <string>
#include <map>
#include "OpcUaStackCore/Base/Config.h"

using namespace OpcUaStackCore;

namespace OpcUaGui
{
	class ProjectData
	{
	  public:
		typedef boost::shared_ptr<ProjectData> SPtr;
		typedef std::map<std::string, ProjectData::SPtr> Map;

		ProjectData(void);
		~ProjectData(void);

		void handle(uint32_t handle);
		uint32_t handle(void);
		void projectName(const std::string& projectName);
		std::string& projectName(void);
		void projectFile(const std::string& projectFile);
		std::string& projectFile(void);

		bool encode(Config& config);
		bool decode(Config& config);

	  private:
		uint32_t handle_;
		std::string projectName_;
		std::string projectFile_;
	};

}

#endif
