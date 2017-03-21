/*
   Copyright 2016 Kai Huebl (kai@huebl-sgh.de)

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

#include "OpcUaGui/Application/MainWindow.h"
#include "OpcUaGui/Application/ProjectWindow.h"
#include "OpcUaGui/Application/Application.h"
#include "OpcUaGui/Application/Modul.h"
#include <iostream>

#include <QApplication>
#include <QCloseEvent>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>
#include <QTreeWidget>
#include <QMessageBox>

namespace OpcUaGui
{

	MainWindow::MainWindow(void)
	: QMainWindow()
	, newProjectAction_(NULL)
	, application_(new Application())
	, modul_(new Modul())
	{
		createActions();
		createMenus();
		createToolBars();
		createStatusBar();
	}

	MainWindow::~MainWindow(void)
	{
		delete modul_;
		delete application_;
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// application
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	bool
	MainWindow::startup(int argc, char**argv)
	{
		// check number of command line parameters
		if (argc != 2) {
			QMessageBox::critical(
				this,
				"OpcUaDesigner - command line error",
				"usage: OpcUaDesigner <ConfigFileName>",
				QMessageBox::Ok
			);
			return false;
		}

		// parse configuration file
		if (!application_->parseConfig(argv[1])) {
			QMessageBox::critical(
				this,
				"OpcUaDesigner - configuration file error",
				application_->errorString().c_str(),
				QMessageBox::Ok
			);
			return false;
		}

		// init logging
		if (!application_->initLogging()) {
			QMessageBox::critical(
				this,
				"OpcUaDesigner - logging error",
				application_->errorString().c_str(),
				QMessageBox::Ok
			);
			return false;
		}

		// load modul configuration
		modul_->modulDirectory(application_->libraryConfigPath());
		if (!modul_->startup()) {
			return false;
		}
		addModulMenus();

		return true;
	}

	bool
	MainWindow::shutdown(void)
	{
		modul_->shutdown();
		return true;
	}

	void
	MainWindow::closeEvent(QCloseEvent* event)
	{
		std::cout << "STOP" << std::endl;
		event->accept();
	}

	void
	MainWindow::createActions(void)
	{
		//
		// project actions
		//
		newProjectAction_ = new QAction(tr("&New"), this);
		newProjectAction_->setIcon(QIcon(":images/New.png"));
		newProjectAction_->setShortcut(QKeySequence::New);
		newProjectAction_->setStatusTip(tr("create a new project"));
		connect(newProjectAction_, SIGNAL(triggered()), this, SLOT(newProjectAction()));

		openProjectAction_ = new QAction(tr("&Open"), this);
		openProjectAction_->setIcon(QIcon(":images/Open.png"));
		openProjectAction_->setShortcut(QKeySequence::Open);
		openProjectAction_->setStatusTip(tr("open an existing project"));
		connect(openProjectAction_, SIGNAL(triggered()), this, SLOT(openProjectAction()));

		saveProjectAction_ = new QAction(tr("&Save"), this);
		saveProjectAction_->setIcon(QIcon(":images/Save.png"));
		saveProjectAction_->setShortcut(QKeySequence::Save);
		saveProjectAction_->setStatusTip(tr("save the project"));
		connect(saveProjectAction_, SIGNAL(triggered()), this, SLOT(saveProjectAction()));

		saveAsProjectAction_ = new QAction(tr("Save&As"), this);
		saveAsProjectAction_->setIcon(QIcon(":images/SaveAs.png"));
		saveAsProjectAction_->setShortcut(QKeySequence::Save);
		saveAsProjectAction_->setStatusTip(tr("save the project"));
		connect(saveAsProjectAction_, SIGNAL(triggered()), this, SLOT(saveAsProjectAction()));

		//
		// application actions
		//
		exitApplAction_ = new QAction(tr("E&xit"), this);
		exitApplAction_->setShortcut(tr("Ctrl+Q"));
		exitApplAction_->setStatusTip(tr("exit the application"));
		connect(exitApplAction_, SIGNAL(triggered()), this, SLOT(exitApplAction()));

		aboutApplAction_ = new QAction(tr("About"), this);
		aboutApplAction_->setStatusTip(tr("shows the application About box"));
		connect(aboutApplAction_, SIGNAL(triggered()), this, SLOT(aboutApplAction()));

		aboutQtApplAction_ = new QAction(tr("About Qt"), this);
		aboutQtApplAction_->setStatusTip(tr("shows the application Qt About box"));
		connect(aboutQtApplAction_, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	}

	void
	MainWindow::createMenus(void)
	{
		//
		// project menu
		//
		projectMenu_ = menuBar()->addMenu(tr("Project"));
		projectMenu_->addAction(newProjectAction_);
		projectMenu_->addAction(openProjectAction_);
		projectMenu_->addAction(saveProjectAction_);
		projectMenu_->addAction(saveAsProjectAction_);
		projectMenu_->addSeparator();
		projectMenu_->addAction(exitApplAction_);

		//
		// modul menu
		//
		modulMenu_ = menuBar()->addMenu(tr("Modul"));

		//
		// help menu
		//
		menuBar()->addSeparator();
		helpMenu_ = menuBar()->addMenu(tr("&Help"));
		helpMenu_->addAction(aboutApplAction_);
		helpMenu_->addAction(aboutQtApplAction_);
	}

	void
	MainWindow::addModulMenus(void)
	{
		Modul::ModulNames::iterator it;

		for (it = modul_->moduleNames().begin(); it != modul_->moduleNames().end(); it++) {
			QAction* action;
			action = new QAction(tr((*it).c_str()), this);
			//connect(exitApplAction_, SIGNAL(triggered()), this, SLOT(exitApplAction()));

			modulMenu_->addAction(action);
		}
	}

	void
	MainWindow::createToolBars(void)
	{
		//
		// project toolbar
		//
		projectToolBar_ = this->addToolBar(tr("Project"));
		projectToolBar_->addAction(newProjectAction_);
		projectToolBar_->addAction(openProjectAction_);
		projectToolBar_->addAction(saveProjectAction_);
	}

	void
	MainWindow::createStatusBar(void)
	{
		statusBar()->addWidget(new QLabel("status bar"));
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// project actions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	MainWindow::newProjectAction(void)
	{
		// create project window
		projectWindow_ = new ProjectWindow(NULL);
		projectWindow_->modul(modul_);

		// create dock widget
		QDockWidget* dockWidget = new QDockWidget(tr("Project"));
		dockWidget->setObjectName("ProjectName");
		dockWidget->setWidget(projectWindow_);
		dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
		this->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
	}

	void
	MainWindow::openProjectAction(void)
	{
		// FIXME: todo
	}

    void
    MainWindow::saveProjectAction(void)
    {
    	// FIXME: todo
    }

    void
    MainWindow::saveAsProjectAction(void)
    {
    	// FIXME: todo
    }

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// application actions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	MainWindow::exitApplAction(void)
	{
		close();
	}

	void
	MainWindow::aboutApplAction(void)
	{
		// FIXME: todo
		std::cout << "aboutApplAction" << std::endl;
	}

}


int main(int argc, char**argv)
{
	std::cout << "ARGC:" << argc << std::endl;

	QApplication app(argc, argv);
	OpcUaGui::MainWindow mainWindow;
	if (!mainWindow.startup(argc, argv)) {
		return 0;
	}
	mainWindow.resize(400,600);
	mainWindow.show();
	//mainWindow.showMaximized();
	return app.exec();
	return 0;
}


