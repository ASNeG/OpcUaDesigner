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

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QString>
#include <QLabel>

#include "OpcUaStackCore/StandardDataTypes/EnumDefinitionExpand.h"
#include "OpcUaStackServer/AddressSpaceModel/DataTypeNodeClass.h"
#include "OpcUaNodeSetModul/NodeSetWindow/DataTypeEnumTable.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	DataTypeEnumTable::DataTypeEnumTable(QWidget* parent)
	: QWidget()
	{
		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		QLabel* enumLabel = new QLabel("Enumeration:");
		vBoxLayout->addWidget(enumLabel);

		enumTable_ = new QTableWidget(0,2);
		enumTable_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		vBoxLayout->addWidget(enumTable_);

		QStringList headerLabels;
		headerLabels << "Name" << "Value";
		enumTable_->setHorizontalHeaderLabels(headerLabels);

		vBoxLayout->setMargin(0);
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

		// get definition from data type node class
		auto dataTypeNode = boost::static_pointer_cast<DataTypeNodeClass>(nodeInfo->baseNode_);
		auto definitionObject = dataTypeNode->dataTypeDefinition();
		auto definition = boost::static_pointer_cast<EnumDefinitionExpand>(definitionObject);

		auto enumFieldArray = definition->enumFields();
		for (uint32_t idx = 0; idx < enumFieldArray->size(); idx++) {
			EnumField::SPtr enumField;
			enumFieldArray->get(idx, enumField);
			uint32_t row = enumTable_->rowCount();
			enumTable_->insertRow(row);

			setName(row, enumField);
			setValue(row, enumField);
		}

		enumTable_->resizeColumnsToContents();
	}

	void
	DataTypeEnumTable::enabled(bool enabled)
	{
		enumTable_->setEnabled(enabled);
	}

	void
	DataTypeEnumTable::setName(uint32_t row, EnumField::SPtr& enumField)
	{
		QTableWidgetItem* item;
		item = new QTableWidgetItem();
		item->setText(enumField->name().value().c_str());
		enumTable_->setItem(row, 0, item);
	}

	void
	DataTypeEnumTable::setValue(uint32_t row, EnumField::SPtr& enumField)
	{
		QTableWidgetItem* item;
		item = new QTableWidgetItem();
		item->setText(QString("%1").arg(enumField->value()));
		enumTable_->setItem(row, 1, item);
	}

}


