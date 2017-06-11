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

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeBaseTab.h"

#include <QLabel>
#include <QLineEdit>

namespace OpcUaNodeSet
{


	OpcUaAttributeBaseTab::OpcUaAttributeBaseTab(QWidget* parent)
	: QWidget()
	{
		QHBoxLayout* hBoxLayout;
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		QGridLayout* gridLayout = new QGridLayout();


		// NodeId
		QLabel* nodeIdLabel = new QLabel("NodeId");
		gridLayout->addWidget(nodeIdLabel, 0, 0);

		nodeIdWidget_ = new NodeIdWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(nodeIdWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 0, 1);


		// NodeClass
		QLabel* nodeClassLabel = new QLabel("NodeClass");
		gridLayout->addWidget(nodeClassLabel, 1, 0);

		nodeClassWidget_ = new NodeClassWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(nodeClassWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);


		// BrowseName
		QLabel* browseNameLabel = new QLabel("BrowseName");
		gridLayout->addWidget(browseNameLabel, 2, 0);

		browseNameWidget_ = new BrowseNameWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(browseNameWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 2, 1);


		// DisplayName
		QLabel* displayNameLabel = new QLabel("DisplayName");
		gridLayout->addWidget(displayNameLabel, 3, 0);

		displayNameWidget_ = new DisplayNameWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(displayNameWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 3, 1);


		// Description
		QLabel* descriptionLabel = new QLabel("Description");
		gridLayout->addWidget(descriptionLabel, 4, 0);

		descriptionWidget_ = new DescriptionWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(descriptionWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 4, 1);


		// WriteMask
		QLabel* writeMaskLabel = new QLabel("WriteMask");
		gridLayout->addWidget(writeMaskLabel, 5, 0);

		writeMaskLineEdit_ = new QLineEdit();
		writeMaskLineEdit_->setFixedWidth(400);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(writeMaskLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 5, 1);


		// UserWriteMask
		QLabel* userWriteMaskLabel = new QLabel("UserWriteMask");
		gridLayout->addWidget(userWriteMaskLabel, 6, 0);

		userWriteMaskLineEdit_ = new QLineEdit();
		userWriteMaskLineEdit_->setFixedWidth(400);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(userWriteMaskLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 6, 1);


		vBoxLayout->addLayout(gridLayout);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);
	}

	OpcUaAttributeBaseTab::~OpcUaAttributeBaseTab(void)
	{
	}

	void
	OpcUaAttributeBaseTab::nodeChange(NodeInfo* nodeInfo)
	{
		OpcUaNodeId nodeId;
		nodeInfo->baseNode_->getNodeId(nodeId);
		nodeIdWidget_->setValue(nodeInfo->nodeSetNamespace_);
		nodeIdWidget_->setValue(nodeId);

		nodeClassWidget_->nodeChange(nodeInfo);

		OpcUaQualifiedName browseName;
		nodeInfo->baseNode_->getBrowseName(browseName);
		browseNameWidget_->setValue(nodeInfo->nodeSetNamespace_);
		browseNameWidget_->setValue(browseName);

		displayNameWidget_->nodeChange(nodeInfo);

		descriptionWidget_->nodeChange(nodeInfo);

		setWriteMask(nodeInfo);

		setUserWriteMask(nodeInfo);
	}

	void
	OpcUaAttributeBaseTab::setWriteMask(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullWriteMask()) {
			writeMaskLineEdit_->setText(QString(""));
		}
		else {
			OpcUaUInt32 writeMask;
			baseNode->getUserWriteMask(writeMask);
			writeMaskLineEdit_->setText(QString("%1").arg((uint32_t)writeMask));
		}
	}

	void
	OpcUaAttributeBaseTab::setUserWriteMask(NodeInfo* nodeInfo)
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

}


