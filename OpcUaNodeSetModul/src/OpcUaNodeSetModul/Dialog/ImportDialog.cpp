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
#include <QListWidgetItem>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/ConfigXml.h"
#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaStackServer/NodeSet/NodeSetXmlParser.h"
#include "OpcUaStackServer/InformationModel/InformationModelNodeSet.h"
#include "OpcUaStackServer/InformationModel/InformationModelAccess.h"
#include "OpcUaNodeSetModul/Dialog/ImportDialog.h"

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{

	ImportDialog::ImportDialog(DataModel* dataModel)
	: QDialog()
	, dataModel_(dataModel)
	, importInformationModel_(constructSPtr<InformationModel>())
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
			exitButton, SIGNAL(clicked()),
		    this, SLOT(onExitAction())
		);
		connect(
			importButton_, SIGNAL(clicked()),
		    this, SLOT(onMergeAction())
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
	// dialog slots
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
    void
    ImportDialog::onRightAction(void)
    {
    	QList<QListWidgetItem*> items = out_->selectedItems();

    	for (int idx=0; idx<items.size(); idx++) {
    		QListWidgetItem* oldItem = items.at(idx);

    		// create new item
    		QListWidgetItem* newItem = new QListWidgetItem(oldItem->text());

    		// delete old item
    		delete oldItem;
    		in_->addItem(newItem);
    	}

    	if (in_->count() > 0) importButton_->setEnabled(true);
    	else importButton_->setEnabled(false);
    }

    void
    ImportDialog::onLeftAction(void)
    {
    	QList<QListWidgetItem*> items = in_->selectedItems();

    	for (int idx=0; idx<items.size(); idx++) {
    		QListWidgetItem* oldItem = items.at(idx);
    		QListWidgetItem* newItem = new QListWidgetItem(oldItem->text());

    		delete oldItem;
    		out_->addItem(newItem);
    	}

       	if (in_->count() > 0) importButton_->setEnabled(true);
        else importButton_->setEnabled(false);
    }

	void
	ImportDialog::onExitAction(void)
	{
		importInformationModel_->clear();
		close();
	}

	void
	ImportDialog::onMergeAction(void)
	{
		InformationModelAccess ima(dataModel_->informationModel());

		// merge all namespaces in list
		for (uint32_t row = 0; row < in_->count(); row++) {
			QListWidgetItem* item = in_->item(row);

			uint16_t namespaceIndex = dataModel_->nodeSetNamespace().mapToGlobalNamespaceIndex(item->text().toStdString());

			if (!ima.add(importInformationModel_, namespaceIndex)) {
				QMessageBox msgBox;
				msgBox.setText(QString("import namespace %1 error").arg(item->text()));
				msgBox.exec();
				return;
			}
		}

		dataModel_->informationModel()->checkForwardReferences();
		importInformationModel_->clear();
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

		// parse node set file
		ConfigXml configXml;
		bool rc = configXml.parse(fileName.toStdString());
		if (!rc) {
			QMessageBox msgBox;
			msgBox.setText(QString("parse node set file %1 error - %2")
				.arg(fileName)
				.arg(configXml.errorMessage().c_str())
			);
			msgBox.exec();
			return;
		}

		// decode node set
	    NodeSetXmlParser nodeSetXmlParser;
	    rc = nodeSetXmlParser.decode(configXml.ptree());
		if (!rc) {
			QMessageBox msgBox;
			msgBox.setText(QString("decode node set file %1 error")
				.arg(fileName)
			);
			msgBox.exec();
			return;
		}

		rc = InformationModelNodeSet::initial(importInformationModel_, nodeSetXmlParser);
		if (!rc) {
			QMessageBox msgBox;
			msgBox.setText(QString("decode node set model error - %1")
				.arg(fileName)
			);
			msgBox.exec();
			return;
		}

		importInformationModel_->checkForwardReferences();

		// fill list
		NamespaceVec::iterator it;
		NamespaceVec namespaceVec = nodeSetXmlParser.nodeSetNamespace().localNamespaceVec();
		for (it = namespaceVec.begin(); it != namespaceVec.end(); it++) {
			uint16_t namespaceIndex = nodeSetXmlParser.nodeSetNamespace().mapToGlobalNamespaceIndex(*it);
			if (namespaceIndex == 0) continue;
			QListWidgetItem* item = new QListWidgetItem((*it).c_str());
			out_->addItem(item);
		}
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------

}


