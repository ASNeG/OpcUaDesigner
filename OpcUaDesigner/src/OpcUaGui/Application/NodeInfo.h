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

#ifndef __OpcUaGui_NodeInfo_h__
#define __OpcUaGui_NodeInfo_h__

#include "OpcUaGui/Model/ApplicationData.h"
#include "OpcUaGui/Application/Modul.h"

namespace OpcUaGui
{

    class NodeInfo
    {
      public:
    	NodeInfo(void);
    	~NodeInfo(void);

    	void modulConfig(ModulConfig::SPtr& modulConfig);
    	ModulConfig::SPtr modulConfig(void);
    	void handle(uint32_t handle);
    	uint32_t handle(void);
    	void applicationData(ApplicationData::SPtr& applicationData);
    	ApplicationData::SPtr applicationData(void);

      private:
    	ModulConfig::SPtr modulConfig_;
    	uint32_t handle_;
    	ApplicationData::SPtr applicationData_;
    };

}

Q_DECLARE_METATYPE(OpcUaGui::NodeInfo*);

#endif
