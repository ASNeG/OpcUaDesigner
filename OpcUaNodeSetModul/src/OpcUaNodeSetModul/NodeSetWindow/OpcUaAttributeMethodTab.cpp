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

#include "OpcUaStackServer/InformationModel/InformationModelAccess.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeMethodTab.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	OpcUaAttributeMethodTab::OpcUaAttributeMethodTab(QWidget* parent)
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

		// Executable
		QLabel* executableLabel = new QLabel("Executable");
		gridLayout->addWidget(executableLabel, 0, 0, Qt::AlignTop);

		executableWidget_ = new ExecutableWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(executableWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 0, 1);


		// UserExecutable
		QLabel* userExecutableLabel = new QLabel("UserExecutable");
		gridLayout->addWidget(userExecutableLabel, 1, 0, Qt::AlignTop);

		userExecutableWidget_ = new UserExecutableWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(userExecutableWidget_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);

		vBoxLayout->addLayout(gridLayout);

		// input arguments
		inArgumentsWidget_ = new ArgumentsWidget("Input Arguments");
		vBoxLayout->addWidget(inArgumentsWidget_);

		// output arguments
		outArgumentsWidget_ = new ArgumentsWidget("Output Arguments");
		vBoxLayout->addWidget(outArgumentsWidget_);


		vBoxLayout->addStretch();

		setLayout(vBoxLayout);

		//
		// actions
		//
		connect(executableWidget_, SIGNAL(update()), this, SLOT(update()));
		connect(userExecutableWidget_, SIGNAL(update()), this, SLOT(update()));
	}

	OpcUaAttributeMethodTab::~OpcUaAttributeMethodTab(void)
	{
	}

	void
	OpcUaAttributeMethodTab::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::Vec childBaseNodeClassVec;
		BaseNodeClass::SPtr baseNode;
		bool enabled = true;
		nodeInfo_ = nodeInfo;

		OpcUaNodeId nodeId;
		nodeInfo->baseNode_->getNodeId(nodeId);
		if (nodeId.namespaceIndex() == 0) {
			enabled = false;
		}


		//
		// update executable
		//
		executableWidget_->nodeChange(nodeInfo);
		executableWidget_->enabled(enabled);


		//
		// update user executable
		//
		userExecutableWidget_->nodeChange(nodeInfo);
		userExecutableWidget_->enabled(enabled);


		//
		// update input arguments
		//
		baseNode.reset();
		childBaseNodeClassVec.clear();

		InformationModelAccess ima1(nodeInfo->informationModel_);
		ima1.getChildHierarchically(
			nodeInfo->baseNode_,
			childBaseNodeClassVec
		);

		for (uint32_t idx = 0; idx < childBaseNodeClassVec.size(); idx++) {
			BaseNodeClass::SPtr baseNodeChild = childBaseNodeClassVec[idx];

			OpcUaLocalizedText displayName;
			baseNodeChild->getDisplayName(displayName);

			if (displayName.text().toStdString() == "InputArguments") {
				baseNode = baseNodeChild;
				break;
			}
		}
		inArgumentsWidget_->nodeChange(nodeInfo, baseNode);
		inArgumentsWidget_->enabled(enabled);


		//
		// update output arguments
		//
		baseNode.reset();
		childBaseNodeClassVec.clear();

		InformationModelAccess ima2(nodeInfo->informationModel_);
		ima2.getChildHierarchically(
			nodeInfo->baseNode_,
			childBaseNodeClassVec
		);

		for (uint32_t idx = 0; idx < childBaseNodeClassVec.size(); idx++) {
			BaseNodeClass::SPtr baseNodeChild = childBaseNodeClassVec[idx];

			OpcUaLocalizedText displayName;
			baseNodeChild->getDisplayName(displayName);

			if (displayName.text().toStdString() == "OutputArguments") {
				baseNode = baseNodeChild;
				break;
			}
		}
		outArgumentsWidget_->nodeChange(nodeInfo, baseNode);
		outArgumentsWidget_->enabled(enabled);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// Toolbar
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	OpcUaAttributeMethodTab::createToolBarActions(void)
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
	OpcUaAttributeMethodTab::onOrderOkAction(void)
    {
    	InformationModel::SPtr informationModel_ = nodeInfo_->informationModel_;
    	BaseNodeClass::SPtr baseNode = nodeInfo_->baseNode_;

       	// check executable
        OpcUaBoolean executable;
        baseNode->getExecutableSync(executable);

        OpcUaBoolean newExecutable;
        executableWidget_->getValue(newExecutable);

        if (executable != newExecutable) {
        	baseNode->setExecutable(newExecutable);
        }

      	// check user executable
        OpcUaBoolean userExecutable;
        baseNode->getUserExecutableSync(userExecutable);

        OpcUaBoolean newUserExecutable;
        userExecutableWidget_->getValue(newUserExecutable);

        if (userExecutable != newUserExecutable) {
        	baseNode->setExecutable(newUserExecutable);
        }

    	orderOkAction_->setEnabled(false);
    	orderDeleteAction_->setEnabled(false);

    	emit updateTab();
    }

    void
	OpcUaAttributeMethodTab::onOrderDeleteAction(void)
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
	OpcUaAttributeMethodTab::update(void)
    {
    	orderOkAction_->setEnabled(true);
    	orderDeleteAction_->setEnabled(true);

    	if (!executableWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!userExecutableWidget_->isValid()) orderOkAction_->setEnabled(false);
    }


}


