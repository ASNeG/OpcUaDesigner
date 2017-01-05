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

#include <QWidget>
#include <QHeaderView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

namespace OpcUaGui
{

	ProjectWindow::ProjectWindow(QWidget* parent)
	: QWidget()
	{
		// create project tree
		projectTree_ = new QTreeWidget();
		projectTree_->header()->close();

		// added root item
		rootItem_ = new QTreeWidgetItem(projectTree_);
		rootItem_->setText(0, "Project");
		rootItem_->setIcon(0, QIcon(":images/Project.png"));
		addContextMenu("Project", rootItem_);

		// show project tree
		QVBoxLayout* layout_ = new QVBoxLayout();
		layout_->addWidget(projectTree_);
		this->setLayout(layout_);
	}

	ProjectWindow::~ProjectWindow(void)
	{
	}

	void
	ProjectWindow::addContextMenu(const std::string modulType, QTreeWidgetItem* rootItem)
	{
		// FIXME: todo
	}

}


