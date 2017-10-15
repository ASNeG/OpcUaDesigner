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
#include <QLabel>
#include <QLineEdit>

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeObjectTab.h"

namespace OpcUaNodeSet
{


	OpcUaAttributeObjectTab::OpcUaAttributeObjectTab(QWidget* parent)
	: QWidget()
	{
		QHBoxLayout* hBoxLayout;
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		QGridLayout* gridLayout = new QGridLayout();


		// EventNotifier
		QLabel* accessLevelLabel = new QLabel("EventNotifier");
		gridLayout->addWidget(accessLevelLabel, 0, 0);

		eventNotifierLineEdit_ = new QLineEdit();
		eventNotifierLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(eventNotifierLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 0, 1);


		vBoxLayout->addLayout(gridLayout);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);
	}

	OpcUaAttributeObjectTab::~OpcUaAttributeObjectTab(void)
	{
	}

	void
	OpcUaAttributeObjectTab::nodeChange(NodeInfo* nodeInfo)
	{
		setEventNotifier(nodeInfo);
	}

	void
	OpcUaAttributeObjectTab::setEventNotifier(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullEventNotifier()) {
			eventNotifierLineEdit_->setText(QString(""));
		}
		else {
			OpcUaByte eventNotifier;
			baseNode->getEventNotifier(eventNotifier);
			eventNotifierLineEdit_->setText(QString("%1").arg((uint32_t)eventNotifier));
		}
	}

}


