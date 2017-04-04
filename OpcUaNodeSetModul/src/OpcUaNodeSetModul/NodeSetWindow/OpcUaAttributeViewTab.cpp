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

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeViewTab.h"

namespace OpcUaNodeSet
{


	OpcUaAttributeViewTab::OpcUaAttributeViewTab(QWidget* parent)
	: QWidget()
	{
		QHBoxLayout* hBoxLayout;
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		QGridLayout* gridLayout = new QGridLayout();


		// ContainsNoLoops
		QLabel* containsNoLoopsLabel = new QLabel("ContainsNoLoops");
		gridLayout->addWidget(containsNoLoopsLabel, 0, 0);

		containsNoLoopsLineEdit_ = new QLineEdit();
		containsNoLoopsLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(containsNoLoopsLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 0, 1);


		// EventNotifier
		QLabel* eventNotifierLabel = new QLabel("EventNotifier");
		gridLayout->addWidget(eventNotifierLabel, 1, 0);

		eventNotifierLineEdit_ = new QLineEdit();
		eventNotifierLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(eventNotifierLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);


		// UserWriteMask
		QLabel* userWriteMaskLabel = new QLabel("UserWriteMask");
		gridLayout->addWidget(userWriteMaskLabel, 2, 0);

		userWriteMaskLineEdit_ = new QLineEdit();
		userWriteMaskLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(userWriteMaskLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 2, 1);


		// WriteMask
		QLabel* writeMaskLabel = new QLabel("WriteMask");
		gridLayout->addWidget(writeMaskLabel, 3, 0);

		writeMaskLineEdit_ = new QLineEdit();
		writeMaskLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(writeMaskLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 3, 1);


		vBoxLayout->addLayout(gridLayout);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);
	}

	OpcUaAttributeViewTab::~OpcUaAttributeViewTab(void)
	{
	}

	void
	OpcUaAttributeViewTab::nodeChange(NodeInfo* nodeInfo)
	{
		setContainsNoLoops(nodeInfo);
		setEventNotifier(nodeInfo);
		setUserWriteMask(nodeInfo);
		setWriteMask(nodeInfo);
	}

	void
	OpcUaAttributeViewTab::setContainsNoLoops(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullContainsNoLoops()) {
			containsNoLoopsLineEdit_->setText(QString(""));
		}
		else {
			OpcUaBoolean containsNoLoops;
			baseNode->getContainsNoLoops(containsNoLoops);
			containsNoLoopsLineEdit_->setText(containsNoLoops == 1 ? QString("True") : QString("False"));
		}
	}

	void
	OpcUaAttributeViewTab::setEventNotifier(NodeInfo* nodeInfo)
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

	void
	OpcUaAttributeViewTab::setUserWriteMask(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullUserWriteMask()) {
			userWriteMaskLineEdit_->setText(QString(""));
		}
		else {
			OpcUaUInt32 userWriteMask;
			baseNode->getUserWriteMask(userWriteMask);
			userWriteMaskLineEdit_->setText(QString("%1").arg((uint32_t)userWriteMask));
		}
	}

	void
	OpcUaAttributeViewTab::setWriteMask(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullWriteMask()) {
			writeMaskLineEdit_->setText(QString(""));
		}
		else {
			OpcUaUInt32 writeMask;
			baseNode->getWriteMask(writeMask);
			writeMaskLineEdit_->setText(QString("%1").arg((uint32_t)writeMask));
		}
	}

}


