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

#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QToolBar>

#include "OpcUaNodeSetModul/Dialog/NamespaceManagerDialog.h"

namespace OpcUaNodeSet
{


	NamespaceManagerDialog::NamespaceManagerDialog(DataModel* dataModel)
	: QDialog()
	, dataModel_(dataModel)
	{
		setWindowTitle(QString("Namespace Manager"));

		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		//
		// table tool bar
		//
		createTableActions();
		tableToolBar_ = new QToolBar();
		tableToolBar_->addAction(addRowAction_);
		vBoxLayout->addWidget(tableToolBar_);

		//
		// create table widget
		//
		namespaceTable_ = new QTableWidget(0,2);
		namespaceTable_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		writeHeader();
		writeData();
		vBoxLayout->addWidget(namespaceTable_);

		//
		// signal - slot
		//
		connect(
			namespaceTable_, SIGNAL(cellChanged(int, int)),
			this, SLOT(onCellChanged(int, int))
		);
		connect(
			namespaceTable_, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)),
			this, SLOT(onCurrentItemChanged(QTableWidgetItem*, QTableWidgetItem*))
		);

		setLayout(vBoxLayout);
	}

	NamespaceManagerDialog::~NamespaceManagerDialog(void)
	{
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// dialog slots
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	NamespaceManagerDialog::onAddRowAction(void)
	{
		dataModel_->nodeSetNamespace().addNewGlobalNamespace("NewNamespace");
		writeHeader();
		writeData();
	}

	void
	NamespaceManagerDialog::onCellChanged(int row, int column)
	{
		std::cout << "CellChanged - " << row << " " << column << std::endl;
	}

	void
	NamespaceManagerDialog::onCurrentItemChanged(QTableWidgetItem* newItem, QTableWidgetItem* oldItem)
	{
		std::string oldString = "";
		std::string newString = "";
		if (oldItem != NULL) oldString = oldItem->text().toStdString();
		if (newItem != NULL) newString = newItem->text().toStdString();
		std::cout << "ItemChanged: " << oldString << " - " <<  newString << std::endl;
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	NamespaceManagerDialog::createTableActions(void)
	{
		addRowAction_ = new QAction("Add table row", this);
		addRowAction_->setIcon(QIcon(":images/Add.png"));
		connect(addRowAction_, SIGNAL(triggered()), this, SLOT(onAddRowAction()));
	}

	void
	NamespaceManagerDialog::writeHeader(void)
	{
		QStringList headerLabels;

		// reset table
		namespaceTable_->setColumnCount(0);
		namespaceTable_->setRowCount(0);

		// create table header
		namespaceTable_->setColumnCount(3);
		headerLabels << "Idx" << "Visible" << "Namespace";
		namespaceTable_->setHorizontalHeaderLabels(headerLabels);
	}

	void
	NamespaceManagerDialog::writeData(void)
	{
		NamespaceVec::iterator it;
		NamespaceVec& namespaceVec = dataModel_->nodeSetNamespace().globalNamespaceVec();

		for (uint32_t row = 0; row < namespaceVec.size(); row++) {
			QTableWidgetItem* item;

			// added new row to table
			namespaceTable_->insertRow(namespaceTable_->rowCount());

			// index
			item = new QTableWidgetItem();
			item->setText(QString("%1").arg(row));
			item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			namespaceTable_->setItem(row, 0, item);

			// visible
			bool isVisible = dataModel_->namespaceVisible(namespaceVec[row]);
			item = new QTableWidgetItem();
			item->data(Qt::CheckStateRole);
			item->setCheckState(isVisible ? Qt::Checked : Qt::Unchecked);
			if (row == 0) item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			namespaceTable_->setItem(row, 1, item);

			// namespace name
			item = new QTableWidgetItem();
			item->setText(QString(namespaceVec[row].c_str()));
			if (row == 0) item->setFlags(item->flags() ^ Qt::ItemIsEditable);
			namespaceTable_->setItem(row, 2, item);
		}
	}

}


