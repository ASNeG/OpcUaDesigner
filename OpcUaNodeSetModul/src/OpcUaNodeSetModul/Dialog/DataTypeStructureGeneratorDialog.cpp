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


#include "OpcUaNodeSetModul/Dialog/DataTypeStructureGeneratorDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

namespace OpcUaNodeSet
{


	DataTypeStructureGeneratorDialog::DataTypeStructureGeneratorDialog(DataModel* dataModel)
	: QDialog()
	, dataModel_(dataModel)
	{
		this->setWindowTitle(QString("DataTypeStructureGenerator NodeSet Dialog"));

		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		//
		// namespace selection layout
		//
		QHBoxLayout* namespaceSelectionLayout = new QHBoxLayout();

		QVBoxLayout* namespaceSelectionOutLayout = new QVBoxLayout();
		namespaceSelectionOutLayout->addWidget(new QLabel("All available namespaces"));
		out_ = new QListWidget();
		out_->setSelectionMode(QAbstractItemView::MultiSelection);
		namespaceSelectionOutLayout->addWidget(out_);
		namespaceSelectionLayout->addLayout(namespaceSelectionOutLayout);

		QVBoxLayout* selectionButtonLayout = new QVBoxLayout();
		QPushButton* right = new QPushButton();
		right->setIcon(QIcon(":images/Right.png"));
		selectionButtonLayout->addWidget(right);
		QPushButton* left = new QPushButton();
		left->setIcon(QIcon(":images/Left.png"));
		selectionButtonLayout->addWidget(left);
		namespaceSelectionLayout->addLayout(selectionButtonLayout);

		QVBoxLayout* typeSelectionInLayout = new QVBoxLayout();
		typeSelectionInLayout->addWidget(new QLabel("All namespaces to export"));
		in_ = new QListWidget();
		in_->setSelectionMode(QAbstractItemView::MultiSelection);
		typeSelectionInLayout->addWidget(in_);
		namespaceSelectionLayout->addLayout(typeSelectionInLayout);

		vBoxLayout->addLayout(namespaceSelectionLayout);

		//
		// dialog action button
		//
		QHBoxLayout* actionButtonLayout = new QHBoxLayout();
		QPushButton* exitButton = new QPushButton("Exit");
		actionButtonLayout->addWidget(exitButton);
		saveButton_ = new QPushButton("Save");
		saveButton_->setEnabled(false);
		actionButtonLayout->addWidget(saveButton_);
		vBoxLayout->addLayout(actionButtonLayout);

		//
		// connections
		//
		connect(
			right, SIGNAL(clicked()),
			this, SLOT(onRightAction())
		);
		connect(
			left, SIGNAL(clicked()),
			this, SLOT(onLeftAction())
		);
		connect(
			exitButton, SIGNAL(clicked()),
			this, SLOT(onExitAction())
		);
		connect(
			saveButton_, SIGNAL(clicked()),
			this, SLOT(onDataTypeStructureGeneratorAction())
		);

		//
		// data model
		//
		fillList();

		setLayout(vBoxLayout);
	}

	DataTypeStructureGeneratorDialog::~DataTypeStructureGeneratorDialog(void)
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
    DataTypeStructureGeneratorDialog::onRightAction(void)
    {
    	QList<QListWidgetItem*> items = out_->selectedItems();

    	for (int idx=0; idx<items.size(); idx++) {
    		QListWidgetItem* oldItem = items.at(idx);
    		QListWidgetItem* newItem = new QListWidgetItem(oldItem->text());

    		delete oldItem;
    		in_->addItem(newItem);
    	}
    	enableDataTypeStructureGeneratorButton();
    }

    void
    DataTypeStructureGeneratorDialog::onLeftAction(void)
    {
    	QList<QListWidgetItem*> items = in_->selectedItems();

    	for (int idx=0; idx<items.size(); idx++) {
    		QListWidgetItem* oldItem = items.at(idx);
    		QListWidgetItem* newItem = new QListWidgetItem(oldItem->text());
    		newItem->setIcon(QIcon(":images/ObjectType.png"));

    		delete oldItem;
    		out_->addItem(newItem);
    	}
    	enableDataTypeStructureGeneratorButton();
    }

    void
    DataTypeStructureGeneratorDialog::onExitAction(void)
    {
    	close();
    }

    void
    DataTypeStructureGeneratorDialog::onDataTypeStructureGeneratorAction(void)
    {
		// get node set file name
		std::string docs = "NodeSet (*.NodeSet.xml)";
		QString fileName = QFileDialog::getSaveFileName(
			NULL, tr("Set DataTypeStructureGenerator NodeSet File"), QDir::homePath(), QString(docs.c_str())
		);
		if (fileName.isNull()) {
			return;
		}

		if (!fileName.endsWith(".NodeSet.xml")) {
			fileName.append(".NodeSet.xml");
		}

		NamespaceVec namespaceVec;
		for (int idx=0; idx<in_->count(); idx++) {
			std::string name = in_->item(idx)->text().toStdString();
			namespaceVec.push_back(name);
		}

		// save empty node set
		if (!dataModel_->writeNodeSet(fileName.toStdString(), namespaceVec)) {
			QMessageBox msgBox;
			msgBox.setText(QString("cannot write node set file %1").arg(fileName));
			msgBox.exec();
			return;
		}

		QMessageBox::information(this,
			tr("export nodeset success"),
			tr("write nodeset file %1 done").arg(fileName)
		);
    }

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	DataTypeStructureGeneratorDialog::fillList(void)
	{
		NamespaceVec::iterator it;
		NamespaceVec namespaceVec = dataModel_->nodeSetNamespace().globalNamespaceVec();

		for (it = namespaceVec.begin(); it != namespaceVec.end(); it++) {
			QListWidgetItem* item = new QListWidgetItem((*it).c_str());
			out_->addItem(item);
		}
	}

	void
	DataTypeStructureGeneratorDialog::enableDataTypeStructureGeneratorButton(void)
	{
		if (in_->count() > 0) {
			saveButton_->setEnabled(true);
		}
		else {
			saveButton_->setEnabled(false);
		}
	}

}


