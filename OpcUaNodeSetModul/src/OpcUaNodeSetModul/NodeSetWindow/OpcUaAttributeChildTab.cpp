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


#include <QVBoxLayout>

#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackServer/InformationModel/InformationModelAccess.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeChildTab.h"

#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

using namespace OpcUaStackServer;
using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{


	OpcUaAttributeChildTab::OpcUaAttributeChildTab(QWidget* parent)
	: QWidget()
	{
		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		// create table
		opcUaChildTable_ = new QTableWidget(0, 5);
		opcUaChildTable_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		vBoxLayout->addWidget(opcUaChildTable_);

		QStringList headerLabels;
		headerLabels << "NodeClass" << "DisplayName" << "TypeDefinition" << "DataType" << "Reference";
		opcUaChildTable_->setHorizontalHeaderLabels(headerLabels);

		// show opc ua attriubute tab
		setLayout(vBoxLayout);
	}

	OpcUaAttributeChildTab::~OpcUaAttributeChildTab(void)
	{
	}

	void
	OpcUaAttributeChildTab::nodeChange(NodeInfo* nodeInfo)
	{
		bool success;

		// clear table
		while (opcUaChildTable_->rowCount() > 0) {
			opcUaChildTable_->removeRow(0);
		}

		// find childs
		BaseNodeClass::Vec childBaseNodeClassVec;
		InformationModelAccess ima(nodeInfo->informationModel_);
		success = ima.getChildHierarchically(nodeInfo->baseNode_, childBaseNodeClassVec);
		if (!success || childBaseNodeClassVec.size() == 0) {
			return;
		}

		// fill table
		BaseNodeClass::Vec::iterator it;
		for (it = childBaseNodeClassVec.begin(); it != childBaseNodeClassVec.end(); it++) {
			uint32_t row = opcUaChildTable_->rowCount();
			opcUaChildTable_->insertRow(row);

			setNodeClass(nodeInfo, row, *it);
			setDisplayName(nodeInfo, row, *it);
			setTypeDefinition(nodeInfo, row, *it);
			setDataType(nodeInfo, row, *it);
			setReference(nodeInfo, row, *it);
		}
		opcUaChildTable_->resizeColumnsToContents();
	}

	void
	OpcUaAttributeChildTab::setNodeClass(NodeInfo* nodeInfo, uint32_t row, BaseNodeClass::SPtr baseNode)
	{
		QTableWidgetItem* item = new QTableWidgetItem("");
		if (!baseNode->isNullNodeClass()) {
			NodeClassType nodeClass;
			baseNode->getNodeClass(nodeClass);
			item->setText(QString(NodeClass::toString(nodeClass).c_str()));
		}
		opcUaChildTable_->setItem(row, 0, item);
	}

    void
    OpcUaAttributeChildTab::setDisplayName(NodeInfo* nodeInfo, uint32_t row, BaseNodeClass::SPtr baseNode)
    {
    	QTableWidgetItem* item = new QTableWidgetItem("");
		if (!baseNode->isNullDisplayName()) {
			OpcUaLocalizedText displayName;
			baseNode->getDisplayName(displayName);
			item->setText(QString(displayName.toString().c_str()));
		}
		opcUaChildTable_->setItem(row, 1, item);
    }

    void
    OpcUaAttributeChildTab::setTypeDefinition(NodeInfo* nodeInfo, uint32_t row, BaseNodeClass::SPtr baseNode)
    {
    	bool success;

    	QTableWidgetItem* item = new QTableWidgetItem("");

    	// get type node id
    	OpcUaNodeId typeNodeId;
    	InformationModelAccess ima(nodeInfo->informationModel_);
    	success = ima.getType(baseNode, typeNodeId);
    	if (success) {
    		std::string typeNodeIdString = "";

    		if (typeNodeId.namespaceIndex() == 0 && typeNodeId.nodeIdType() == OpcUaBuildInType_OpcUaUInt32) {
    			uint32_t id = typeNodeId.nodeId<uint32_t>();
    			typeNodeIdString = OpcUaIdMap::shortString(id);
    		}

    		if (typeNodeIdString == "") {
    			item->setText(QString(typeNodeId.toString().c_str()));
    		}
    		else {
    			item->setText(QString(typeNodeIdString.c_str()));
    		}
    	}

    	opcUaChildTable_->setItem(row, 2, item);
    }

    void
    OpcUaAttributeChildTab::setDataType(NodeInfo* nodeInfo, uint32_t row, BaseNodeClass::SPtr baseNode)
    {
    	QTableWidgetItem* item = new QTableWidgetItem("");
    	opcUaChildTable_->setItem(row, 3, item);
    }

    void
    OpcUaAttributeChildTab::setReference(NodeInfo* nodeInfo, uint32_t row, BaseNodeClass::SPtr baseNode)
    {
    	QTableWidgetItem* item = new QTableWidgetItem("");
    	opcUaChildTable_->setItem(row, 4, item);
    }

}


