/*
   Copyright 2016-2017 Kai Huebl (kai@huebl-sgh.de)

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

#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaGui/Application/ProjectWindow.h"
#include "OpcUaGui/Application/Modul.h"

#include <QWidget>
#include <QHeaderView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
using namespace OpcUaStackCore;

namespace OpcUaGui
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// ModulInfo
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	ModulInfo::ModulInfo(void)
	: modulConfig_(NULL)
	, projectData_()
	, handle_(0)
	, modulName_("")
	{
	}

	ModulInfo::~ModulInfo(void)
	{
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// ProjectWindow
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	ProjectWindow::ProjectWindow(QWidget* parent)
	: QWidget()
	, modul_(NULL)
	, rootItem_(NULL)
	, actItem_(NULL)
	, dataModel_(NULL)
	{
		//
		// create project tree
		//
		projectTree_ = new QTreeWidget();
		projectTree_->header()->close();
		projectTree_->setContextMenuPolicy(Qt::CustomContextMenu);

		//
		// added root item
		//
		ModulInfo* modulInfo = new ModulInfo();
		modulInfo->modulName_ = "Project";
		QVariant v;
		v.setValue(modulInfo);

		rootItem_ = new QTreeWidgetItem(projectTree_);
		rootItem_->setText(0, "Project");
		rootItem_->setData(0, Qt::UserRole, v);
		rootItem_->setIcon(0, QIcon(":images/Project.png"));

		//
		// connections
		//
		connect(
		    projectTree_, SIGNAL(customContextMenuRequested(const QPoint&)),
		    this, SLOT(onCustomContextMenuRequested(const QPoint&))
		);
		connect(
			projectTree_, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),
			this, SLOT(onItemDoubleClicked(QTreeWidgetItem*, int))
		);

		//
		// show project tree
		//
		QVBoxLayout* layout_ = new QVBoxLayout();
		layout_->addWidget(projectTree_);
		setLayout(layout_);
	}

	ProjectWindow::~ProjectWindow(void)
	{
	}

	void
	ProjectWindow::modul(Modul* modul)
	{
		modul_ = modul;
	}

	bool
	ProjectWindow::dataModel(DataModel* dataModel)
	{
		dataModel_ = dataModel;
		return true;
	}

    void
    ProjectWindow::onCustomContextMenuRequested(const QPoint& pos)
    {
    	QMenu menu;

    	// get and check tree widget item
        actItem_ = projectTree_->itemAt(pos);
        if (actItem_ == NULL) {
        	return;
        }

        // get modul configuration
        QVariant v = actItem_->data(0, Qt::UserRole);
        ModulInfo* modulInfo = v.value<ModulInfo*>();
        ModulConfig::SPtr modulConfig = modul_->getModulConfig(modulInfo->modulName_);
        if (modulConfig.get() == NULL) {
        	return;
        }

        // create menu
        createNewMenu(menu, modulConfig.get());
        createOpenMenu(menu, modulConfig.get());
        createSaveMenu(menu, modulInfo);
        createSaveAsMenu(menu, modulInfo);
        createRenameMenu(menu, modulInfo);
        createCloseMenu(menu, modulInfo);
        createDeleteMenu(menu, modulInfo);

        // show menu
        menu.exec(projectTree_->viewport()->mapToGlobal(pos));
    }

    void
    ProjectWindow::createNewMenu(QMenu& menu, ModulConfig* modulConfig)
    {
        if (!modulConfig->modulChilds_.empty()) {
        	ModulConfig::ModulChilds::iterator it1;
        	QMenu* newMenu = new QMenu();
        	menu.addMenu(newMenu);
        	newMenu->setTitle(tr("New"));
        	newMenu->setIcon(QIcon(":images/New.png"));

        	for (it1 = modulConfig->modulChilds_.begin(); it1 != modulConfig->modulChilds_.end(); it1++) {
                ModulConfig::SPtr modulConfigChild = modul_->getModulConfig(*it1);
                if (modulConfigChild.get() == NULL) {
                	continue;
                }

        		// create modul config value
        		QVariant v;
        		v.setValue((void*)modulConfigChild.get());

        		QAction* action = new QAction(tr((*it1).c_str()), this);
        		action->setIcon(*modulConfigChild->modulLibraryInterface_->libModulIcon());
        		action->setData(v);
        		newMenu->addAction(action);
        		connect(action, SIGNAL(triggered()), this, SLOT(projectNewAction()));
        	}
        }
    }

    void
    ProjectWindow::createOpenMenu(QMenu& menu, ModulConfig* modulConfig)
    {
        if (!modulConfig->modulChilds_.empty()) {
        	ModulConfig::ModulChilds::iterator it1;
        	QMenu* openMenu = new QMenu();
        	menu.addMenu(openMenu);
        	openMenu->setTitle(tr("Open"));
        	openMenu->setIcon(QIcon(":images/Open.png"));

        	for (it1 = modulConfig->modulChilds_.begin(); it1 != modulConfig->modulChilds_.end(); it1++) {
                ModulConfig::SPtr modulConfigChild = modul_->getModulConfig(*it1);
                if (modulConfigChild.get() == NULL) {
                	continue;
                }

        		// create modul config value
        		QVariant v;
        		v.setValue((void*)modulConfigChild.get());

        		QAction* action = new QAction(tr((*it1).c_str()), this);
        		action->setIcon(*modulConfigChild->modulLibraryInterface_->libModulIcon());
        		action->setData(v);
        	    openMenu->addAction(action);
        		connect(action, SIGNAL(triggered()), this, SLOT(projectOpenAction()));
        	}
        }
    }

    void
    ProjectWindow::createSaveMenu(QMenu& menu, ModulInfo* modulInfo)
    {
    	if (modulInfo->handle_ == 0) return;

    	QVariant v;
    	v.setValue((void*)modulInfo);

    	QAction* action = new QAction("Save", this);
    	action->setIcon(QIcon(":images/Save.png"));
    	action->setData(v);
    	menu.addAction(action);
    	connect(action, SIGNAL(triggered()), this, SLOT(projectSaveAction()));
    }

    void
    ProjectWindow::createSaveAsMenu(QMenu& menu, ModulInfo* modulInfo)
    {
    	if (modulInfo->handle_ == 0) return;

    	QVariant v;
    	v.setValue((void*)modulInfo);

    	QAction* action = new QAction("SaveAs", this);
    	action->setIcon(QIcon(":images/SaveAs.png"));
    	action->setData(v);
    	menu.addAction(action);
    	connect(action, SIGNAL(triggered()), this, SLOT(projectSaveAsAction()));
    }

    void
    ProjectWindow::createRenameMenu(QMenu& menu, ModulInfo* modulInfo)
    {
       	if (modulInfo->handle_ == 0) return;

        	QVariant v;
        	v.setValue((void*)modulInfo);

        	QAction* action = new QAction("Rename", this);
        	action->setIcon(QIcon(":images/Edit.png"));
        	action->setData(v);
        	menu.addAction(action);
        	connect(action, SIGNAL(triggered()), this, SLOT(projectRenameAction()));
    }

    void
    ProjectWindow::createCloseMenu(QMenu& menu, ModulInfo* modulInfo)
    {
       	if (modulInfo->handle_ == 0) return;

        	QVariant v;
        	v.setValue((void*)modulInfo);

        	QAction* action = new QAction("Close", this);
        	action->setIcon(QIcon(":images/Close.png"));
        	action->setData(v);
        	menu.addAction(action);
        	connect(action, SIGNAL(triggered()), this, SLOT(projectCloseAction()));
    }

    void
    ProjectWindow::createDeleteMenu(QMenu& menu, ModulInfo* modulInfo)
    {
    	if (modulInfo->handle_ == 0) return;

    	QVariant v;
    	v.setValue((void*)modulInfo);

    	QAction* action = new QAction("Delete", this);
    	action->setIcon(QIcon(":images/Delete.png"));
    	action->setData(v);
    	menu.addAction(action);
    	connect(action, SIGNAL(triggered()), this, SLOT(projectDeleteAction()));
    }

    void
    ProjectWindow::projectNewAction(void)
    {
    	// find modul configuration
    	QAction* action = (QAction*)sender();
    	QVariant a = action->data();
    	ModulConfig* modulConfig = (ModulConfig*)a.value<void*>();

    	// get modul file name
    	QString dialogText = QString("Create new project: select %1 file").arg(modulConfig->modulName_.c_str());
    	QString fileExtension = QString("Dokumente (*.%1)").arg(modulConfig->modulLibraryInterface_->getFileExtension().c_str());
		QString fileName = QFileDialog::getSaveFileName(
			NULL, dialogText, QDir::homePath(), fileExtension
		);
		if (fileName.isNull()) {
			return;
		}

		// use file name as project name
		QStringList parts1 = fileName.split("/");
		QString projectName = parts1.at(parts1.size()-1);
		projectName.replace(modulConfig->modulLibraryInterface_->getFileExtension().c_str(), "");

		// check if project already exist
		if (dataModel_->existProjectData(projectName.toStdString())) {
			uint32_t idx = 1;
			do {
				QString newProjectName = QString("%1_%2").arg(projectName).arg(idx);
				if (!dataModel_->existProjectData(newProjectName.toStdString())) {
					projectName = newProjectName;
					break;
				}
				idx++;
			} while (true);
		}

		// open modul window
		uint32_t handle;
		bool success = modulConfig->modulLibraryInterface_->projectNew(
			handle,
			projectName.toStdString(),
			fileName.toStdString()
		);
		if (!success) {
			QMessageBox msgBox;
			msgBox.setText("create new project error");
			msgBox.exec();
			return;
		}

		// create new data model entry
		ProjectData::SPtr projectData = constructSPtr<ProjectData>();
		projectData->projectName(projectName.toStdString());
		projectData->projectFile(fileName.toStdString());
		dataModel_->setProjectData(projectName.toStdString(), projectData);

    	// insert new modul window item into project window
		ModulInfo* modulInfo = new ModulInfo();
		modulInfo->modulName_ = modulConfig->modulName_;
		modulInfo->modulConfig_ = modulConfig;
		modulInfo->handle_ = handle;
		modulInfo->projectData_ = projectData;
		QVariant v;
		v.setValue(modulInfo);

		QTreeWidgetItem* item;
		item = new QTreeWidgetItem(actItem_);
		item->setText(0, projectName);
		item->setData(0, Qt::UserRole, v);
		item->setIcon(0, *modulConfig->modulLibraryInterface_->libModulIcon());
		actItem_->setExpanded(true);
    }

    void
    ProjectWindow::projectOpenAction(void)
    {
    	// find modul configuration
    	QAction* action = (QAction*)sender();
    	QVariant a = action->data();
    	ModulConfig* modulConfig = (ModulConfig*)a.value<void*>();

    	// get modul file name
    	QString dialogText = QString("Open existing project: select %1 file").arg(modulConfig->modulName_.c_str());
    	QString fileExtension = QString("Dokumente (*.%1)").arg(modulConfig->modulLibraryInterface_->getFileExtension().c_str());
		QString fileName = QFileDialog::getOpenFileName(
			NULL, dialogText, QDir::homePath(), fileExtension
		);
		if (fileName.isNull()) {
			return;
		}

		// use file name as project name
		QStringList parts1 = fileName.split("/");
		QString projectName = parts1.at(parts1.size()-1);
		projectName.replace(modulConfig->modulLibraryInterface_->getFileExtension().c_str(), "");

		// check if project already exist
		if (dataModel_->existProjectData(projectName.toStdString())) {
			uint32_t idx = 1;
			do {
				QString newProjectName = QString("%1_%2").arg(projectName).arg(idx);
				if (!dataModel_->existProjectData(newProjectName.toStdString())) {
					projectName = newProjectName;
					break;
				}
				idx++;
			} while (true);
		}

		// open modul window
		uint32_t handle;
		bool success = modulConfig->modulLibraryInterface_->projectOpen(
			handle,
			projectName.toStdString(),
			fileName.toStdString()
		);
		if (!success) {
			QMessageBox msgBox;
			msgBox.setText("open existing project error");
			msgBox.exec();
			return;
		}

		// create new data model entry
		ProjectData::SPtr projectData = constructSPtr<ProjectData>();
		projectData->projectName(projectName.toStdString());
		projectData->projectFile(fileName.toStdString());
		dataModel_->setProjectData(projectName.toStdString(), projectData);

    	// insert new modul window item into project window
		ModulInfo* modulInfo = new ModulInfo();
		modulInfo->modulName_ = modulConfig->modulName_;
		modulInfo->modulConfig_ = modulConfig;
		modulInfo->handle_ = handle;
		modulInfo->projectData_ = projectData;
		QVariant v;
		v.setValue(modulInfo);

		QTreeWidgetItem* item;
		item = new QTreeWidgetItem(actItem_);
		item->setText(0, projectName);
		item->setData(0, Qt::UserRole, v);
		item->setIcon(0, *modulConfig->modulLibraryInterface_->libModulIcon());
		actItem_->setExpanded(true);
    }

    void
    ProjectWindow::projectSaveAction(void)
    {
    	// find modul configuration
    	QAction* action = (QAction*)sender();
    	QVariant a = action->data();
    	ModulInfo* modulInfo = (ModulInfo*)a.value<void*>();
    	ModulConfig* modulConfig = modulInfo->modulConfig_;

        // save project
        bool rc = modulConfig->modulLibraryInterface_->projectSave(modulInfo->handle_);
        if (!rc) {
			QMessageBox msgBox;
			msgBox.setText("save project error");
			msgBox.exec();
        	return;
        }
    }

    void
    ProjectWindow::projectSaveAsAction(void)
    {
    	// find modul configuration
    	QAction* action = (QAction*)sender();
    	QVariant a = action->data();
    	ModulInfo* modulInfo = (ModulInfo*)a.value<void*>();
    	ModulConfig* modulConfig = modulInfo->modulConfig_;

    	// get modul file name
    	QString dialogText = QString("Save project: select %1 file").arg(modulConfig->modulName_.c_str());
    	QString fileExtension = QString("Dokumente (*.%1)").arg(modulConfig->modulLibraryInterface_->getFileExtension().c_str());
		QString fileName = QFileDialog::getSaveFileName(
			NULL, dialogText, QDir::homePath(), fileExtension
		);
		if (fileName.isNull()) {
			return;
		}

		// use file name as project name
		QStringList parts1 = fileName.split("/");
		QString projectName = parts1.at(parts1.size()-1);
		projectName.replace(modulConfig->modulLibraryInterface_->getFileExtension().c_str(), "");

        // save project
        bool rc = modulConfig->modulLibraryInterface_->projectSaveAs(modulInfo->handle_, fileName.toStdString());
        if (!rc) {
			QMessageBox msgBox;
			msgBox.setText("saveAs project error");
			msgBox.exec();
        	return;
        }

		// update project data
		ProjectData::SPtr projectData = modulInfo->projectData_;
		projectData->projectFile(fileName.toStdString());
    }

    void
    ProjectWindow::projectRenameAction(void)
    {
    	// find modul configuration
    	QAction* action = (QAction*)sender();
    	QVariant a = action->data();
    	ModulInfo* modulInfo = (ModulInfo*)a.value<void*>();
    	ModulConfig* modulConfig = modulInfo->modulConfig_;
    	ProjectData::SPtr projectData = modulInfo->projectData_;

    }

    void
    ProjectWindow::projectCloseAction(void)
    {
    	// find modul configuration
    	QAction* action = (QAction*)sender();
    	QVariant a = action->data();
    	ModulInfo* modulInfo = (ModulInfo*)a.value<void*>();
    	ModulConfig* modulConfig = modulInfo->modulConfig_;

        // close modul
        bool rc = modulConfig->modulLibraryInterface_->projectClose(modulInfo->handle_);
        if (!rc) return;
        modulInfo->handle_ = 0;
    }

    void
    ProjectWindow::projectDeleteAction(void)
    {
    	// find modul configuration
    	QAction* action = (QAction*)sender();
    	QVariant a = action->data();
    	ModulInfo* modulInfo = (ModulInfo*)a.value<void*>();
    	ModulConfig* modulConfig = modulInfo->modulConfig_;

        // close modul
        modulConfig->modulLibraryInterface_->projectClose(modulInfo->handle_);

    	// delete item
        dataModel_->delProjectData(modulInfo->projectData_->projectName());
    	delete modulInfo;
    	delete actItem_->parent()->takeChild(actItem_->parent()->indexOfChild(actItem_));
    }

    void
    ProjectWindow::onItemDoubleClicked(QTreeWidgetItem* treeWidgetItem, int column)
    {
    	// find modul configuration
	    QVariant v = actItem_->data(0, Qt::UserRole);
    	ModulInfo* modulInfo = v.value<ModulInfo*>();
    	if (modulInfo == NULL) {
    		Log(Error, "onItemDoubleClicked: modulInfo == NULL");
    		return;
    	}
    	ModulConfig* modulConfig = modulInfo->modulConfig_;
    	if (modulInfo->handle_ != 0) {
    		Log(Error, "onItemDoubleClicked: modulInfo->handle_ != 0");
    		return;
    	}

		// open modul window
		uint32_t handle;
		bool success = modulConfig->modulLibraryInterface_->projectOpen(
			handle,
			modulInfo->projectData_->projectName(),
			modulInfo->projectData_->projectFile()
		);
		if (!success) {
	   		Log(Error, "onItemDoubleClicked: projectOpen error");
			return;
		}
		modulInfo->handle_ = handle;
    }

}


