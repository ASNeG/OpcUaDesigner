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

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QVBoxLayout>

#include "OpcUaStackServer/AddressSpaceModel/DataTypeNodeClass.h"
#include "OpcUaStackServer/NodeSet/DataTypeDefinition.h"
#include "OpcUaNodeSetModul/NodeSetWindow/DataTypeEnumTable.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	DataTypeEnumTable::DataTypeEnumTable(QWidget* parent)
	: QWidget()
	{
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		enumTable_ = new QTableWidget();
		vBoxLayout->addWidget(enumTable_);

		QStringList headerLabels;
		headerLabels << "Name" << "Value";
		enumTable_->setHorizontalHeaderLabels(headerLabels);

		this->setLayout(vBoxLayout);
	}

	DataTypeEnumTable::~DataTypeEnumTable(void)
	{
	}

	void
	DataTypeEnumTable::nodeChange(NodeInfo* nodeInfo)
	{
		bool success;

		// clear table
		while (enumTable_->rowCount() > 0) {
			enumTable_->removeRow(0);
		}

#if 0
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
#endif
		enumTable_->resizeColumnsToContents();
	}

}


