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
	, maxNamespaceIndex_(0)
	, dataModel_(dataModel)
	{
		namespaceVec_ = dataModel_->nodeSetNamespace().globalNamespaceVec();

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
			ss << "http://ASNeG.de/New" << counter;

			bool exist = false;
			for (uint32_t idx = 0; idx < namespaceVec_.size(); idx++) {
				if (ss.str() == namespaceVec_[idx]) {
					exist = true;
					continue;
				}
			}

			if (exist) {
				counter++;
				continue;
			}

			namespaceVec_.push_back(ss.str());
			break;

		}

		addRow(namespaceVec_.size()-1);
	}

	void
	NamespaceManagerDialog::onDeleteRowAction(void)
	{
		// FIXME: todo
	}

    void
    NamespaceManagerDialog::onCellChanged(int row, int column)
    {
    	std::cout << "cell changed - " << row << " " << column << std::endl;
    	// FIXME: todo
    }

    void
    NamespaceManagerDialog::onCurrentItemChanged(QTableWidgetItem* newItem, QTableWidgetItem* oldItem)
    {
    	std::cout << "on current item changed - NEW ";
    	if (newItem == NULL) std::cout << "NULL ";
    	else std::cout << newItem->row() << " " << newItem->column() << " ";
    	std::cout << " OLD ";
       	if (oldItem == NULL) std::cout << "NULL ";
        else std::cout << oldItem->row() << " " << oldItem->column() << " ";
       	std::cout << std::endl;

       	if (newItem == NULL) {
       		deleteRowAction_->setEnabled(false);
       	}
       	else {
       		if (newItem->row() > maxNamespaceIndex_) deleteRowAction_->setEnabled(true);
       		else deleteRowAction_->setEnabled(false);
       	}

    	// FIXME: todo
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
		for (uint32_t row = 0; row < namespaceVec_.size(); row++) {
			addRow(row);
		}
	}

	void
	NamespaceManagerDialog::addRow(uint32_t row)
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
		bool isVisible = dataModel_->namespaceVisible(namespaceVec_[row]);
		item = new QTableWidgetItem();
		item->data(Qt::CheckStateRole);
		item->setCheckState(isVisible ? Qt::Checked : Qt::Unchecked);
		if (row == 0) item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		namespaceTable_->setItem(row, 1, item);

		// namespace name
		item = new QTableWidgetItem();
		item->setText(QString(namespaceVec_[row].c_str()));
		if (row == 0) item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		namespaceTable_->setItem(row, 2, item);

		namespaceTable_->resizeColumnsToContents();
	}

	void
	NamespaceManagerDialog::deleteRow(uint32_t row)
	{
		// FIXME: todo
	}

}


