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

#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeValueTypeTab.h"

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{

	OpcUaAttributeValueTypeTab::OpcUaAttributeValueTypeTab(QWidget* parent)
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

		// ArrayDimensions
		QLabel* arrayDimensionsLabel = new QLabel("ArrayDimensions");
		gridLayout->addWidget(arrayDimensionsLabel, 1, 0);

		arrayDimensionsWidget_ = new ArrayDimensionsWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(arrayDimensionsWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);


		// DataType
		QLabel* dataTypeLabel = new QLabel("DataType");
		gridLayout->addWidget(dataTypeLabel, 2, 0);

		dataTypeWidget_ = new DataTypeWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(dataTypeWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 2, 1);



		// ValueRank
		QLabel* valueRankLabel = new QLabel("ValueRank");
		gridLayout->addWidget(valueRankLabel, 3, 0);

		valueRankWidget_ = new ValueRankWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(valueRankWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 3, 1);


		// Value
		QLabel* valueLabel = new QLabel("Value");
		gridLayout->addWidget(valueLabel, 4, 0);

		valueWidget_ = new ValueWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(valueWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 4, 1);


		vBoxLayout->addLayout(gridLayout);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);

		//
		// actions
		//
		connect(isAbstractWidget_, SIGNAL(update()), this, SLOT(update()));
		connect(arrayDimensionsWidget_, SIGNAL(update()), this, SLOT(update()));
		connect(dataTypeWidget_, SIGNAL(update()), this, SLOT(update()));
		connect(valueRankWidget_, SIGNAL(update()), this, SLOT(update()));
		connect(valueWidget_, SIGNAL(update()), this, SLOT(update()));
	}

	OpcUaAttributeValueTypeTab::~OpcUaAttributeValueTypeTab(void)
	{
	}

	void
	OpcUaAttributeValueTypeTab::nodeChange(NodeInfo* nodeInfo)
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

	    arrayDimensionsWidget_->nodeChange(nodeInfo);
		arrayDimensionsWidget_->enabled(enabled);

	    dataTypeWidget_->nodeChange(nodeInfo);
		dataTypeWidget_->enabled(enabled);

	    valueRankWidget_->nodeChange(nodeInfo);
		valueRankWidget_->enabled(enabled);

	    valueWidget_->nodeChange(nodeInfo);
		valueWidget_->enabled(enabled);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// Toolbar
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	OpcUaAttributeValueTypeTab::createToolBarActions(void)
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
	OpcUaAttributeValueTypeTab::onOrderOkAction(void)
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

        // check array dimensions
        // FIXME: todo

        // check data type
        // FIXME: todo

      	// check value rank
        if (valueRankWidget_->acceptValue()) {
            OpcUaInt32 savedValue;
            valueRankWidget_->getSavedValue(savedValue);
        	baseNode->setValueRank(savedValue);
        }

        // check value
        if (valueWidget_->acceptValue()) {
             OpcUaDataValue savedValue;
             valueWidget_->getSavedValue(savedValue);
         	baseNode->setValue(savedValue);
         }

    	orderOkAction_->setEnabled(false);
    	orderDeleteAction_->setEnabled(false);

    	emit updateTab();
    }

    void
	OpcUaAttributeValueTypeTab::onOrderDeleteAction(void)
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
	OpcUaAttributeValueTypeTab::update(void)
    {
    	orderOkAction_->setEnabled(true);
    	orderDeleteAction_->setEnabled(true);

    	if (!isAbstractWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!arrayDimensionsWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!dataTypeWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!valueRankWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!valueWidget_->isValid()) orderOkAction_->setEnabled(false);
    }

}


