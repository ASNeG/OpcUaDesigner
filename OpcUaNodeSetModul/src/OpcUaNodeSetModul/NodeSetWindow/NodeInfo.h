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

#ifndef __OpcUaNodeSetModul_NodeInfo_h__
#define __OpcUaNodeSetModul_NodeInfo_h__

#include <QMetaType>

#include "OpcUaStackServer/AddressSpaceModel/BaseNodeClass.h"
#include "OpcUaStackServer/InformationModel/InformationModel.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{

	class NodeInfo
	{
	  public:
		NodeInfo(void);
		~NodeInfo(void);

		BaseNodeClass::SPtr baseNode_;
		InformationModel::SPtr informationModel_;
	};

}

Q_DECLARE_METATYPE(OpcUaNodeSet::NodeInfo*);

#endif
