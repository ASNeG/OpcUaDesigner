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


#include <OpcUaNodeSetModul/Dialog/ArrayDimensionsDialog.h>
#include <iostream>
#include <sstream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QCheckBox>
#include <QToolBar>
#include <QAction>
#include <QLabel>
#include <QEvent>

namespace OpcUaNodeSet
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
		// is null check box
		//
		QHBoxLayout* isNullLayout = new QHBoxLayout();
		QLabel* checkBoxLabel = new QLabel(QString("IsNull"));
		isNullLayout->addWidget(checkBoxLabel);
		checkboxWidget_ = new QCheckBox();
		isNullLayout->addWidget(checkboxWidget_);

		vBoxLayout->addLayout(isNullLayout);

		//
		// property list
		//
		dimensionList_ = new QListWidget();
		vBoxLayout->addWidget(dimensionList_);

		//
		// control action buttons
		//
		createToolBarActions();
		toolBar_ = new QToolBar();
		toolBar_->addAction(addAction_);
		toolBar_->addAction(delAction_);
		toolBar_->addAction(downAction_);
		toolBar_->addAction(upAction_);
		vBoxLayout->addWidget(toolBar_);

		//
		// dialog action button
		//
		QHBoxLayout* actionButtonLayout = new QHBoxLayout();
		QPushButton* cancelButton = new QPushButton("Cancel");
		actionButtonLayout->addWidget(cancelButton);
		okButton_ = new QPushButton("Ok");
		actionButtonLayout->addWidget(okButton_);
		vBoxLayout->addLayout(actionButtonLayout);

		//
		// connection
		//
		connect(
			checkboxWidget_, SIGNAL(stateChanged(int)),
			this, SLOT(onStateChanged(int))
		);
		connect(
			dimensionList_, SIGNAL(itemActivated(QListWidgetItem*)),
		    this, SLOT(onItemActivatedAction(QListWidgetItem*))
		);
		connect(
			dimensionList_, SIGNAL(currentTextChanged(const QString&)),
		    this, SLOT(onCurrentTextChanged(const QString&))
		);
		connect(
			cancelButton, SIGNAL(clicked()),
		    this, SLOT(onCancelAction())
		);
		connect(
			okButton_, SIGNAL(clicked()),
		    this, SLOT(onOkAction())
		);

		//dimensionList_->installEventFilter(this);

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
	ArrayDimensionDialog::setArrayDimensions(OpcUaUInt32Array::SPtr& arrayDimensions)
	{
		if (arrayDimensions.get() == nullptr || arrayDimensions->isNull()) {
			checkboxWidget_->setCheckState(Qt::Checked);
			dimensionList_->setVisible(false);
			toolBar_->setVisible(false);
			return;
		}

		uint32_t size = arrayDimensions->size();
		for (uint32_t idx=0; idx<size; idx++) {
			OpcUaUInt32 arrayDimension;
			arrayDimensions->get(idx, arrayDimension);

			QListWidgetItem* item = new QListWidgetItem(QString("%1").arg(arrayDimension));
			dimensionList_->addItem(item);
			dimensionList_->setCurrentItem(item);
		}

		if (size > 0) dimensionList_->setCurrentRow(0);
		enableButtons();
	}

	void
	ArrayDimensionDialog::getArrayDimensions(OpcUaUInt32Array::SPtr& arrayDimensions)
	{
		arrayDimensions = constructSPtr<OpcUaUInt32Array>();
		if (checkboxWidget_->isChecked()) {
			arrayDimensions->setNull();
			return;
		}

		if (dimensionList_->count() != 0) {
			arrayDimensions->resize(dimensionList_->count());
		}
   		for (uint32_t row=0; row<dimensionList_->count(); row++) {
    		QListWidgetItem* item = dimensionList_->item(row);

    		OpcUaUInt32 value = item->text().toUInt();
    		arrayDimensions->set(row, value);
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
		if (dimensionList_->count() == 0) {
		    delAction_->setEnabled(false);
		    upAction_->setEnabled(false);
		    downAction_->setEnabled(false);
		    return;
		}

		if (dimensionList_->count() == 1) {
		    delAction_->setEnabled(true);
		    upAction_->setEnabled(false);
		    downAction_->setEnabled(false);
		    return;
		}

		delAction_->setEnabled(true);
		if (dimensionList_->currentRow() == 0) {
			upAction_->setEnabled(false);
			downAction_->setEnabled(true);
			return;
		}

		if (dimensionList_->currentRow() == (dimensionList_->count()-1)) {
			upAction_->setEnabled(true);
			downAction_->setEnabled(false);
			return;
		}
		upAction_->setEnabled(true);
		downAction_->setEnabled(true);
	}

	bool
	ArrayDimensionDialog::eventFilter(QObject *obj, QEvent *event)
	{
#if 0
		if (obj == dimensionList_ && event->type() == QEvent::KeyRelease ) {
	    	okButton_->setEnabled(true);
	   		for (uint32_t row=0; row<dimensionList_->count(); row++) {
	    		QListWidgetItem* item = dimensionList_->item(row);

	    		bool ok = true;
	    		item->text().toUInt(&ok);
	    		if (!ok) {
	    			std::cout << "not ok " << item->text().toStdString() << std::endl;
	    			okButton_->setEnabled(false);
	    			item->setBackground(Qt::red);
	    		}
	    		else {
	    			std::cout << "ok " << item->text().toStdString() << std::endl;
	    			item->setBackground(Qt::white);
	    		}
	   		}
		}
#endif
		return QObject::eventFilter(obj, event);
	}

    void
    ArrayDimensionDialog::onAddAction(void)
    {
    	// insert new property to list widget
    	QListWidgetItem* item = new QListWidgetItem(QString("1"));
    	dimensionList_->addItem(item);
    	dimensionList_->setCurrentItem(item);
    	enableButtons();
    }

    void
    ArrayDimensionDialog::onDelAction(void)
    {
    	QListWidgetItem* item = dimensionList_->currentItem();
    	if (item != NULL) delete item;
    	enableButtons();
    }

    void
    ArrayDimensionDialog::onUpAction(void)
    {
    	int actRow = dimensionList_->currentRow();
    	QListWidgetItem* actItem = dimensionList_->item(actRow);
    	QListWidgetItem* upItem = dimensionList_->item(actRow-1);

    	QString actName = actItem->text();
    	QString upName = upItem->text();

    	actItem->setText(upName);
    	upItem->setText(actName);

    	dimensionList_->setCurrentRow(actRow-1);
    	enableButtons();
    }

	void
	ArrayDimensionDialog::onDownAction(void)
	{
    	int actRow = dimensionList_->currentRow();
    	QListWidgetItem* actItem = dimensionList_->item(actRow);
    	QListWidgetItem* downItem = dimensionList_->item(actRow+1);

    	QString actName = actItem->text();
    	QString downName = downItem->text();

    	actItem->setText(downName);
    	downItem->setText(actName);

    	dimensionList_->setCurrentRow(actRow+1);
    	enableButtons();
	}

    void
    ArrayDimensionDialog::onCancelAction(void)
    {
    	dimensionList_->clear();
    	close();
    }

    void
    ArrayDimensionDialog::onOkAction(void)
    {
    	onCurrentTextChanged(QString("..."));
    	if (!okButton_->isEnabled()) {
    		return;
    	}

    	ok_ = true;
    	close();
    }

    void
    ArrayDimensionDialog::onItemActivatedAction(QListWidgetItem* item)
    {
    	actValue_ = item->text().toStdString();
    	actRow_ = dimensionList_->currentRow();
    	dimensionList_->openPersistentEditor (item);
    	enableButtons();
    }

    void
    ArrayDimensionDialog::onCurrentTextChanged(const QString& text)
    {
    	okButton_->setEnabled(true);
   		for (uint32_t row=0; row<dimensionList_->count(); row++) {
    		QListWidgetItem* item = dimensionList_->item(row);

    		bool ok = true;
    		item->text().toUInt(&ok);
    		if (!ok) {
    			okButton_->setEnabled(false);
    			item->setBackground(Qt::red);
    		}
    		else {
    			item->setBackground(Qt::white);
    		}
   		}

     	enableButtons();
     }

	void
	ArrayDimensionDialog::onStateChanged(int stateCheckBox)
	{
		if (stateCheckBox == Qt::Checked) {
		    dimensionList_->setVisible(false);
		    toolBar_->setVisible(false);
		    okButton_->setEnabled(true);
		}
		else {
		    dimensionList_->setVisible(true);
		    toolBar_->setVisible(true);
		}
	}

}


