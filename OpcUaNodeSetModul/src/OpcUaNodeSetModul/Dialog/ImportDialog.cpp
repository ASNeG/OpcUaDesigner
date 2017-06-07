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


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>

#include "OpcUaNodeSetModul/Dialog/ImportDialog.h"

namespace OpcUaNodeSet
{


	ImportDialog::ImportDialog(DataModel* dataModel)
	: QDialog()
	, dataModel_(dataModel)
	{
		this->setWindowTitle(QString("Import NodeSet Dialog"));

		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		//
		// type selection lyout
		//
		QHBoxLayout* namespaceSelectionLayout = new QHBoxLayout();

		QVBoxLayout* namespaceSelectionOutLayout = new QVBoxLayout();
		namespaceSelectionOutLayout->addWidget(new QLabel("Loaded namespaces"));
		out_ = new QListWidget();
		out_->setContextMenuPolicy(Qt::CustomContextMenu);
		out_->setSelectionMode(QAbstractItemView::MultiSelection);
		namespaceSelectionOutLayout->addWidget(out_);
		namespaceSelectionLayout->addLayout(namespaceSelectionOutLayout);

		QVBoxLayout* namespaceSelectionInLayout = new QVBoxLayout();
		QPushButton* right = new QPushButton();
		right->setIcon(QIcon(":images/Right.png"));
		namespaceSelectionInLayout->addWidget(right);
		QPushButton* left = new QPushButton();
		left->setIcon(QIcon(":images/Left.png"));
		namespaceSelectionInLayout->addWidget(left);
		namespaceSelectionLayout->addLayout(namespaceSelectionInLayout);

		QVBoxLayout* typeSelectionInLayout = new QVBoxLayout();
		typeSelectionInLayout->addWidget(new QLabel("Accepted namespaces"));
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
		importButton_ = new QPushButton("Import");
		importButton_->setEnabled(false);
		actionButtonLayout->addWidget(importButton_);
		QPushButton* loadButton = new QPushButton("Load");
		actionButtonLayout->addWidget(loadButton);
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
		    out_, SIGNAL(customContextMenuRequested(const QPoint&)),
		    this, SLOT(onCustomContextMenuRequested(const QPoint&))
		);
		connect(
			exitButton, SIGNAL(clicked()),
		    this, SLOT(onExitAction())
		);
		connect(
			importButton_, SIGNAL(clicked()),
		    this, SLOT(onTakeOverAction())
		);
		connect(
			loadButton, SIGNAL(clicked()),
		    this, SLOT(onImportAction())
		);

