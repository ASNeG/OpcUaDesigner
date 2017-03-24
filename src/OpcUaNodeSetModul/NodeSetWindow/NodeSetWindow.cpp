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

#include <QString>
#include <QDockWidget>

#include "OpcUaNodeSetModul/NodeSetWindow/NodeSetWindow.h"

namespace OpcUaNodeSet
{

	NodeSetWindow::NodeSetWindow(QMainWindow* parentMainWindow)
	: QMainWindow()
	, modulName_("")
	, modulFile_("")
	, parentMainWindow_(parentMainWindow)
	{
	}

	NodeSetWindow::~NodeSetWindow(void)
	{
	}

	void
	NodeSetWindow::start(void)
	{
		setWindowTitle(QString("OpcUaNodeSet - %1").arg(QString(modulName_.c_str())));

		// create opc ua tree window
		opcUaTreeWindow_ = new OpcUaTreeWindow(NULL);

		// create dock widget
		QDockWidget* dockWidget = new QDockWidget(tr("OPC UA Model"));
		dockWidget->setObjectName("ProjectName");
		dockWidget->setWidget(opcUaTreeWindow_);
		dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
		this->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
	}

	void
	NodeSetWindow::modulName(const std::string& modulName)
	{
		modulName_ = modulName;
	}

	std::string
	NodeSetWindow::modulName(void)
	{
		return modulName_;
	}

	void
	NodeSetWindow::modulFile(const std::string& modulFile)
	{
		modulFile_ = modulFile;
	}

	std::string
	NodeSetWindow::modulFile(void)
	{
		return modulFile_;
	}

}

