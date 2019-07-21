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
#include <QHBoxLayout>
#include <QGridLayout>

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeBaseTab.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QToolBar>
#include <QMenu>

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	OpcUaAttributeBaseTab::OpcUaAttributeBaseTab(QWidget* parent)
	: QWidget()
	, nodeInfo_(nullptr)
	{
		QHBoxLayout* hBoxLayout;
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		QGridLayout* gridLayout = new QGridLayout();

		// create toolbar menu
		createToolBarActions();
		tableToolBar_ = new QToolBar();
		tableToolBar_->addAction(orderOkAction_);
		tableToolBar_->addAction(orderDeleteAction_);
		vBoxLayout->addWidget(tableToolBar_);


		// NodeClass
		QLabel* nodeClassLabel = new QLabel("NodeClass");
		gridLayout->addWidget(nodeClassLabel, 0, 0, Qt::AlignTop);

		nodeClassWidget_ = new NodeClassWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(nodeClassWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 0, 1);


		// NodeId
		QLabel* nodeIdLabel = new QLabel("NodeId");
		gridLayout->addWidget(nodeIdLabel, 1, 0, Qt::AlignTop);

		nodeIdWidget_ = new NodeIdWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(nodeIdWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);


		// BrowseName
		QLabel* browseNameLabel = new QLabel("BrowseName");
		gridLayout->addWidget(browseNameLabel, 2, 0, Qt::AlignTop);

		browseNameWidget_ = new BrowseNameWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(browseNameWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 2, 1);


		// DisplayName
		QLabel* displayNameLabel = new QLabel("DisplayName");
		gridLayout->addWidget(displayNameLabel, 3, 0, Qt::AlignTop);

		displayNameWidget_ = new DisplayNameWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(displayNameWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 3, 1);


		// Description
		QLabel* descriptionLabel = new QLabel("Description");
		gridLayout->addWidget(descriptionLabel, 4, 0, Qt::AlignTop);

		descriptionWidget_ = new DescriptionWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(descriptionWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 4, 1);


		// WriteMask
		QLabel* writeMaskLabel = new QLabel("WriteMask");
		gridLayout->addWidget(writeMaskLabel, 5, 0, Qt::AlignTop);

		writeMaskWidget_ = new WriteMaskWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(writeMaskWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 5, 1);


		// UserWriteMask
		QLabel* userWriteMaskLabel = new QLabel("UserWriteMask");
		gridLayout->addWidget(userWriteMaskLabel, 6, 0, Qt::AlignTop);

		userWriteMaskWidget_ = new UserWriteMaskWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(userWriteMaskWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 6, 1);

		vBoxLayout->addLayout(gridLayout);

		vBoxLayout->addStretch();

		setLayout(vBoxLayout);

		//
		// actions
		//
		connect(nodeIdWidget_, SIGNAL(update()), this, SLOT(update()));
		connect(browseNameWidget_, SIGNAL(update()), this, SLOT(update()));
		connect(displayNameWidget_, SIGNAL(update()), this, SLOT(update()));
		connect(descriptionWidget_, SIGNAL(update()), this, SLOT(update()));
		connect(writeMaskWidget_, SIGNAL(update()), this, SLOT(update()));
		connect(userWriteMaskWidget_, SIGNAL(update()), this, SLOT(update()));
	}

	OpcUaAttributeBaseTab::~OpcUaAttributeBaseTab(void)
	{
	}

	void
	OpcUaAttributeBaseTab::nodeChange(NodeInfo* nodeInfo)
	{
		bool enabled = true;

		nodeInfo_ = nodeInfo;

		NodeClass::Enum nodeClassType;
		nodeInfo->baseNode_->getNodeClass(nodeClassType);
		nodeClassWidget_->setValue(nodeClassType);
		nodeClassWidget_->enabled(false);

		OpcUaNodeId nodeId;
		nodeInfo->baseNode_->getNodeId(nodeId);
		if (nodeId.namespaceIndex() == 0) {
			enabled = false;
		}
		nodeIdWidget_->setValue(nodeInfo->nodeSetNamespace_);
		nodeIdWidget_->setValue(nodeId);
		nodeIdWidget_->enabled(enabled);

		OpcUaQualifiedName browseName;
		nodeInfo->baseNode_->getBrowseName(browseName);
		browseNameWidget_->setValue(nodeInfo->nodeSetNamespace_);
		browseNameWidget_->setValue(browseName);
		browseNameWidget_->enabled(enabled);

		OpcUaLocalizedText displayName;
		nodeInfo->baseNode_->getDisplayName(displayName);
		displayNameWidget_->setValue(displayName);
		displayNameWidget_->enabled(enabled);

		descriptionWidget_->nodeChange(nodeInfo);
		descriptionWidget_->enabled(enabled);

		writeMaskWidget_->nodeChange(nodeInfo);
		writeMaskWidget_->enabled(enabled);

		userWriteMaskWidget_->nodeChange(nodeInfo);
		userWriteMaskWidget_->enabled(enabled);

		orderOkAction_->setEnabled(false);
		orderDeleteAction_->setEnabled(false);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// Toolbar
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	OpcUaAttributeBaseTab::createToolBarActions(void)
	{
		orderOkAction_ = new QAction("Apply tab input", this);
		orderOkAction_->setIcon(QIcon(":images/OrderOk.png"));
		orderOkAction_->setEnabled(false);
		connect(orderOkAction_, SIGNAL(triggered()), this, SLOT(onOrderOkAction()));

		orderDeleteAction_ = new QAction("Cancel tab input", this);
		orderDeleteAction_->setIcon(QIcon(":images/OrderDelete.png"));
		orderDeleteAction_->setEnabled(false);
		connect(orderDeleteAction_, SIGNAL(triggered()), this, SLOT(onOrderDeleteAction()));
	}

    void
	OpcUaAttributeBaseTab::onOrderOkAction(void)
    {
    	InformationModel::SPtr informationModel_ = nodeInfo_->informationModel_;
    	BaseNodeClass::SPtr baseNode = nodeInfo_->baseNode_;

    	// check node id
    	OpcUaNodeId nodeId;
    	baseNode->getNodeId(nodeId);

    	OpcUaNodeId newNodeId;
    	nodeIdWidget_->getValue(newNodeId);

    	if (nodeId != newNodeId) {
    		informationModel_->remove(nodeId);
    		baseNode->setNodeId(newNodeId);
    		informationModel_->insert(baseNode);
    	}

    	// check display name
    	OpcUaLocalizedText displayName;
    	baseNode->getDisplayNameSync(displayName);

    	OpcUaLocalizedText newDisplayName;
    	displayNameWidget_->getValue(newDisplayName);

    	if (displayName != newDisplayName) {
    		baseNode->setDisplayNameSync(newDisplayName);
    	}

    	// check browse name
    	OpcUaQualifiedName browseName;
    	baseNode->getBrowseName(browseName);

    	OpcUaQualifiedName newBrowseName;
    	browseNameWidget_->getValue(newBrowseName);

    	if (browseName != newBrowseName) {
    		baseNode->setBrowseNameSync(newBrowseName);
    	}

    	// check description
    	OpcUaLocalizedText description;
    	baseNode->getDescription(description);

    	OpcUaLocalizedText newDescription;
    	descriptionWidget_->getValue(newDescription);

    	if (description != newDescription) {
    		baseNode->setDescription(newDescription);
    	}

    	// check write mask
    	OpcUaUInt32 writeMask;
    	baseNode->getWriteMask(writeMask);

    	OpcUaUInt32 newWriteMask;
    	writeMaskWidget_->getValue(newWriteMask);

    	if (writeMask != newWriteMask) {
    		baseNode->setWriteMask(newWriteMask);
    	}

    	// check user write mask
    	OpcUaUInt32 userWriteMask;
    	baseNode->getUserWriteMaskSync(userWriteMask);

    	OpcUaUInt32 newUserWriteMask;
    	userWriteMaskWidget_->getValue(newUserWriteMask);

    	if (userWriteMask != newUserWriteMask) {
    		baseNode->setUserWriteMask(newUserWriteMask);
    	}

    	orderOkAction_->setEnabled(false);
    	orderDeleteAction_->setEnabled(false);

    	emit updateTab();
    }

    void
	OpcUaAttributeBaseTab::onOrderDeleteAction(void)
    {
    	nodeChange(nodeInfo_);

    	orderOkAction_->setEnabled(false);
    	orderDeleteAction_->setEnabled(false);
    }

    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    //
    // widget actions
    //
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    void
	OpcUaAttributeBaseTab::update(void)
    {
    	orderOkAction_->setEnabled(true);
    	orderDeleteAction_->setEnabled(true);

    	if (!nodeIdWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!browseNameWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!displayNameWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!descriptionWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!writeMaskWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!userWriteMaskWidget_->isValid()) orderOkAction_->setEnabled(false);
    }

}


