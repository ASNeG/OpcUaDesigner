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

		historizingLineEdit_ = new QLineEdit();
		historizingLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(historizingLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);


		// MinimumSamplingInterval
		QLabel* minimumSamplingIntervalLabel = new QLabel("MinimumSamplingInterval");
		gridLayout->addWidget(minimumSamplingIntervalLabel, 2, 0);

		minimumSamplingIntervalLineEdit_ = new QLineEdit();
		minimumSamplingIntervalLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(minimumSamplingIntervalLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 2, 1);

		// ArrayDimensions
		QLabel* arrayDimensionsLabel = new QLabel("ArrayDimensions");
		gridLayout->addWidget(arrayDimensionsLabel, 3, 0);

		arrayDimensionsLineEdit_ = new QLineEdit();
		arrayDimensionsLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(arrayDimensionsLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 3, 1);


		// DataType
		QLabel* dataTypeLabel = new QLabel("DataType");
		gridLayout->addWidget(dataTypeLabel, 4, 0);

		dataTypeLineEdit_ = new QLineEdit();
		dataTypeLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(dataTypeLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 4, 1);



		// ValueRank
		QLabel* valueRankLabel = new QLabel("ValueRank");
		gridLayout->addWidget(valueRankLabel, 5, 0);

		valueRankLineEdit_ = new QLineEdit();
		valueRankLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(valueRankLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 5, 1);


		// Value
		QLabel* valueLabel = new QLabel("Value");
		gridLayout->addWidget(valueLabel, 6, 0);

		valueLineEdit_ = new QLineEdit();
		valueLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(valueLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 6, 1);


		vBoxLayout->addLayout(gridLayout);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);

		//
		// actions
		//
		connect(accessLevelWidget_, SIGNAL(update()), this, SLOT(update()));
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

		setArrayDimensions(nodeInfo);
		setDataType(nodeInfo);
		setHistorizing(nodeInfo);
		setMinimumSamplingInterval(nodeInfo);
		setValue(nodeInfo);
		setValueRank(nodeInfo);
	}

	void
	OpcUaAttributeValueTab::setArrayDimensions(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullArrayDimensions()) {
			arrayDimensionsLineEdit_->setText(QString(""));
		}
		else {
			OpcUaUInt32Array arrayDimensions;
			baseNode->getArrayDimensions(arrayDimensions);
			std::stringstream ss;
			arrayDimensions.out(ss);
			arrayDimensionsLineEdit_->setText(QString(ss.str().c_str()));
		}
	}

	void
	OpcUaAttributeValueTab::setDataType(NodeInfo* nodeInfo)
	{
		bool success;

		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
	   	if (baseNode->isNullDataType()) {
	   		dataTypeLineEdit_->setText(QString(""));
	   	}
	   	else {
	    	std::string dataTypeString = "";

	    	OpcUaNodeId dataType;
	    	success = baseNode->getDataType(dataType);
	    	if (success) {

	    		if (dataType.namespaceIndex() == 0 &&  dataType.nodeIdType() == OpcUaBuildInType_OpcUaUInt32) {
	    			uint32_t id = dataType.nodeId<uint32_t>();
	    			dataTypeString = OpcUaIdMap::shortString(id);
	    		}
	    		else {
	    			dataTypeString = dataType.toString();
	    		}
	    	}

	    	dataTypeLineEdit_->setText(QString(dataTypeString.c_str()));
	    }
	}

	void
	OpcUaAttributeValueTab::setHistorizing(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullHistorizing()) {
			historizingLineEdit_->setText(QString(""));
		}
		else {
			OpcUaBoolean historizing;
			baseNode->getHistorizing(historizing);
			historizingLineEdit_->setText(historizing == 1 ? QString("True") : QString("False"));
		}
	}

	void
	OpcUaAttributeValueTab::setMinimumSamplingInterval(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullMinimumSamplingInterval()) {
			minimumSamplingIntervalLineEdit_->setText(QString(""));
		}
		else {
			OpcUaDouble minimumSamplingInterval;
			baseNode->getMinimumSamplingInterval(minimumSamplingInterval);
			minimumSamplingIntervalLineEdit_->setText(QString("%1").arg((double)minimumSamplingInterval));
		}
	}

	void
	OpcUaAttributeValueTab::setValue(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullValue()) {
			valueLineEdit_->setText(QString(""));
		}
		else {
			OpcUaDataValue dataValue;
			baseNode->getValue(dataValue);
			std::stringstream ss;
			dataValue.out(ss);
			valueLineEdit_->setText(QString(ss.str().c_str()));
		}
	}

	void
	OpcUaAttributeValueTab::setValueRank(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullValueRank()) {
			valueRankLineEdit_->setText(QString(""));
		}
		else {
			OpcUaInt32 valueRank;
			baseNode->getValueRank(valueRank);
			valueRankLineEdit_->setText(QString("%1").arg((int32_t)valueRank));
		}
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

#if 0
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
#endif

    	orderOkAction_->setEnabled(false);
    	orderDeleteAction_->setEnabled(false);

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
	OpcUaAttributeValueTab::update(void)
    {
    	orderOkAction_->setEnabled(true);
    	orderDeleteAction_->setEnabled(true);

    	if (!accessLevelWidget_->isValid()) orderOkAction_->setEnabled(false);
    }

}


