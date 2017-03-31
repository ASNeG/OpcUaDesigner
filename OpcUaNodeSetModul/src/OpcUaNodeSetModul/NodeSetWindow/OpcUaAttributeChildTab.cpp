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

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeChildTab.h"

#include <QLabel>
#include <QTableWidget>

namespace OpcUaNodeSet
{


	OpcUaAttributeChildTab::OpcUaAttributeChildTab(QWidget* parent)
	: QWidget()
	{
		QVBoxLayout* vBoxLayout = new QVBoxLayout();


		// create table
		opcUaChildTable_ = new QTableWidget(4, 4);
		vBoxLayout->addWidget(opcUaChildTable_);

		QStringList headerLabels;
		headerLabels << "NodeClass" << "DisplayName" << "TypeDefinition" << "DataType";
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
		// FIXME: todo
	}

}


