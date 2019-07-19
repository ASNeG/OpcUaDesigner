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

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeReferenceTypeTab.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	OpcUaAttributeReferenceTypeTab::OpcUaAttributeReferenceTypeTab(QWidget* parent)
	: QWidget()
	{
		QHBoxLayout* hBoxLayout;
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		QGridLayout* gridLayout = new QGridLayout();


		// InverseName
		QLabel* inverseNameLabel = new QLabel("InverseName");
		gridLayout->addWidget(inverseNameLabel, 0, 0, Qt::AlignTop);

		inverseNameLineEdit_ = new QLineEdit();
		inverseNameLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(inverseNameLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 0, 1);


		// Symmetric
		QLabel* symmetricLabel = new QLabel("Symmetric");
		gridLayout->addWidget(symmetricLabel, 1, 0, Qt::AlignTop);

		symmetricLineEdit_ = new QLineEdit();
		symmetricLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(symmetricLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);


		// UserWriteMask
		QLabel* userWriteMaskLabel = new QLabel("UserWriteMask");
		gridLayout->addWidget(userWriteMaskLabel, 2, 0, Qt::AlignTop);

		userWriteMaskLineEdit_ = new QLineEdit();
		userWriteMaskLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(userWriteMaskLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 2, 1);


		// WriteMask
		QLabel* writeMaskLabel = new QLabel("WriteMask");
		gridLayout->addWidget(writeMaskLabel, 3, 0, Qt::AlignTop);

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

	OpcUaAttributeReferenceTypeTab::~OpcUaAttributeReferenceTypeTab(void)
	{
	}

	void
	OpcUaAttributeReferenceTypeTab::nodeChange(NodeInfo* nodeInfo)
	{
		setInverseName(nodeInfo);
		setSymmetric(nodeInfo);
		setUserWriteMask(nodeInfo);
		setWriteMask(nodeInfo);
	}

	void
	OpcUaAttributeReferenceTypeTab::setInverseName(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullInverseName()) {
			inverseNameLineEdit_->setText(QString(""));
		}
		else {
			OpcUaLocalizedText inverseName;
			baseNode->getInverseName(inverseName);
			inverseNameLineEdit_->setText(inverseName.toString().c_str());
		}
	}

	void
	OpcUaAttributeReferenceTypeTab::setSymmetric(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullSymmetric()) {
			symmetricLineEdit_->setText(QString(""));
		}
		else {
			OpcUaBoolean symmetric;
			baseNode->getSymmetric(symmetric);
			symmetricLineEdit_->setText(symmetric == 1 ? QString("True") : QString("False"));
		}
	}

	void
	OpcUaAttributeReferenceTypeTab::setUserWriteMask(NodeInfo* nodeInfo)
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
	OpcUaAttributeReferenceTypeTab::setWriteMask(NodeInfo* nodeInfo)
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


