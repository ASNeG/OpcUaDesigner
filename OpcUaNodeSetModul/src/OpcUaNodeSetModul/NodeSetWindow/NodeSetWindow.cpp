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
#include <QCloseEvent>
#include <QMessageBox>

#include "OpcUaStackCore/Base/Config.h"
#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaNodeSetModul/NodeSetWindow/NodeSetWindow.h"

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{

	NodeSetWindow::NodeSetWindow(QMainWindow* parentMainWindow)
	: QMainWindow()
	, projectName_("")
	, projectFile_("")
	, parentMainWindow_(parentMainWindow)
	, libraryConfig_(NULL)
	{
	}

	NodeSetWindow::~NodeSetWindow(void)
	{
	}

	void
	NodeSetWindow::closeEvent(QCloseEvent* event)
	{
		event->ignore();
	}

	bool
	NodeSetWindow::createWindow(void)
	{
		setWindowTitle(QString("OpcUaNodeSet - %1").arg(QString(projectName_.c_str())));

		// create opc ua tree window
		opcUaTreeWindow_ = new OpcUaTreeWindow(NULL);
		opcUaTreeWindow_->dataModel(&dataModel_);
		opcUaTreeWindow_->standardNodeSetFileName(libraryConfig_->standardNodeSetFile_);

		// create dock widget
		QDockWidget* dockWidget = new QDockWidget(tr("OPC UA Model"));
		dockWidget->setObjectName("ProjectName");
		dockWidget->setWidget(opcUaTreeWindow_);
		dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
		this->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);


		// opc ua attribute window
		opcUaAttributeWindow_ = new OpcUaAttributeWindow(NULL);
		this->setCentralWidget(opcUaAttributeWindow_);


		// signals
		connect(
			opcUaTreeWindow_, SIGNAL(nodeChanged(NodeInfo*)),
			opcUaAttributeWindow_, SLOT(onNodeChanged(NodeInfo*))
		);

		return true;
	}

	bool
	NodeSetWindow::projectNew(uint32_t handle, const std::string& projectName, const std::string& projectFile)
	{
		bool rc;

		projectName_ = projectName;
		projectFile_ = projectFile;

		// create window
		if (!createWindow()) {
			return false;
		}

		// create empty node set
		if (!dataModel_.loadStandardNodeSet(libraryConfig_->standardNodeSetFile_)) {
			QMessageBox msgBox;
			msgBox.setText(QString("read standard nodeset file %1 error").arg(libraryConfig_->standardNodeSetFile_.c_str()));
			msgBox.exec();
			return false;
		}

		// save empty node set
		if (!dataModel_.writeNodeSet(projectFile_)) {
			QMessageBox msgBox;
			msgBox.setText(QString("cannot create node set file %1").arg(projectFile_.c_str()));
			msgBox.exec();
		}

		// show nodeset
		if (!opcUaTreeWindow_->show()) {
			return false;
		}

		return true;
	}

    bool
    NodeSetWindow::projectOpen(uint32_t handle, const std::string& projectName, const std::string& projectFile)
    {
    	// FIXME:
    	return true;
    }

	bool
	NodeSetWindow::projectSave(uint32_t handle)
	{
		// FIXME:
		return true;
	}

	bool
	NodeSetWindow::projectSaveAs(uint32_t handle, const std::string& projectFile)
	{
		// FIXME:
		return true;
	}

	bool
	NodeSetWindow::projectRename(uint32_t handle, const std::string& projectName)
	{
		// FIXME:
		return true;
	}

	bool
	NodeSetWindow::projectReadyToClose(uint32_t handle)
	{
		// FIXME:
		return true;
	}

	bool
	NodeSetWindow::projectClose(uint32_t handle)
	{
		// FIXME:
		return true;
	}

#if 0
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

		rc = opcUaTreeWindow_->open(modulFile_);
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
#endif

	void
	NodeSetWindow::libraryConfig(LibraryConfig* libraryConfig)
	{
		libraryConfig_ = libraryConfig;
	}

}

