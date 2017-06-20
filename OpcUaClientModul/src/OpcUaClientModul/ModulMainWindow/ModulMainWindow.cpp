/*
   Copyright 2016-2017 Samuel Huebl (samuel@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Samuel Huebl (samuel@huebl-sgh.de)
 */

#include "OpcUaClientModul/ModulMainWindow/ModulMainWindow.h"

namespace OpcUaClientModul
{
	ModulMainWindow::ModulMainWindow(QMainWindow* parentMainWindow, OpcUaClientProvider* client)
	: QMainWindow()
	, modulName_("")
	, parentMainWindow_(parentMainWindow)
	, client_(client)
	, treeNodeWidget_(new TreeNodeWidget(client))
	, attributeWidget_(new AttributeWidget(client))
	, connectionInfoWidget_(new ConnectionInfoWidget())
	{
	}

	ModulMainWindow::~ModulMainWindow()
	{
	}

	bool
	ModulMainWindow::create(void)
	{
		setWindowTitle(QString("OpcUaClientModul - ModulMainWindow"));

		statusBar()->addWidget(new QLabel("Connection: opc.tcp://127.0.0.1:8889"));
		statusBar()->addWidget(new QLabel("| Connection Status: Connected"));

		// create dock tree node widget
		QDockWidget* dockTreeNodeWidget = new QDockWidget(tr("OPC UA AddressSpace"));
		dockTreeNodeWidget->setObjectName("ProjectNameTreeNode");
		dockTreeNodeWidget->setWidget(treeNodeWidget_);
		dockTreeNodeWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
		dockTreeNodeWidget->setFloating(true);
		this->addDockWidget(Qt::LeftDockWidgetArea, dockTreeNodeWidget);

		if (!treeNodeWidget_->create())
		{
			return false;
		}

		// create dock attribute widget
		QDockWidget* dockAttributeWidget = new QDockWidget(tr("OPC UA Attribute"));
		dockAttributeWidget->setObjectName("ProjectNameAttribute");
		dockAttributeWidget->setWidget(attributeWidget_);
		dockAttributeWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
		dockAttributeWidget->setFloating(true);
		this->addDockWidget(Qt::RightDockWidgetArea, dockAttributeWidget);

		// set connections
		connect(
			treeNodeWidget_, SIGNAL(nodeChanged(BaseNode*)),
			attributeWidget_, SLOT(nodeChange(BaseNode*))
		);
		connect(
				treeNodeWidget_, SIGNAL(createNewMonitorItem(BaseNode*)),
				this, SIGNAL(createNewMonitorItem(BaseNode*))
		);

		return true;
	}

	bool
	ModulMainWindow::open(void)
	{
		return false;
	}

	void
	ModulMainWindow::modulName(const std::string& modulName)
	{
		modulName_ = modulName;
	}

	std::string
	ModulMainWindow::modulName(void)
	{
		return modulName_;
	}
}
