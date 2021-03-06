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

#ifndef __OpcUaNodeSet_OpcUaAttributeChildTab_h__
#define __OpcUaNodeSet_OpcUaAttributeChildTab_h__

#include "OpcUaNodeSetModul/Base/NodeInfo.h"

#include <QWidget>

class QTableWidget;

namespace OpcUaNodeSet
{

	class OpcUaAttributeChildTab
	: public QWidget
	{
		Q_OBJECT

	  public:
		OpcUaAttributeChildTab(QWidget* parent = 0);
		virtual ~OpcUaAttributeChildTab(void);

		void nodeChange(NodeInfo* nodeInfo);

	  private:
		void setNodeClass(NodeInfo* nodeInfo, uint32_t row, OpcUaStackServer::BaseNodeClass::SPtr baseNode);
	    void setDisplayName(NodeInfo* nodeInfo, uint32_t row,  OpcUaStackServer::BaseNodeClass::SPtr baseNode);
	    void setTypeDefinition(NodeInfo* nodeInfo, uint32_t row,  OpcUaStackServer::BaseNodeClass::SPtr baseNode);
	    void setDataType(NodeInfo* nodeInfo, uint32_t row, OpcUaStackServer::BaseNodeClass::SPtr baseNode);
	    void setReference(NodeInfo* nodeInfo, uint32_t row, OpcUaStackServer::BaseNodeClass::SPtr baseNode);

		QTableWidget* opcUaChildTable_;
	};

}

#endif
