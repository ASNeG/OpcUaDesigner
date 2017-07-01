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


#include "OpcUaStackCore/DataType/DataTypeGenerator.h"
#include "OpcUaStackServer/AddressSpaceModel/DataTypeNodeClass.h"
#include "OpcUaStackServer/InformationModel/InformationModelAccess.h"
#include "OpcUaNodeSetModul/Dialog/DataTypeStructureGeneratorDialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

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
		BaseNodeClass::SPtr baseNodeClass = nodeClass_;
		InformationModelAccess ima(dataModel_->informationModel());
		OpcUaNodeId nodeId;
		OpcUaLocalizedText displayName;

		do
		{
			baseNodeClass->getNodeId(nodeId);
			baseNodeClass->getDisplayName(displayName);

			if (nodeId == OpcUaNodeId(22)) return;

			//
			// use only selected types
			//
			bool found = false;
			for (uint32_t idx = 0; idx < in_->count(); idx++) {
				QListWidgetItem* item = in_->item(idx);

				if (item->text().toStdString() == displayName.text().value()) {
					found = true;
				}
			}

			if (found) {
				DataTypeGenerator dataTypeGenerator;

				//
				// get directory to save generated source code
				//
				QString directory = QFileDialog::getExistingDirectory(
					NULL, tr("Set Export NodeSet File"), QDir::homePath(), QFileDialog::ShowDirsOnly
				);
				if (directory.isNull()) {
					return;
				}

			    //
			    // get data type definition from node class
			    //
				DataTypeNodeClass::SPtr dataTypeNodeClass = boost::static_pointer_cast<DataTypeNodeClass>(baseNodeClass);
				Object::SPtr object = dataTypeNodeClass->dataTypeDefinition();
				if (object.get() == nullptr) {
					QMessageBox::information(this,
						tr("generate data type error"),
						tr("no definition for datatype %1 found").arg(displayName.text().value().c_str())
					);
					return;
				}
				DataTypeDefinition::SPtr dataTypeDefinition;
				dataTypeDefinition = boost::static_pointer_cast<DataTypeDefinition>(object);
				dataTypeGenerator.dataTypeDefinition(dataTypeDefinition);

				//
				// base class or derived class
				//
				BaseNodeClass::SPtr subTypeNodeClass;
			    ima.getSubType(baseNodeClass, subTypeNodeClass);
			    OpcUaNodeId subTypeNodeId;
			    subTypeNodeClass->getNodeId(nodeId);

			    if (subTypeNodeId != OpcUaNodeId(22)) {
				    //
				    // get data type definition from node class
				    //
					DataTypeNodeClass::SPtr dataTypeNodeClass = boost::static_pointer_cast<DataTypeNodeClass>(subTypeNodeClass);
					Object::SPtr object = dataTypeNodeClass->dataTypeDefinition();
					if (object.get() == nullptr) {
						OpcUaLocalizedText displayName;
						subTypeNodeClass->getDisplayName(displayName);

						QMessageBox::information(this,
							tr("generate data type error"),
							tr("no definition for base datatype %1 found").arg(displayName.text().value().c_str())
						);
						return;
					}
					DataTypeDefinition::SPtr dataTypeDefinition;
					dataTypeDefinition = boost::static_pointer_cast<DataTypeDefinition>(object);
					dataTypeGenerator.superTypeDataTypeDefinition(dataTypeDefinition);
			    }

			    //
				// create source code
			    //
			    // FIXME: use default actually ...
				//void projectNamespace(const std::string& projectName);
				//void projectDirectory(const std::string& projectDirectory);
			    if (!dataTypeGenerator.generate()) {
			    	QMessageBox::information(this,
			    		tr("generate data type error"),
			    		tr("create data type %1 error").arg(displayName.text().value().c_str())
			    	);

			    	// FIXME: todo
			    	std::cout << dataTypeGenerator.headerFileContent() << std::endl;
			    	std::cout << "===================================" << std::endl;
			    	std::cout << dataTypeGenerator.sourceFileContent() << std::endl;
			    }
			    else {
			    	QMessageBox::information(this,
			    		tr("generate data type success"),
			    		tr("create data type %1").arg(displayName.text().value().c_str())
			    	);
			    }
			}

			BaseNodeClass::SPtr subTypeNodeClass;
			if (ima.getSubType(baseNodeClass, subTypeNodeClass)) {
				baseNodeClass = subTypeNodeClass;
			}
			else {
				return;
			}
		} while (true);

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
		BaseNodeClass::SPtr baseNodeClass = nodeClass_;
		InformationModelAccess ima(dataModel_->informationModel());
		OpcUaNodeId nodeId;
		OpcUaLocalizedText displayName;

		do
		{
			baseNodeClass->getNodeId(nodeId);
			baseNodeClass->getDisplayName(displayName);

			if (nodeId == OpcUaNodeId(22)) return;

			QListWidgetItem* item = new QListWidgetItem(displayName.text().value().c_str());
			out_->addItem(item);

			BaseNodeClass::SPtr subTypeNodeClass;
			if (ima.getSubType(baseNodeClass, subTypeNodeClass)) {
				baseNodeClass = subTypeNodeClass;
			}
			else {
				return;
			}
		} while (true);
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


