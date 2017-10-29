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

#include <OpcUaNodeSetModul/Dialog/ArrayDimensionsDialog.h>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QToolBar>
#include <QMenu>

#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeValueTab.h"

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{

	OpcUaAttributeValueTab::OpcUaAttributeValueTab(QWidget* parent)
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


		// AccessLevel
		QLabel* accessLevelLabel = new QLabel("AccessLevel");
		gridLayout->addWidget(accessLevelLabel, 0, 0);

		accessLevelWidget_ = new AccessLevelWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(accessLevelWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 0, 1);


		// Historizing
		QLabel* historizingLabel = new QLabel("Historizing");
		gridLayout->addWidget(historizingLabel, 1, 0);

		historizingWidget_ = new HistorizingWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(historizingWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);


		// MinimumSamplingInterval
		QLabel* minimumSamplingIntervalLabel = new QLabel("MinimumSamplingInterval");
		gridLayout->addWidget(minimumSamplingIntervalLabel, 2, 0);

		minimumSamplingIntervalWidget_ = new MinimumSamplingIntervalWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(minimumSamplingIntervalWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 2, 1);

		// ArrayDimensions
		QLabel* arrayDimensionsLabel = new QLabel("ArrayDimensions");
		gridLayout->addWidget(arrayDimensionsLabel, 3, 0);

		arrayDimensionsWidget_ = new ArrayDimensionsWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(arrayDimensionsWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 3, 1);


		// DataType
		QLabel* dataTypeLabel = new QLabel("DataType");
		gridLayout->addWidget(dataTypeLabel, 4, 0);

		dataTypeWidget_ = new DataTypeWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(dataTypeWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 4, 1);



		// ValueRank
		QLabel* valueRankLabel = new QLabel("ValueRank");
		gridLayout->addWidget(valueRankLabel, 5, 0);

		valueRankWidget_ = new ValueRankWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(valueRankWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 5, 1);


		// Value
		QLabel* valueLabel = new QLabel("Value");
		gridLayout->addWidget(valueLabel, 6, 0);

		valueWidget_ = new ValueWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(valueWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 6, 1);


		vBoxLayout->addLayout(gridLayout);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);

		//
		// actions
		//
		connect(accessLevelWidget_, SIGNAL(update()), this, SLOT(onUpdate()));
		connect(historizingWidget_, SIGNAL(update()), this, SLOT(onUpdate()));
		connect(minimumSamplingIntervalWidget_, SIGNAL(update()), this, SLOT(onUpdate()));
		connect(arrayDimensionsWidget_, SIGNAL(update()), this, SLOT(onUpdate()));
		connect(dataTypeWidget_, SIGNAL(update()), this, SLOT(onUpdate()));
		connect(valueRankWidget_, SIGNAL(update()), this, SLOT(onUpdate()));
		connect(valueWidget_, SIGNAL(update()), this, SLOT(onUpdate()));

		connect(
			arrayDimensionsWidget_,
			SIGNAL(selectDimensionArray(OpcUaUInt32Array::SPtr&)),
			this,
			SLOT(onSelectDimensionArray(OpcUaUInt32Array::SPtr&))
		);
	}

	OpcUaAttributeValueTab::~OpcUaAttributeValueTab(void)
	{
	}

	void
	OpcUaAttributeValueTab::nodeChange(NodeInfo* nodeInfo)
	{
		bool enabled = true;
		nodeInfo_ = nodeInfo;

		OpcUaNodeId nodeId;
		nodeInfo->baseNode_->getNodeId(nodeId);
		if (nodeId.namespaceIndex() == 0) {
			enabled = false;
		}

		accessLevelWidget_->nodeChange(nodeInfo);
		accessLevelWidget_->enabled(enabled);

		historizingWidget_->nodeChange(nodeInfo);
		historizingWidget_->enabled(enabled);

		minimumSamplingIntervalWidget_->nodeChange(nodeInfo);
		minimumSamplingIntervalWidget_->enabled(enabled);

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
	OpcUaAttributeValueTab::createToolBarActions(void)
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
	OpcUaAttributeValueTab::onOrderOkAction(void)
    {
    	InformationModel::SPtr informationModel_ = nodeInfo_->informationModel_;
    	BaseNodeClass::SPtr baseNode = nodeInfo_->baseNode_;

       	// check access level
        OpcUaByte accessLevel;
        baseNode->getAccessLevelSync(accessLevel);

        OpcUaByte newAccessLevel;
        accessLevelWidget_->getValue(newAccessLevel);

        if (accessLevel != newAccessLevel) {
        	baseNode->setAccessLevel(newAccessLevel);
        }

       	// check historizing
        if (historizingWidget_->acceptValue()) {
            OpcUaBoolean newHistorizing;
            historizingWidget_->getNewValue(newHistorizing);
        	baseNode->setHistorizing(newHistorizing);
        }

       	// check minimum sampling interval
        OpcUaDouble minimumSamplingInterval;
        baseNode->getMinimumSamplingIntervalSync(minimumSamplingInterval);

        OpcUaDouble newMinimumSamplingInterval;
        minimumSamplingIntervalWidget_->getValue(newMinimumSamplingInterval);

        if (minimumSamplingInterval != newMinimumSamplingInterval) {
        	baseNode->setMinimumSamplingInterval(newMinimumSamplingInterval);
        }

        // check array dimensions
        OpcUaUInt32Array dimensionsArray;
        baseNode->getArrayDimensions(dimensionsArray);

        OpcUaUInt32Array::SPtr newDimensionsArray = constructSPtr<OpcUaUInt32Array>();
        arrayDimensionsWidget_->getValue(newDimensionsArray);

        if (newDimensionsArray.get() != nullptr) {
        	if (dimensionsArray != *newDimensionsArray) {
        		newDimensionsArray->out(std::cout); std::cout << std::endl;
        		baseNode->setArrayDimensions(*newDimensionsArray);
        	}
        }
        else {
        	baseNode->unsetArrayDimensions();
        }

        // check data type
        if (dataTypeWidget_->acceptValue()) {
            OpcUaNodeId newDataType;
            dataTypeWidget_->getNewValue(newDataType);
        	baseNode->setDataType(newDataType);
        }

      	// check value rank
        OpcUaInt32 valueRank;
        baseNode->getValueRankSync(valueRank);

        OpcUaInt32 newValueRank;
        valueRankWidget_->getValue(newValueRank);

        if (valueRank != newValueRank) {
        	baseNode->setValueRank(newValueRank);
        }

    	orderOkAction_->setEnabled(false);
    	orderDeleteAction_->setEnabled(false);

    	// check value
    	// FIXME: todo

    	emit updateTab();
    }

    void
	OpcUaAttributeValueTab::onOrderDeleteAction(void)
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
	OpcUaAttributeValueTab::onUpdate(void)
    {
    	orderOkAction_->setEnabled(true);
    	orderDeleteAction_->setEnabled(true);

    	if (!accessLevelWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!historizingWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!minimumSamplingIntervalWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!arrayDimensionsWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!dataTypeWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!valueRankWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!valueWidget_->isValid()) orderOkAction_->setEnabled(false);
    }

    void
	OpcUaAttributeValueTab::onSelectDimensionArray(OpcUaUInt32Array::SPtr& arrayDimensions)
    {
    	ArrayDimensionDialog dialog;
    	dialog.setArrayDimensions(arrayDimensions);
    	dialog.exec();

    	if (dialog.ok()) {
    		OpcUaUInt32Array::SPtr ad = constructSPtr<OpcUaUInt32Array>();
    		dialog.getArrayDimensions(ad);
    		arrayDimensionsWidget_->nodeChange(ad);
    	}
    }

}


