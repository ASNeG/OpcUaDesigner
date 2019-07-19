/*
   Copyright 2017-2019 Kai Huebl (kai@huebl-sgh.de)

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
#include "OpcUaStackServer/NodeSet/NodeSetNamespace.h"


namespace OpcUaNodeSet
{

	class NodeInfo
	{
	  public:
		NodeInfo(void);
		~NodeInfo(void);

		OpcUaStackServer::BaseNodeClass::SPtr baseNode_;
		OpcUaStackServer::InformationModel::SPtr informationModel_;
		OpcUaStackServer::NodeSetNamespace nodeSetNamespace_;
	};

}

Q_DECLARE_METATYPE(OpcUaNodeSet::NodeInfo*);

#endif
