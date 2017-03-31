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

#include "OpcUaStackCore/Base/Config.h"
#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaNodeSetModul/NodeSetWindow/NodeSetWindow.h"

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{

	NodeSetWindow::NodeSetWindow(QMainWindow* parentMainWindow)
	: QMainWindow()
	, modulName_("")
	, modulFile_("")
	, parentMainWindow_(parentMainWindow)
	, libraryConfig_(NULL)
	{
	}

	NodeSetWindow::~NodeSetWindow(void)
	{
	}

	bool
	NodeSetWindow::create(void)
	{
		bool rc;

		setWindowTitle(QString("OpcUaNodeSet - %1").arg(QString(modulName_.c_str())));


		// --------------------------------------------------------------------
		//
		// opc ua tree window
		//
		// --------------------------------------------------------------------

		// create opc ua tree window
		opcUaTreeWindow_ = new OpcUaTreeWindow(NULL);
		opcUaTreeWindow_->standardNodeSetFileName(libraryConfig_->standardNodeSetFile_);

		// create dock widget
		QDockWidget* dockWidget = new QDockWidget(tr("OPC UA Model"));
		dockWidget->setObjectName("ProjectName");
		dockWidget->setWidget(opcUaTreeWindow_);
		dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
		this->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

		rc = opcUaTreeWindow_->create(modulFile_);
		if (!rc) {
			delete dockWidget;
			return false;
		}

		// --------------------------------------------------------------------
		//
		// opc ua attribute window
		//
		// --------------------------------------------------------------------
		opcUaAttributeWindow_ = new OpcUaAttributeWindow(NULL);
		this->setCentralWidget(opcUaAttributeWindow_);

		// --------------------------------------------------------------------
		//
		// signals
		//
		// --------------------------------------------------------------------
		connect(
			opcUaTreeWindow_, SIGNAL(nodeChanged(NodeInfo*)),
			opcUaAttributeWindow_, SLOT(onNodeChanged(NodeInfo*))
		);

		return true;
	}

	bool
	NodeSetWindow::open(void)
	{
		// FIXME: todo
		return false;
	}

	void
	NodeSetWindow::libraryConfig(LibraryConfig* libraryConfig)
	{
		libraryConfig_ = libraryConfig;
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