		setLayout(vBoxLayout);
	}

	ImportDialog::~ImportDialog(void)
	{
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// context menu function
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	ImportDialog::onCustomContextMenuRequested(const QPoint& pos)
	{
#if 0
	    QMenu menu;

		QAction* action = new QAction("Rename", this);
		action->setIcon(QIcon(":images/Edit.png"));
		menu.addAction(action);
		connect(action, SIGNAL(triggered()), this, SLOT(onRenameAction()));

	    // show menu
	    menu.exec(out_->viewport()->mapToGlobal(pos));
#endif
	}

	void
	ImportDialog::onRenameAction(void)
	{
#if 0
		// get current item from out list
		QListWidgetItem* item = out_->currentItem();

		// ask new type name
		bool success;
		QString newTypeName = QInputDialog::getText(this,
			"Change Type Name",
			"Please input new type name:",
			QLineEdit::Normal,
			item->text(),
			&success
		);
		if (!success || newTypeName.isEmpty()) {
			return;
		}

		// check new type name
		if (dataModel_->existNodeSet(newTypeName.toStdString()) ||
			importDataModel_.existNodeSet(newTypeName.toStdString())) {
	    	QMessageBox::critical(this,
	    		tr("import types error"),
	    		tr("type %1 already exist in data model").arg(newTypeName)
	    	);
			return;
		}

		// set new type name
		importDataModel_.changeNodeSet(item->text().toStdString(), newTypeName.toStdString());
		item->setText(newTypeName);
#endif
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// dialog slots
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
    void
    ImportDialog::onRightAction(void)
    {
#if 0
    	QList<QListWidgetItem*> items = out_->selectedItems();

    	for (int idx=0; idx<items.size(); idx++) {
    		QListWidgetItem* oldItem = items.at(idx);

    		// duplicate check
    		if (dataModel_->existNodeSet(oldItem->text().toStdString())) {
    			QMessageBox::critical(this,
    				tr("import types error"),
    				tr("type %1 already exist in data model").arg(oldItem->text())
    			);
    			continue;
    		}

    		// create new item
    		QListWidgetItem* newItem = new QListWidgetItem(oldItem->text());
    		newItem->setIcon(QIcon(":images/ObjectType.png"));

    		// delete old item
    		delete oldItem;
    		in_->addItem(newItem);
    	}

    	if (in_->count() > 0) importButton_->setEnabled(true);
    	else importButton_->setEnabled(false);
#endif
    }

    void
    ImportDialog::onLeftAction(void)
    {
#if 0
    	QList<QListWidgetItem*> items = in_->selectedItems();

    	for (int idx=0; idx<items.size(); idx++) {
    		QListWidgetItem* oldItem = items.at(idx);
    		QListWidgetItem* newItem = new QListWidgetItem(oldItem->text());
    		newItem->setIcon(QIcon(":images/ObjectType.png"));

    		delete oldItem;
    		out_->addItem(newItem);
    	}

       	if (in_->count() > 0) importButton_->setEnabled(true);
        else importButton_->setEnabled(false);
#endif
    }

	void
	ImportDialog::onExitAction(void)
	{
#if 0
		importDataModel_.clearNodeSet();
		in_->clear();
		out_->clear();
		close();
#endif
	}

	void
	ImportDialog::onTakeOverAction(void)
	{
		close();
	}

	void
	ImportDialog::onImportAction(void)
	{
		//importDataModel_.clearNodeSet();
		in_->clear();
		out_->clear();

		// get type file name
		std::string docs = "NodeSet (*.NodeSet.xml)";
		QString fileName = QFileDialog::getOpenFileName(
			NULL, tr("Set Import NodeSet File"), QDir::homePath(), QString(docs.c_str())
		);
		if (fileName.isNull()) {
			return;
		}

#if 0
		// read types file
		ConfigXml configXml;
		if (!configXml.read(fileName.toStdString())) {
			QMessageBox::critical(this,
				tr("import types error"),
				tr("read types file %1 error").arg(fileName)
			);
			return;
		}

		// create configuration
		Config config;
		config.child(configXml.ptree());

		// create types
		if (!config.exist("NodeSet")) {
			QMessageBox::critical(this,
				tr("import types error"),
				tr("invalid format in types file %1 - NodeSet element missing").arg(fileName)
			);
			return;
		}

		std::vector<Config> configNodeSetVec;
		config.getChilds("NodeSet.DataType", configNodeSetVec);
		if (configNodeSetVec.size() == 0) {
			QMessageBox::critical(this,
				tr("import types error"),
				tr("invalid format in types file %1 -  DataType element missing").arg(fileName)
			);
			return;
		}

		// decode configuration - create types
		std::vector<Config>::iterator it1;
		for (it1 = configNodeSetVec.begin(); it1 != configNodeSetVec.end(); it1++) {
			NodeSet::SPtr types = constructSPtr<NodeSet>();
			if (!types->decode(*it1)) {
				QMessageBox::critical(this,
					tr("import types error"),
					tr("invalid format in types file %1 -  DataType element missing").arg(fileName)
				);
				return;
			}
			if (importDataModel_.existNodeSet(types->name())) {
				QMessageBox::critical(this,
					tr("import types error"),
					tr("duplicate type definition in types file %1").arg(fileName)
				);
				return;
			}

			if (role_ != types->role()) continue;

			importDataModel_.insertNodeSet(types);
		}

		// fill list
		NodeSet::Map::iterator it2;
		for (it2 = importDataModel_.typesMap().begin(); it2 != importDataModel_.typesMap().end(); it2++) {
			QListWidgetItem* item = new QListWidgetItem(QString(it2->first.c_str()));
			item->setIcon(QIcon(":images/ObjectType.png"));
			out_->addItem(item);
		}
#endif
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------

}


