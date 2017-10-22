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


#include "OpcUaNodeSetModul/Dialog/ArrayDimensionDialog.h"

#include <iostream>
#include <sstream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QToolBar>
#include <QAction>

namespace BHIMatlabSimulink
{


	ArrayDimensionDialog::ArrayDimensionDialog(void)
	: QDialog()
	, actRow_(0)
	, actValue_("")
	, ok_(false)
	{
		this->setWindowTitle(QString("ArrayDimension Dialog"));

		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		//
		// property list
		//
		propertyList_ = new QListWidget();
		vBoxLayout->addWidget(propertyList_);

		//
		// control action buttons
		//
		createToolBarActions();
		QToolBar* toolBar = new QToolBar();
		toolBar->addAction(addAction_);
		toolBar->addAction(delAction_);
		toolBar->addAction(downAction_);
		toolBar->addAction(upAction_);
		vBoxLayout->addWidget(toolBar);

		//
		// dialog action button
		//
		QHBoxLayout* actionButtonLayout = new QHBoxLayout();
		QPushButton* cancelButton = new QPushButton("Cancel");
		actionButtonLayout->addWidget(cancelButton);
		QPushButton* okButton = new QPushButton("Ok");
		actionButtonLayout->addWidget(okButton);
		vBoxLayout->addLayout(actionButtonLayout);

		//
		// connection
		//
		connect(
			propertyList_, SIGNAL(itemActivated(QListWidgetItem*)),
		    this, SLOT(onItemActivatedAction(QListWidgetItem*))
		);
		connect(
			propertyList_, SIGNAL(currentTextChanged(const QString&)),
		    this, SLOT(onCurrentTextChanged(const QString&))
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

	ArrayDimensionDialog::~ArrayDimensionDialog(void)
	{
	}

	bool
	ArrayDimensionDialog::ok(void)
	{
		return ok_;
	}

	void
	ArrayDimensionDialog::setArrayDimensionVec(std::vector<std::string>& propertyVec)
	{
		std::vector<std::string>::iterator it;
		for (it=propertyVec.begin(); it!=propertyVec.end(); it++) {
	    	QListWidgetItem* item = new QListWidgetItem(QString((*it).c_str()));
	    	propertyList_->addItem(item);
	    	propertyList_->setCurrentItem(item);
		}

		if (propertyVec.size() > 0) propertyList_->setCurrentRow(0);
		enableButtons();
	}

	void
	ArrayDimensionDialog::getArrayDimensionVec(std::vector<std::string>& propertyVec)
	{
   		for (uint32_t row=0; row<propertyList_->count(); row++) {
    		QListWidgetItem* item = propertyList_->item(row);
    		propertyVec.push_back(item->text().toStdString());
   		}
	}

	void
	ArrayDimensionDialog::createToolBarActions(void)
	{
		addAction_ = new QAction("Add new property", this);
		addAction_->setIcon(QIcon(":images/Add.png"));
		connect(addAction_, SIGNAL(triggered()), this, SLOT(onAddAction()));

		delAction_ = new QAction("Delete new property", this);
		delAction_->setIcon(QIcon(":images/Delete.png"));
		delAction_->setEnabled(false);
		connect(delAction_, SIGNAL(triggered()), this, SLOT(onDelAction()));

		upAction_ = new QAction("Move property up", this);
		upAction_->setIcon(QIcon(":images/Up.png"));
		upAction_->setEnabled(false);
		connect(upAction_, SIGNAL(triggered()), this, SLOT(onUpAction()));

		downAction_ = new QAction("Move property down", this);
		downAction_->setIcon(QIcon(":images/Down.png"));
		downAction_->setEnabled(false);
		connect(downAction_, SIGNAL(triggered()), this, SLOT(onDownAction()));
	}

	void
	ArrayDimensionDialog::enableButtons(void)
	{
		if (propertyList_->count() == 0) {
		    delAction_->setEnabled(false);
		    upAction_->setEnabled(false);
		    downAction_->setEnabled(false);
		    return;
		}

		if (propertyList_->count() == 1) {
		    delAction_->setEnabled(true);
		    upAction_->setEnabled(false);
		    downAction_->setEnabled(false);
		    return;
		}

		delAction_->setEnabled(true);
		if (propertyList_->currentRow() == 0) {
			upAction_->setEnabled(false);
			downAction_->setEnabled(true);
			return;
		}

		if (propertyList_->currentRow() == (propertyList_->count()-1)) {
			upAction_->setEnabled(true);
			downAction_->setEnabled(false);
			return;
		}
		upAction_->setEnabled(true);
		downAction_->setEnabled(true);

	}

	uint32_t
	ArrayDimensionDialog::findItem(const std::string& itemName)
	{
		uint32_t count = 0;
   		for (uint32_t row=0; row<propertyList_->count(); row++) {
    		QListWidgetItem* item = propertyList_->item(row);
    		if (item->text().toStdString() == itemName) count++;
   		}
   		return count;
	}

    void
    ArrayDimensionDialog::onAddAction(void)
    {
    	// create new property name
    	std::string itemName;
    	uint32_t idx = 1;
    	do {
    		std::stringstream ss;
    		ss << "ArrayDimension " << idx;

    		bool found = false;
    		for (uint32_t row=0; row<propertyList_->count(); row++) {
    			QListWidgetItem* item = propertyList_->item(row);
    			if (item->text().toStdString() == ss.str()) {
    				found = true;
    				break;
    			}
    		}

    		idx++;
    		if (found) continue;
    		itemName = ss.str();
    		break;
    	} while (true);

    	// insert new property to list widget
    	QListWidgetItem* item = new QListWidgetItem(QString(itemName.c_str()));
    	propertyList_->addItem(item);
    	propertyList_->setCurrentItem(item);
    	enableButtons();
    }

    void
    ArrayDimensionDialog::onDelAction(void)
    {
    	QListWidgetItem* item = propertyList_->currentItem();
    	if (item != NULL) delete item;
    	enableButtons();
    }

    void
    ArrayDimensionDialog::onUpAction(void)
    {
    	int actRow = propertyList_->currentRow();
    	QListWidgetItem* actItem = propertyList_->item(actRow);
    	QListWidgetItem* upItem = propertyList_->item(actRow-1);

    	QString actName = actItem->text();
    	QString upName = upItem->text();

    	actItem->setText(upName);
    	upItem->setText(actName);

    	propertyList_->setCurrentRow(actRow-1);
    	enableButtons();
    }

	void
	ArrayDimensionDialog::onDownAction(void)
	{
    	int actRow = propertyList_->currentRow();
    	QListWidgetItem* actItem = propertyList_->item(actRow);
    	QListWidgetItem* downItem = propertyList_->item(actRow+1);

    	QString actName = actItem->text();
    	QString downName = downItem->text();

    	actItem->setText(downName);
    	downItem->setText(actName);

    	propertyList_->setCurrentRow(actRow+1);
    	enableButtons();
	}

    void
    ArrayDimensionDialog::onCancelAction(void)
    {
    	propertyList_->clear();
    	close();
    }

    void
    ArrayDimensionDialog::onOkAction(void)
    {
    	ok_ = true;
    	close();
    }

    void
    ArrayDimensionDialog::onItemActivatedAction(QListWidgetItem* item)
    {
    	actValue_ = item->text().toStdString();
    	actRow_ = propertyList_->currentRow();
    	propertyList_->openPersistentEditor (item);
    	enableButtons();
    }

    void
    ArrayDimensionDialog::onCurrentTextChanged(const QString& text)
    {
     	if (propertyList_->count() <= actRow_) return;

     	QListWidgetItem* item = propertyList_->item(actRow_);
     	if (findItem(item->text().toStdString()) > 1) {
     		propertyList_->setCurrentItem(item);
     		item->setText(QString(actValue_.c_str()));
     	}

     	enableButtons();
     }

}


