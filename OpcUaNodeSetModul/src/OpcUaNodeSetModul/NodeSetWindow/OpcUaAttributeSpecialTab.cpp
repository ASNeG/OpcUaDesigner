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
#include <QHBoxLayout>
#include <QGridLayout>

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeSpecialTab.h"

#include <QLabel>
#include <QLineEdit>

namespace OpcUaNodeSet
{


	OpcUaAttributeSpecialTab::OpcUaAttributeSpecialTab(QWidget* parent)
	: QWidget()
	{
		QHBoxLayout* hBoxLayout;
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		QGridLayout* gridLayout = new QGridLayout();


		// NodeId
		QLabel* nodeIdLabel = new QLabel("NodeId");
		gridLayout->addWidget(nodeIdLabel, 0, 0);


		vBoxLayout->addLayout(gridLayout);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);
	}

	OpcUaAttributeSpecialTab::~OpcUaAttributeSpecialTab(void)
	{
	}

	void
	OpcUaAttributeSpecialTab::nodeChange(NodeInfo* nodeInfo)
	{
	}

}


