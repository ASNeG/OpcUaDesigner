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

#include <QApplication>
#include <QCloseEvent>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

namespace OpcUaGui
{

	MainWindow::MainWindow(void)
	: QMainWindow()
	, newProjectAction_(NULL)
	{
		createActions();
		createMenus();
	}

	MainWindow::~MainWindow(void)
	{
	}

	void
	MainWindow::closeEvent(QCloseEvent* event)
	{
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
		connect(newProjectAction_, SIGNAL(triggered()), this, SLOT(openProjectAction()));
	}

	void
	MainWindow::createMenus(void)
	{
		projectMenu_ = menuBar()->addMenu(tr("Project"));
		projectMenu_->addAction(newProjectAction_);
		projectMenu_->addAction(openProjectAction_);
	}

	void
	MainWindow::newProjectAction(void)
	{
		;
	}

	void
	MainWindow::openProjectAction(void)
	{
	}
}


int main(int argc, char**argv)
{
	QApplication app(argc, argv);
	OpcUaGui::MainWindow mainWindow;
	mainWindow.show();
	return app.exec();
	return 0;
}


