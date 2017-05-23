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
#include "OpcUaGui/Application/NodeInfo.h"

#include <QWidget>
#include <QHeaderView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QLineEdit>
#include <QInputDialog>
using namespace OpcUaStackCore;

namespace OpcUaGui
{

	ProjectWindow::ProjectWindow(QWidget* parent)
	: QWidget()
	, handle_(0)
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
		// create new data model entry
		ApplicationData::SPtr applicationData = constructSPtr<ApplicationData>();
		applicationData->modulName("Project");

		NodeInfo* nodeInfo = new NodeInfo();
		nodeInfo->applicationData(applicationData);
		QVariant v;
		v.setValue(nodeInfo);

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
		showModel();
		return true;
	}

	void
	ProjectWindow::closeModel(void)
	{
		actItem_ = NULL;
		projectCloseAllAction(rootItem_);
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
        NodeInfo* nodeInfo = v.value<NodeInfo*>();
        ModulConfig::SPtr modulConfig = modul_->getModulConfig(nodeInfo->applicationData()->modulName());
        if (modulConfig.get() == NULL) {
        	return;
        }

        // create menu
        createNewMenu(menu, modulConfig.get());
        createOpenMenu(menu, modulConfig.get());
        createSaveMenu(menu, nodeInfo);
        createSaveAsMenu(menu, nodeInfo);
        createRenameMenu(menu, nodeInfo);
        createCloseMenu(menu, nodeInfo);
        createDeleteMenu(menu, nodeInfo);

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

        		// create node info
                NodeInfo* nodeInfo = new NodeInfo();
                nodeInfo->modulConfig(modulConfigChild);
        		QVariant v;
        		v.setValue((void*)nodeInfo);

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

           		// create node info
                    NodeInfo* nodeInfo = new NodeInfo();
                    nodeInfo->modulConfig(modulConfigChild);
            		QVariant v;
            		v.setValue((void*)nodeInfo);

        		QAction* action = new QAction(tr((*it1).c_str()), this);
        		action->setIcon(*modulConfigChild->modulLibraryInterface_->libModulIcon());
        		action->setData(v);
        	    openMenu->addAction(action);
        		connect(action, SIGNAL(triggered()), this, SLOT(projectOpenAction()));
        	}
        }
    }

    void
    ProjectWindow::createSaveMenu(QMenu& menu, NodeInfo* nodeInfo)
    {
    	if (nodeInfo->handle() == 0) return;

    	QVariant v;
    	v.setValue((void*)nodeInfo);

    	QAction* action = new QAction("Save", this);
    	action->setIcon(QIcon(":images/Save.png"));
    	action->setData(v);
    	menu.addAction(action);
    	connect(action, SIGNAL(triggered()), this, SLOT(projectSaveAction()));
    }

    void
    ProjectWindow::createSaveAsMenu(QMenu& menu, NodeInfo* nodeInfo)
    {
    	if (nodeInfo->handle() == 0) return;

    	QVariant v;
    	v.setValue((void*)nodeInfo);

    	QAction* action = new QAction("SaveAs", this);
    	action->setIcon(QIcon(":images/SaveAs.png"));
    	action->setData(v);
    	menu.addAction(action);
    	connect(action, SIGNAL(triggered()), this, SLOT(projectSaveAsAction()));
    }

    void
    ProjectWindow::createRenameMenu(QMenu& menu, NodeInfo* nodeInfo)
    {
       	if (nodeInfo->handle() == 0) return;

        	QVariant v;
        	v.setValue((void*)nodeInfo);

        	QAction* action = new QAction("Rename", this);
        	action->setIcon(QIcon(":images/Edit.png"));
        	action->setData(v);
        	menu.addAction(action);
        	connect(action, SIGNAL(triggered()), this, SLOT(projectRenameAction()));
    }

    void
    ProjectWindow::createCloseMenu(QMenu& menu, NodeInfo* nodeInfo)
    {
       	if (nodeInfo->handle() == 0) return;

        	QVariant v;
        	v.setValue((void*)nodeInfo);

        	QAction* action = new QAction("Close", this);
        	action->setIcon(QIcon(":images/Close.png"));
        	action->setData(v);
        	menu.addAction(action);
        	connect(action, SIGNAL(triggered()), this, SLOT(projectCloseAction()));
    }

    void
    ProjectWindow::createDeleteMenu(QMenu& menu, NodeInfo* nodeInfo)
    {
    	if (nodeInfo->handle() == 0) return;

    	QVariant v;
    	v.setValue((void*)nodeInfo);

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
    	NodeInfo* nf = (NodeInfo*)a.value<void*>();
    	ModulConfig::SPtr modulConfig = nf->modulConfig();

    	// get modul file name
    	QString dialogText = QString("Create new project: select %1 file").arg(modulConfig->modulName_.c_str());
    	QString fileSuffix = modulConfig->modulLibraryInterface_->getFileExtension().c_str();
    	QString fileExtension = QString("Dokumente (*.%1)").arg(fileSuffix);
    	QString fileName = QFileDialog::getSaveFileName(
			NULL, dialogText, QDir::homePath(), fileExtension
		);
		if (fileName.isNull()) {
			return;
		}
		if (!fileName.endsWith(fileSuffix)) {
			fileName = QString("%1.%2").arg(fileName).arg(fileSuffix);
		}

		// use file name as project name
		QStringList parts = fileName.split("/");
		QString applicationName = parts.at(parts.size()-1);
		applicationName.replace(QString(".%1").arg(fileSuffix), "");

		// check if project already exist
		if (dataModel_->existApplicationData(applicationName.toStdString())) {
			uint32_t idx = 1;
			do {
				QString newProjectName = QString("%1_%2").arg(applicationName).arg(idx);
				if (!dataModel_->existApplicationData(newProjectName.toStdString())) {
					applicationName = newProjectName;
					break;
				}
				idx++;
			} while (true);
		}

		// open modul window
		handle_++;
		bool success = modulConfig->modulLibraryInterface_->projectNew(
			handle_,
			applicationName.toStdString(),
			fileName.toStdString()
		);
		if (!success) {
			QMessageBox msgBox;
			msgBox.setText("create new project error");
			msgBox.exec();
			return;
		}

		// create new data model entry
		ApplicationData::SPtr applicationData = constructSPtr<ApplicationData>();
		applicationData->applicationName(applicationName.toStdString());
		applicationData->parentApplicationName(actItem_->text(0).toStdString());
		applicationData->projectFile(fileName.toStdString());
		applicationData->modulName(modulConfig->modulName_);
		dataModel_->setApplicationData(applicationName.toStdString(), applicationData);

    	// insert new modul window item into project window
		NodeInfo* nodeInfo = new NodeInfo();
		nodeInfo->modulConfig(modulConfig);
		nodeInfo->handle(handle_);
		nodeInfo->applicationData(applicationData);
		QVariant v;
		v.setValue(nodeInfo);

		QTreeWidgetItem* item;
		item = new QTreeWidgetItem(actItem_);
		item->setText(0, applicationName);
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
    	NodeInfo* nf = (NodeInfo*)a.value<void*>();
    	ModulConfig::SPtr modulConfig = nf->modulConfig();

    	// get modul file name
    	QString dialogText = QString("Open existing project: select %1 file").arg(modulConfig->modulName_.c_str());
    	QString fileSuffix = modulConfig->modulLibraryInterface_->getFileExtension().c_str();
    	QString fileExtension = QString("Dokumente (*.%1)").arg(fileSuffix);
		QString fileName = QFileDialog::getOpenFileName(
			NULL, dialogText, QDir::homePath(), fileExtension
		);
		if (fileName.isNull()) {
			return;
		}

		// use file name as project name
		QStringList part = fileName.split("/");
		QString applicationName = part.at(part.size()-1);
		applicationName.replace(QString(".%1").arg(fileSuffix), "");

		// check if project already exist
		if (dataModel_->existApplicationData(applicationName.toStdString())) {
			uint32_t idx = 1;
			do {
				QString newProjectName = QString("%1_%2").arg(applicationName).arg(idx);
				if (!dataModel_->existApplicationData(newProjectName.toStdString())) {
					applicationName = newProjectName;
					break;
				}
				idx++;
			} while (true);
		}

		// open modul window
		handle_++;
		bool success = modulConfig->modulLibraryInterface_->projectOpen(
			handle_,
			applicationName.toStdString(),
			fileName.toStdString()
		);
		if (!success) {
			QMessageBox msgBox;
			msgBox.setText("open existing project error");
			msgBox.exec();
			return;
		}

		// create new data model entry
		ApplicationData::SPtr applicationData = constructSPtr<ApplicationData>();
		applicationData->applicationName(applicationName.toStdString());
		applicationData->parentApplicationName(actItem_->text(0).toStdString());
		applicationData->projectFile(fileName.toStdString());
		applicationData->modulName(modulConfig->modulName_);
		dataModel_->setApplicationData(applicationName.toStdString(), applicationData);

    	// insert new modul window item into project window
		NodeInfo* nodeInfo = new NodeInfo();
		nodeInfo->modulConfig(modulConfig);
		nodeInfo->handle(handle_);
		nodeInfo->applicationData(applicationData);
		QVariant v;
		v.setValue(nodeInfo);

		QTreeWidgetItem* item;
		item = new QTreeWidgetItem(actItem_);
		item->setText(0, applicationName);
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
    	NodeInfo* nodeInfo = (NodeInfo*)a.value<void*>();
    	ModulConfig::SPtr modulConfig = nodeInfo->modulConfig();

        // save project
        bool rc = modulConfig->modulLibraryInterface_->projectSave(nodeInfo->handle());
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
    	NodeInfo* nodeInfo = (NodeInfo*)a.value<void*>();
    	ModulConfig::SPtr modulConfig = nodeInfo->modulConfig();

    	// get modul file name
    	QString dialogText = QString("Save project: select %1 file").arg(modulConfig->modulName_.c_str());
    	QString fileSuffix = modulConfig->modulLibraryInterface_->getFileExtension().c_str();
    	QString fileExtension = QString("Dokumente (*.%1)").arg(fileSuffix);
		QString fileName = QFileDialog::getSaveFileName(
			NULL, dialogText, QDir::homePath(), fileExtension
		);
		if (fileName.isNull()) {
			return;
		}
		if (!fileName.endsWith(fileSuffix)) {
			fileName = QString("%1.%2").arg(fileName).arg(fileSuffix);
		}

		// use file name as project name
		QStringList parts1 = fileName.split("/");
		QString applicationName = parts1.at(parts1.size()-1);
		applicationName.replace(QString(".%1").arg(fileSuffix), "");

        // save project
        bool rc = modulConfig->modulLibraryInterface_->projectSaveAs(nodeInfo->handle(), fileName.toStdString());
        if (!rc) {
			QMessageBox msgBox;
			msgBox.setText("saveAs project error");
			msgBox.exec();
        	return;
        }

		// update project data
		ApplicationData::SPtr applicationData = nodeInfo->applicationData();
		applicationData->projectFile(fileName.toStdString());
    }

    void
    ProjectWindow::projectRenameAction(void)
    {
    	// find modul configuration
    	QAction* action = (QAction*)sender();
    	QVariant a = action->data();
    	NodeInfo* nodeInfo = (NodeInfo*)a.value<void*>();
    	ModulConfig::SPtr modulConfig = nodeInfo->modulConfig();
    	ApplicationData::SPtr applicationData = nodeInfo->applicationData();

    	// input project name
    	bool ok;
    	QString newProjectName = QInputDialog::getText(
    		this,
    		"Project Name Dialog",
    	    "Set new project name:",
    	    QLineEdit::Normal,
    	    QDir::home().dirName(),
    	    &ok
    	);
    	if (!ok || newProjectName.isEmpty()) {
    		return;
    	}

		// check if project already exist
		if (dataModel_->existApplicationData(newProjectName.toStdString())) {
			QMessageBox msgBox;
			msgBox.setText("Project name already exist in data model");
			msgBox.exec();
			return;
		}

		// update project data
		dataModel_->delApplicationData(applicationData->applicationName());
		applicationData->applicationName(newProjectName.toStdString());
		dataModel_->setApplicationData(applicationData->applicationName(), applicationData);
    }

    void
    ProjectWindow::projectCloseAction(void)
    {
    	// find modul configuration
    	QAction* action = (QAction*)sender();
    	QVariant a = action->data();
    	NodeInfo* nodeInfo = (NodeInfo*)a.value<void*>();
    	ModulConfig::SPtr modulConfig = nodeInfo->modulConfig();

    	// FIXME: we must save the open application at this point...

        // close modul
        bool rc = modulConfig->modulLibraryInterface_->projectClose(nodeInfo->handle());
        if (!rc) return;
        nodeInfo->handle(0);
    }

    void
    ProjectWindow::projectCloseAllAction(QTreeWidgetItem* item)
    {
    	uint32_t childCount = item->childCount();
    	for (uint32_t idx=0; idx<childCount; idx++) {
    		projectCloseAllAction(item->child(idx));
    	}

        // get modul configuration
         QVariant v = item->data(0, Qt::UserRole);
         NodeInfo* nodeInfo = v.value<NodeInfo*>();
         if (nodeInfo->handle() == 0) return;
         ModulConfig::SPtr modulConfig = modul_->getModulConfig(nodeInfo->applicationData()->modulName());
         if (modulConfig.get() == NULL) {
         	return;
         }

         // FIXME: we must save the open application at this point...

         // close modul
         bool rc = modulConfig->modulLibraryInterface_->projectClose(nodeInfo->handle());
         if (!rc) return;
         nodeInfo->handle(0);
    }

    void
    ProjectWindow::projectDeleteAction(void)
    {
    	// find modul configuration
    	QAction* action = (QAction*)sender();
    	QVariant a = action->data();
    	NodeInfo* nodeInfo = (NodeInfo*)a.value<void*>();
    	ModulConfig::SPtr modulConfig = nodeInfo->modulConfig();

        // close modul
        modulConfig->modulLibraryInterface_->projectClose(nodeInfo->handle());

    	// delete item
        dataModel_->delApplicationData(nodeInfo->applicationData()->applicationName());
    	delete nodeInfo;
    	delete actItem_->parent()->takeChild(actItem_->parent()->indexOfChild(actItem_));
    }

    void
    ProjectWindow::onItemDoubleClicked(QTreeWidgetItem* treeWidgetItem, int column)
    {
    	// set actual item
    	actItem_ = treeWidgetItem;

    	// find modul configuration
	    QVariant v = actItem_->data(0, Qt::UserRole);
    	NodeInfo* nodeInfo = v.value<NodeInfo*>();
    	if (nodeInfo == NULL) {
    		Log(Error, "onItemDoubleClicked: nodeInfo == NULL");
    		return;
    	}
    	ModulConfig::SPtr modulConfig = nodeInfo->modulConfig();
    	if (nodeInfo->handle() != 0) {
    		Log(Error, "onItemDoubleClicked: nodeInfo->handle() != 0");
    		return;
    	}

		// open modul window
		handle_++;
		bool success = modulConfig->modulLibraryInterface_->projectOpen(
			handle_,
			nodeInfo->applicationData()->applicationName(),
			nodeInfo->applicationData()->projectFile()
		);
		if (!success) {
	   		Log(Error, "onItemDoubleClicked: projectOpen error");
			return;
		}
		nodeInfo->handle(handle_);
    }

    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    //
    // private functions
    //
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    void
    ProjectWindow::showModel(void)
    {
    	std::vector<std::string>::iterator it;
    	std::vector<std::string> applicationNameVec;
    	dataModel_->getApplicationNameVec(applicationNameVec);

    	for (it = applicationNameVec.begin(); it != applicationNameVec.end(); it++) {
    		std::string applicationName = *it;

    		// get application data
    		ApplicationData::SPtr applicationData;
    		dataModel_->getApplicationData(applicationName, applicationData);

      		// find modul configuration
        	ModulConfig::SPtr modulConfig;
        	modulConfig = modul_->getModulConfig(applicationData->modulName());
        	if (modulConfig.get() == NULL) {
        		Log(Error, "cannot show project, because modul not loaded")
        			.parameter("ModulName", applicationData->modulName())
        			.parameter("ApplicationName", applicationName);
        		continue;
        	}

        	// find parent item
        	QList<QTreeWidgetItem*> items;
        	items = projectTree_->findItems(QString(applicationData->parentApplicationName().c_str()), Qt::MatchExactly);
        	if (items.size() < 1) {
        		Log(Error, "no parent item exist")
        			.parameter("Item", applicationData->applicationName())
        			.parameter("ParentItem", applicationData->parentApplicationName());
        		continue;
        	}
        	actItem_ = items.at(0);

        	// insert new modul window item into project window
    		NodeInfo* nodeInfo = new NodeInfo();
    		nodeInfo->modulConfig(modulConfig);
    		nodeInfo->handle(0);
    		nodeInfo->applicationData(applicationData);
    		QVariant v;
    		v.setValue(nodeInfo);

    		QTreeWidgetItem* item;
    		item = new QTreeWidgetItem(actItem_);
    		item->setText(0, QString(applicationData->applicationName().c_str()));
    		item->setData(0, Qt::UserRole, v);
    		item->setIcon(0, *modulConfig->modulLibraryInterface_->libModulIcon());
    		actItem_->setExpanded(true);
    	}
    }

}


