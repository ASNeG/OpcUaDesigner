/*
   Copyright 2017 Kai Huebl (kai@huebl-sgh.de)

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

#ifndef __OpcUaNodeSetModul_DataModel_h__
#define __OpcUaNodeSetModul_DataModel_h__

#include "OpcUaStackServer/InformationModel/InformationModel.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{

	class DataModel
	{
	  public:
		DataModel(void);
		~DataModel(void);

		InformationModel::SPtr& informationModel(void);
		bool loadStandardNodeSet(const std::string& standardNodeSetFileName);
		bool writeNodeSet(const std::string& nodeSetFile);

	  private:
		InformationModel::SPtr informationModel_;
	};

}

#endif
