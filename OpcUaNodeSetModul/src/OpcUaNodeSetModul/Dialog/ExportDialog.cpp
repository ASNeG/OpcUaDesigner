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


#include "OpcUaNodeSetModul/Dialog/ExportDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

namespace OpcUaNodeSet
{


	ExportDialog::ExportDialog(DataModel* dataModel)
	: QDialog()
	, dataModel_(dataModel)
	{
		this->setWindowTitle(QString("Export Nodeset Dialog"));

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
			this, SLOT(onExportAction())
		);

		//
		// data model
		//
		//fillList();

		setLayout(vBoxLayout);
	}

	ExportDialog::~ExportDialog(void)
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

}


