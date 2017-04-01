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
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeRefTab.h"

#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>

namespace OpcUaNodeSet
{


	OpcUaAttributeRefTab::OpcUaAttributeRefTab(QWidget* parent)
	: QWidget()
	{
		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		// create table
		opcUaRefTable_ = new QTableWidget(0, 5);
		opcUaRefTable_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		vBoxLayout->addWidget(opcUaRefTable_);

		QStringList headerLabels;
		headerLabels << "NodeClass" << "DisplayName" << "TypeDefinition" << "DataType" << "Reference";
		opcUaRefTable_->setHorizontalHeaderLabels(headerLabels);

		// show opc ua attriubute tab
		setLayout(vBoxLayout);
	}

	OpcUaAttributeRefTab::~OpcUaAttributeRefTab(void)
	{
	}

	void
	OpcUaAttributeRefTab::nodeChange(NodeInfo* nodeInfo)
	{
		bool success;

		// clear table
		while (opcUaRefTable_->rowCount() > 0) {
			opcUaRefTable_->removeRow(0);
		}

		// find references
		BaseNodeClass::Vec childBaseNodeClassVec;
		InformationModelAccess ima(nodeInfo->informationModel_);
		success = ima.getChildNonHierarchically(
			nodeInfo->baseNode_,
			childBaseNodeClassVec
		);
		if (!success || childBaseNodeClassVec.size() == 0) {
			return;
		}

		// fill table
		for (uint32_t idx = 0; idx < childBaseNodeClassVec.size(); idx++) {
			BaseNodeClass::SPtr baseNodeChild = childBaseNodeClassVec[idx];

			uint32_t row = opcUaRefTable_->rowCount();
			opcUaRefTable_->insertRow(row);

			setNodeClass(nodeInfo, row, baseNodeChild);
			setDisplayName(nodeInfo, row, baseNodeChild);
			setTypeDefinition(nodeInfo, row, baseNodeChild);
			setDataType(nodeInfo, row, baseNodeChild);
			setReference(nodeInfo, row, baseNodeChild);
		}
		opcUaRefTable_->resizeColumnsToContents();
	}

	void
	OpcUaAttributeRefTab::setNodeClass(NodeInfo* nodeInfo, uint32_t row, BaseNodeClass::SPtr baseNode)
	{
		QTableWidgetItem* item = new QTableWidgetItem("");
		if (!baseNode->isNullNodeClass()) {
			NodeClassType nodeClass;
			baseNode->getNodeClass(nodeClass);
			item->setText(QString(NodeClass::toString(nodeClass).c_str()));
		}
		opcUaRefTable_->setItem(row, 0, item);
	}

    void
    OpcUaAttributeRefTab::setDisplayName(NodeInfo* nodeInfo, uint32_t row, BaseNodeClass::SPtr baseNode)
    {
    	QTableWidgetItem* item = new QTableWidgetItem("");
		if (!baseNode->isNullDisplayName()) {
			OpcUaLocalizedText displayName;
			baseNode->getDisplayName(displayName);
			item->setText(QString(displayName.toString().c_str()));
		}
		opcUaRefTable_->setItem(row, 1, item);
    }

    void
    OpcUaAttributeRefTab::setTypeDefinition(NodeInfo* nodeInfo, uint32_t row, BaseNodeClass::SPtr baseNode)
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

    	opcUaRefTable_->setItem(row, 2, item);
    }

    void
    OpcUaAttributeRefTab::setDataType(NodeInfo* nodeInfo, uint32_t row, BaseNodeClass::SPtr baseNode)
    {
    	bool success;
    	QTableWidgetItem* item = new QTableWidgetItem("");

    	// get data type
    	if (!baseNode->isNullDataType()) {
    		std::string dataTypeString = "";

    		OpcUaNodeId dataType;
    		success = baseNode->getDataType(dataType);
    		if (success) {

    			if (dataType.namespaceIndex() == 0 &&  dataType.nodeIdType() == OpcUaBuildInType_OpcUaUInt32) {
    				uint32_t id = dataType.nodeId<uint32_t>();
    				dataTypeString = OpcUaIdMap::shortString(id);
    			}
    			else {
    				dataTypeString = dataType.toString();
    			}
    		}

    		item->setText(QString(dataTypeString.c_str()));
    	}

    	opcUaRefTable_->setItem(row, 3, item);
    }

    void
    OpcUaAttributeRefTab::setReference(
    	NodeInfo* nodeInfo,
    	uint32_t row,
    	BaseNodeClass::SPtr baseNode
    )
    {
    	bool success;

    	// bool getParentReference(BaseNodeClass::SPtr baseNodeClass, std::vector<OpcUaNodeId>& referenceTypeNodeIdVec, ReferenceItem::Vec& referenceItemVec);
    	QTableWidgetItem* item = new QTableWidgetItem("");

    	// get reference type
    	std::string typeNodeIdString = "";
		BaseNodeClass::Vec childBaseNodeClassVec;
		InformationModelAccess ima(nodeInfo->informationModel_);
		std::vector<OpcUaNodeId> referenceTypeNodeIdVec;
		ReferenceItem::Vec referenceItemVec;
		success = ima.getParentReference(
			baseNode,
			referenceTypeNodeIdVec,
			referenceItemVec
		);

		if (success && referenceTypeNodeIdVec.size() > 0) {
		    ReferenceType referenceType = ReferenceTypeMap::nodeIdToReferenceType(referenceTypeNodeIdVec[0]);
		    if (referenceType != ReferenceType_Unknown) {
		        typeNodeIdString = ReferenceTypeMap::typeToString(referenceType);
		    }
		    else {
		    	typeNodeIdString = referenceTypeNodeIdVec[0].toString();
		    }

		}
        item->setText(QString(typeNodeIdString.c_str()));


    	opcUaRefTable_->setItem(row, 4, item);
    }

}


