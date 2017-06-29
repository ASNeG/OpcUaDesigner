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


	DataTypeStructureGeneratorDialog::DataTypeStructureGeneratorDialog(
		DataModel* dataModel,
		BaseNodeClass::SPtr& nodeClass
	)
	: QDialog()
	, dataModel_(dataModel)
	, nodeClass_(nodeClass)
	{
		this->setWindowTitle(QString("Data Type Structure Code Generator Dialog"));

		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		//
		// type selection layout
		//
		QHBoxLayout* typeSelectionLayout = new QHBoxLayout();

		QVBoxLayout* typeSelectionOutLayout = new QVBoxLayout();
		typeSelectionOutLayout->addWidget(new QLabel("All available structure types"));
		out_ = new QListWidget();
		out_->setSelectionMode(QAbstractItemView::MultiSelection);
		typeSelectionOutLayout->addWidget(out_);
		typeSelectionLayout->addLayout(typeSelectionOutLayout);

		QVBoxLayout* selectionButtonLayout = new QVBoxLayout();
		QPushButton* right = new QPushButton();
		right->setIcon(QIcon(":images/Right.png"));
		selectionButtonLayout->addWidget(right);
		QPushButton* left = new QPushButton();
		left->setIcon(QIcon(":images/Left.png"));
		selectionButtonLayout->addWidget(left);
		typeSelectionLayout->addLayout(selectionButtonLayout);

		QVBoxLayout* typeSelectionInLayout = new QVBoxLayout();
		typeSelectionInLayout->addWidget(new QLabel("All structure types to export"));
		in_ = new QListWidget();
		in_->setSelectionMode(QAbstractItemView::MultiSelection);
		typeSelectionInLayout->addWidget(in_);
		typeSelectionLayout->addLayout(typeSelectionInLayout);

		vBoxLayout->addLayout(typeSelectionLayout);

		//
		// dialog action button
		//
		QHBoxLayout* actionButtonLayout = new QHBoxLayout();
		QPushButton* exitButton = new QPushButton("Exit");
		actionButtonLayout->addWidget(exitButton);
		generatorButton_ = new QPushButton("Generator");
		generatorButton_->setEnabled(false);
		actionButtonLayout->addWidget(generatorButton_);
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
			generatorButton_, SIGNAL(clicked()),
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
	DataTypeStructureGeneratorDialog::fillList(void)
	{
		// FIXME: todo
	}

	void
	DataTypeStructureGeneratorDialog::enableDataTypeStructureGeneratorButton(void)
	{
		if (in_->count() > 0) {
			generatorButton_->setEnabled(true);
		}
		else {
			generatorButton_->setEnabled(false);
		}
	}

}


