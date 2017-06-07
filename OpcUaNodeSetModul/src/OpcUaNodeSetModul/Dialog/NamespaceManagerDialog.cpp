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
#include <QHBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <QToolBar>
#include <QMessageBox>
#include <QPushButton>

#include "OpcUaNodeSetModul/Dialog/NamespaceManagerDialog.h"

namespace OpcUaNodeSet
{


	NamespaceManagerDialog::NamespaceManagerDialog(DataModel* dataModel)
	: QDialog()
	, maxNamespaceIndex_(0)
	, dataModel_(dataModel)
	, actValue_("")
	{
		InformationModelMap::iterator it;
		for (it = dataModel_->informationModel()->informationModelMap().begin();
			 it != dataModel_->informationModel()->informationModelMap().end();
			 it++
			)
		{
			OpcUaNodeId nodeId;
			BaseNodeClass::SPtr baseNode = it->second;
			baseNode->getNodeId(nodeId);
			if (nodeId.namespaceIndex() > maxNamespaceIndex_) {
				maxNamespaceIndex_ = nodeId.namespaceIndex();
			}
		}

		setWindowTitle(QString("Namespace Manager"));
		this->setFixedWidth(900);

		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		//
		// table tool bar
		//
		createTableActions();
		tableToolBar_ = new QToolBar();
		tableToolBar_->addAction(addRowAction_);
		tableToolBar_->addAction(deleteRowAction_);
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
		// create cancel and ok button
		//
		QHBoxLayout* buttonLayout = new QHBoxLayout();
		QPushButton* cancelButton = new QPushButton(tr("Cancel"));
		buttonLayout->addWidget(cancelButton);
		QPushButton* okButton = new QPushButton(tr("Ok"));
		buttonLayout->addWidget(okButton);
		vBoxLayout->addLayout(buttonLayout);

		//
		// actions
		//
		connect(
			namespaceTable_, SIGNAL(currentItemChanged(QTableWidgetItem*, QTableWidgetItem*)),
			this, SLOT(onCurrentItemChanged(QTableWidgetItem*, QTableWidgetItem*))
		);
		connect(
			namespaceTable_, SIGNAL(cellChanged(int, int)),
			this, SLOT(onCellChanged(int, int))
		);
		connect(
			cancelButton, SIGNAL(clicked()),
			this, SLOT(onCancelAction())
		);
		connect(
			okButton, SIGNAL(clicked()),
			this, SLOT(onOkAction())
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
		uint32_t counter = 0;
		std::stringstream ss;

		while (true)
		{
			ss.str("");
			ss << "http://ASNeG.de/Namespace" << counter;

			bool exist = false;
			for (uint32_t idx = 0; idx < namespaceTable_->rowCount(); idx++) {
				QTableWidgetItem* item = namespaceTable_->item(idx, 2);
				if (ss.str() == item->text().toStdString()) {
					exist = true;
					continue;
				}
			}

			if (exist) {
				counter++;
				continue;
			}

			break;

		}

		addRow(namespaceTable_->rowCount(), ss.str());
	}

	void
	NamespaceManagerDialog::onDeleteRowAction(void)
	{
		// get current row
		int row = namespaceTable_->currentRow();
		if (row < 0) return;

		// delete current row
		namespaceTable_->removeRow(row);

		// update the following lines
		for (uint32_t idx = row; idx < namespaceTable_->rowCount(); idx++) {
			QTableWidgetItem* item = namespaceTable_->item(idx, 0);
			item->setText(QString("%1").arg(idx));
		}
	}

    void
    NamespaceManagerDialog::onCellChanged(int row, int column)
    {
    	if (column != 2) return;
    	QTableWidgetItem* item = namespaceTable_->item(row, column);
    	std::string value = item->text().toStdString();
    	if (actValue_ == value) return;

    	uint32_t found = 0;
		for (uint32_t idx = 0; idx < namespaceTable_->rowCount(); idx++) {
			QTableWidgetItem* itemTmp = namespaceTable_->item(idx, column);
			if (itemTmp->text().toStdString() == value) {
				found++;
			}
		}

		if (found > 1) {
			QMessageBox::warning(
				this,
				tr("Namespace error"),
				tr("Dupplicate namespace found in table"),
				QMessageBox::Ok
		    );
			item->setText(actValue_.c_str());
		}
		else {
			actValue_ = value;
		}
    }

    void
    NamespaceManagerDialog::onCurrentItemChanged(QTableWidgetItem* newItem, QTableWidgetItem* oldItem)
    {
       	if (newItem == NULL) {
       		deleteRowAction_->setEnabled(false);
       	}
       	else {
       		actValue_ = newItem->text().toStdString();
       		if (newItem->row() > maxNamespaceIndex_) deleteRowAction_->setEnabled(true);
       		else deleteRowAction_->setEnabled(false);
       	}
    }

    void
    NamespaceManagerDialog::onCancelAction(void)
    {
    	close();
    }

    void
    NamespaceManagerDialog::onOkAction(void)
    {
		for (uint32_t idx = 0; idx < namespaceTable_->rowCount(); idx++) {
			QTableWidgetItem* item;

			item = namespaceTable_->item(idx, 2);
			std::string value = item->text().toStdString();

			// update visible mode
			item = namespaceTable_->item(idx, 1);
			if (item->isSelected()) {
				dataModel_->namespaceVisible(value, true);
			}
			else {
				dataModel_->namespaceVisible(value, false);
			}

			if (idx < dataModel_->nodeSetNamespace().globalNamespaceVec().size()) {
				// update existing namespace
				dataModel_->nodeSetNamespace().updateExistGlobalNamespace(idx, value);
			}
			else {
				// add new namespace
				dataModel_->nodeSetNamespace().addNewGlobalNamespace(value);
			}
		}

		// delete unused namespaces
		for (uint32_t idx = namespaceTable_->rowCount(); idx < dataModel_->nodeSetNamespace().globalNamespaceVec().size(); idx++) {
			// FIXME: todo
		}

    	close();
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

		deleteRowAction_ = new QAction("Delete table row", this);
		deleteRowAction_->setIcon(QIcon(":images/Delete.png"));
		deleteRowAction_->setEnabled(false);
		connect(deleteRowAction_, SIGNAL(triggered()), this, SLOT(onDeleteRowAction()));
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
		for (uint32_t row = 0; row < dataModel_->nodeSetNamespace().globalNamespaceVec().size(); row++) {
			addRow(row, dataModel_->nodeSetNamespace().globalNamespaceVec()[row]);
		}
	}

	void
	NamespaceManagerDialog::addRow(uint32_t row, const std::string& namespaceName)
	{
		QTableWidgetItem* item;

		// added new row to table
		namespaceTable_->insertRow(namespaceTable_->rowCount());

		// index
		item = new QTableWidgetItem();
		item->setText(QString("%1").arg(row));
		item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		namespaceTable_->setItem(row, 0, item);

		// visible
		bool isVisible = dataModel_->namespaceVisible(namespaceName);
		item = new QTableWidgetItem();
		item->data(Qt::CheckStateRole);
		item->setCheckState(isVisible ? Qt::Checked : Qt::Unchecked);
		if (row == 0) item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		namespaceTable_->setItem(row, 1, item);

		// namespace name
		item = new QTableWidgetItem();
		item->setText(QString(namespaceName.c_str()));
		if (row == 0) item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		namespaceTable_->setItem(row, 2, item);

		namespaceTable_->resizeColumnsToContents();
	}

}


