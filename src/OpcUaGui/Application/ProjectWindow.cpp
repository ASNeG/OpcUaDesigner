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

#include "OpcUaGui/Application/ProjectWindow.h"
#include "OpcUaGui/Application/Modul.h"

#include <QWidget>
#include <QHeaderView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QMenu>

namespace OpcUaGui
{

	ProjectWindow::ProjectWindow(QWidget* parent)
	: QWidget()
	, modul_(NULL)
	{
		// create project tree
		projectTree_ = new QTreeWidget();
		projectTree_->header()->close();
		projectTree_->setContextMenuPolicy(Qt::CustomContextMenu);

		// added root item
		ModulInfo* modulInfo = new ModulInfo();
		modulInfo->type_ = "Project";
		QVariant v;
		v.setValue(modulInfo);

		rootItem_ = new QTreeWidgetItem(projectTree_);
		rootItem_->setText(0, "Project");
		rootItem_->setData(0, Qt::UserRole, v);
		rootItem_->setIcon(0, QIcon(":images/Project.png"));
		connect(
		    projectTree_, SIGNAL(customContextMenuRequested(const QPoint&)),
		    this, SLOT(onCustomContextMenuRequested(const QPoint&))
		);

		// show project tree
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

    void
    ProjectWindow::onCustomContextMenuRequested(const QPoint& pos)
    {
        QTreeWidgetItem* item = projectTree_->itemAt(pos);

        if (item == NULL) {
        	return;
        }

        // add Menu
        QMenu* addMenu = new QMenu();
        addMenu->setTitle(tr("Add"));
        addMenu->addAction("xxxx1");
        addMenu->addAction("xxxx2");

        // show menu
        QMenu menu;
        menu.addMenu(addMenu);
        menu.exec(projectTree_->viewport()->mapToGlobal(pos));
    }

}


