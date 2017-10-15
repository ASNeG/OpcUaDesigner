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

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeMethodTab.h"

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
		gridLayout->addWidget(executableLabel, 0, 0);

		executableLineEdit_ = new QLineEdit();
		executableLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(executableLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 0, 1);


		// UserExecutable
		QLabel* userExecutableLabel = new QLabel("UserExecutable");
		gridLayout->addWidget(userExecutableLabel, 1, 0);

		userExecutableLineEdit_ = new QLineEdit();
		userExecutableLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(userExecutableLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);


		vBoxLayout->addLayout(gridLayout);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);

		//
		// actions
		//
		//connect(executableWidget_, SIGNAL(update()), this, SLOT(update()));
		//connect(userExecutableWidget_, SIGNAL(update()), this, SLOT(update()));
	}

	OpcUaAttributeMethodTab::~OpcUaAttributeMethodTab(void)
	{
	}

	void
	OpcUaAttributeMethodTab::nodeChange(NodeInfo* nodeInfo)
	{
		setExecutable(nodeInfo);
		setUserExecutable(nodeInfo);

#if 0
		bool enabled = true;
		nodeInfo_ = nodeInfo;

		OpcUaNodeId nodeId;
		nodeInfo->baseNode_->getNodeId(nodeId);
		if (nodeId.namespaceIndex() == 0) {
			enabled = false;
		}

		executableWidget_->nodeChange(nodeInfo);
		executableWidget_->enabled(enabled);

		userExecutableWidget_->nodeChange(nodeInfo);
		userExecutableWidget_->enabled(enabled);
#endif
	}

	void
	OpcUaAttributeMethodTab::setExecutable(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullExecutable()) {
			executableLineEdit_->setText(QString(""));
		}
		else {
			OpcUaBoolean executableLineEdit;
			baseNode->getExecutable(executableLineEdit);
			executableLineEdit_->setText(executableLineEdit == 1 ? QString("True") : QString("False"));
		}
	}

	void
	OpcUaAttributeMethodTab::setUserExecutable(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullUserExecutable()) {
			userExecutableLineEdit_->setText(QString(""));
		}
		else {
			OpcUaBoolean userExecutableLineEdit;
			baseNode->getUserExecutable(userExecutableLineEdit);
			userExecutableLineEdit_->setText(userExecutableLineEdit == 1 ? QString("True") : QString("False"));
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
#if 0
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
#endif

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

#if 0
    	if (!executableWidget_->isValid()) orderOkAction_->setEnabled(false);
    	if (!userExecutableWidget_->isValid()) orderOkAction_->setEnabled(false);
#endif
    }


}


