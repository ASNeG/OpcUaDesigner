/*
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
#include <QToolBar>
#include <QMenu>

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeObjectTypeTab.h"

namespace OpcUaNodeSet
{


	OpcUaAttributeObjectTypeTab::OpcUaAttributeObjectTypeTab(QWidget* parent)
	: QWidget()
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

		// IsAbstract
		QLabel* isAbstractLabel = new QLabel("IsAbstract");
		gridLayout->addWidget(isAbstractLabel, 0, 0);

		isAbstractWidget_ = new IsAbstractWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(isAbstractWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 0, 1);

		vBoxLayout->addLayout(gridLayout);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);

		//
		// actions
		//
		connect(isAbstractWidget_, SIGNAL(update()), this, SLOT(update()));
	}

	OpcUaAttributeObjectTypeTab::~OpcUaAttributeObjectTypeTab(void)
	{
	}

	void
	OpcUaAttributeObjectTypeTab::nodeChange(NodeInfo* nodeInfo)
	{
		bool enabled = true;
		nodeInfo_ = nodeInfo;

		OpcUaNodeId nodeId;
		nodeInfo->baseNode_->getNodeId(nodeId);
		if (nodeId.namespaceIndex() == 0) {
			enabled = false;
		}

		isAbstractWidget_->nodeChange(nodeInfo);
		isAbstractWidget_->enabled(enabled);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// Toolbar
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	OpcUaAttributeObjectTypeTab::createToolBarActions(void)
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
	OpcUaAttributeObjectTypeTab::onOrderOkAction(void)
    {
    	InformationModel::SPtr informationModel_ = nodeInfo_->informationModel_;
    	BaseNodeClass::SPtr baseNode = nodeInfo_->baseNode_;

       	// check isAbstract
        OpcUaBoolean isAbstract;
        baseNode->getIsAbstractSync(isAbstract);

        OpcUaBoolean newIsAbstract;
        isAbstractWidget_->getValue(newIsAbstract);

        if (isAbstract != newIsAbstract) {
        	baseNode->setIsAbstract(newIsAbstract);
        }

    	orderOkAction_->setEnabled(false);
    	orderDeleteAction_->setEnabled(false);

    	emit updateTab();
    }

    void
	OpcUaAttributeObjectTypeTab::onOrderDeleteAction(void)
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
	OpcUaAttributeObjectTypeTab::update(void)
    {
    	orderOkAction_->setEnabled(true);
    	orderDeleteAction_->setEnabled(true);

    	if (!isAbstractWidget_->isValid()) orderOkAction_->setEnabled(false);
    }


}


