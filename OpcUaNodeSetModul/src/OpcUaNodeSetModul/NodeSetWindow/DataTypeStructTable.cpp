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

#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackCore/StandardDataTypes/StructureDefinitionExpand.h"
#include "OpcUaStackServer/AddressSpaceModel/DataTypeNodeClass.h"
#include "OpcUaNodeSetModul/NodeSetWindow/DataTypeStructTable.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{

	DataTypeStructTable::DataTypeStructTable(QWidget* parent)
	: QWidget()
	{
		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		QLabel* structLabel = new QLabel("Structure:");
		vBoxLayout->addWidget(structLabel);

		structTable_ = new QTableWidget(0,5);
		structTable_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		vBoxLayout->addWidget(structTable_);

		QStringList headerLabels;
		headerLabels << "Name" << "DataType" << "ValueRank" << "Description" << "Optional";
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
		auto dataTypeNode = boost::static_pointer_cast<DataTypeNodeClass>(nodeInfo->baseNode_);
		auto definitionObject = dataTypeNode->dataTypeDefinition();
		auto definition = boost::static_pointer_cast<StructureDefinitionExpand>(definitionObject);

		auto structureFieldArray = definition->fields();
		for (uint32_t idx = 0; idx < structureFieldArray->size(); idx++) {
			QTableWidgetItem* item;
			StructureField::SPtr structureField;
			structureFieldArray->get(idx, structureField);

			uint32_t row = structTable_->rowCount();
			structTable_->insertRow(row);

			setName(row, structureField);
			setDataType(row, structureField);
			setValueRank(row, structureField);
			setDescription(row, structureField);
			setIsOptional(row, structureField);
		}

		structTable_->resizeColumnsToContents();
	}

	void
	DataTypeStructTable::enabled(bool enabled)
	{
		structTable_->setEnabled(enabled);
	}

	void
	DataTypeStructTable::setName(uint32_t row, StructureField::SPtr& structureField)
	{
		QTableWidgetItem* item;
		item = new QTableWidgetItem();
		item->setText(structureField->name().value().c_str());
		structTable_->setItem(row, 0, item);
	}

	void
	DataTypeStructTable::setDataType(uint32_t row, StructureField::SPtr& structureField)
	{
		std::string dataTypeString = "";
    	OpcUaNodeId dataType = structureField->dataType();

    	if (dataType.namespaceIndex() == 0 &&  dataType.nodeIdType() == OpcUaBuildInType_OpcUaUInt32) {
    		uint32_t id = dataType.nodeId<uint32_t>();
    		dataTypeString = OpcUaIdMap::shortString(id);
    	}
    	else {
    		dataTypeString = dataType.toString();
    	}

		QTableWidgetItem* item;
		item = new QTableWidgetItem();
		item->setText(dataTypeString.c_str());
		structTable_->setItem(row, 1, item);
	}

	void
	DataTypeStructTable::setValueRank(uint32_t row, StructureField::SPtr& structureField)
	{
		int32_t valueRank = structureField->valueRank();

		QTableWidgetItem* item;
		item = new QTableWidgetItem();
		item->setText(QString("%1").arg((int32_t)valueRank));
		structTable_->setItem(row, 2, item);
	}

	void
	DataTypeStructTable::setDescription(uint32_t row, StructureField::SPtr& structureField)
	{
		QTableWidgetItem* item;
		item = new QTableWidgetItem();
		item->setText(structureField->description().text().value().c_str());
		structTable_->setItem(row, 3, item);
	}

	void
	DataTypeStructTable::setIsOptional(uint32_t row, StructureField::SPtr& structureField)
	{
		QTableWidgetItem* item;
		item = new QTableWidgetItem();
		item->setText(structureField->isOptional() == true ? QString("Yes") : QString("No"));
		structTable_->setItem(row, 4, item);
	}

}


