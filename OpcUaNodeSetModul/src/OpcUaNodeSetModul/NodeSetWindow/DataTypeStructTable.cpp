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
#include <QString>
#include <QLabel>

#include "OpcUaStackServer/AddressSpaceModel/DataTypeNodeClass.h"
#include "OpcUaStackServer/NodeSet/DataTypeDefinition.h"
#include "OpcUaNodeSetModul/NodeSetWindow/DataTypeStructTable.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{

	DataTypeStructTable::DataTypeStructTable(QWidget* parent)
	: QWidget()
	{
		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		QLabel* structLabel = new QLabel("Structure:");
		vBoxLayout->addWidget(structLabel);

		structTable_ = new QTableWidget(0,1);
		structTable_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		vBoxLayout->addWidget(structTable_);

		QStringList headerLabels;
		headerLabels << "Name";
		structTable_->setHorizontalHeaderLabels(headerLabels);

		vBoxLayout->setMargin(0);
		this->setLayout(vBoxLayout);
	}

	DataTypeStructTable::~DataTypeStructTable(void)
	{
	}

	void
	DataTypeStructTable::nodeChange(NodeInfo* nodeInfo)
	{
		bool success;

		// clear table
		while (structTable_->rowCount() > 0) {
			structTable_->removeRow(0);
		}

		// get definition from data type node class
		DataTypeNodeClass::SPtr dataTypeNode = boost::static_pointer_cast<DataTypeNodeClass>(nodeInfo->baseNode_);
		Object::SPtr definitionObject = dataTypeNode->dataTypeDefinition();
		DataTypeDefinition::SPtr definition = boost::static_pointer_cast<DataTypeDefinition>(definitionObject);

		DataTypeField::Vec dataTypeFieldVec = definition->dataFields();
		for (uint32_t idx = 0; idx < dataTypeFieldVec.size(); idx++) {
			QTableWidgetItem* item;
			DataTypeField::SPtr dataField = dataTypeFieldVec[idx];

			uint32_t row = structTable_->rowCount();
			structTable_->insertRow(row);

			item = new QTableWidgetItem();
			item->setText(dataField->name().value().c_str());
			structTable_->setItem(row, 0, item);

			//item = new QTableWidgetItem();
			//item->setText(QString("%1").arg(dataField->value()));
			//enumTable_->setItem(row, 1, item);
		}

		structTable_->resizeColumnsToContents();
	}

}


