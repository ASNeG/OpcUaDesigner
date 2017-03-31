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

#include "OpcUaStackServer/InformationModel/InformationModelAccess.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeChildTab.h"

#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	OpcUaAttributeChildTab::OpcUaAttributeChildTab(QWidget* parent)
	: QWidget()
	{
		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		// create table
		opcUaChildTable_ = new QTableWidget(0, 5);
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

		std::cout << "size=" << childBaseNodeClassVec.size() << std::endl;

		// fill table
		BaseNodeClass::Vec::iterator it;
		for (it = childBaseNodeClassVec.begin(); it != childBaseNodeClassVec.end(); it++) {
			uint32_t row = opcUaChildTable_->rowCount();
			opcUaChildTable_->insertRow(row);

			std::cout << "row=" << row << std::endl;

			for (uint32_t idx=0; idx<5; idx++) {
				QTableWidgetItem* item = new QTableWidgetItem("entry");
				opcUaChildTable_->setItem(row, idx, item);
			}
		}
	}

}


