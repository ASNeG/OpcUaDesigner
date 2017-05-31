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

#include "OpcUaNodeSetModul/Dialog/NamespaceManagerDialog.h"

namespace OpcUaNodeSet
{


	NamespaceManagerDialog::NamespaceManagerDialog(DataModel* dataModel)
	: QDialog()
	, dataModel_(dataModel)
	{
		this->setWindowTitle(QString("Namespace Manager"));

		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		//
		// create table widget
		//
		namespaceTable_ = new QTableWidget(0,2);
		namespaceTable_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		writeHeader();
		writeData();
		vBoxLayout->addWidget(namespaceTable_);

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

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
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

		for (uint32_t idx = 0; idx < namespaceVec.size(); idx++) {
			QTableWidgetItem* item;

			// added new row to table
			namespaceTable_->insertRow(namespaceTable_->rowCount());

			// index
			item = new QTableWidgetItem();
			item->setText(QString("%1").arg(idx));
			namespaceTable_->setItem(idx, 0, item);

			// visible
			item = new QTableWidgetItem();
			item->data(Qt::CheckStateRole);
			item->setCheckState(Qt::Checked);
			namespaceTable_->setItem(idx, 1, item);

			// namespace name
			item = new QTableWidgetItem();
			item->setText(QString(namespaceVec[idx].c_str()));
			namespaceTable_->setItem(idx, 2, item);
		}
	}

}


