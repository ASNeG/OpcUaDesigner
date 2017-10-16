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

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QMenu>
#include <QToolBar>

#include "OpcUaNodeSetModul/OpcUaWidget/ArgumentsWidget.h"

namespace OpcUaNodeSet
{


	ArgumentsWidget::ArgumentsWidget(const std::string& title, QWidget* parent)
	: QWidget()
	, checkOn_(true)
	, isValid_(true)
	, title_(title)
	{
		// layout
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->setMargin(0);

		// title
		QLabel* titleWidget = new QLabel();
		titleWidget->setText(QString(title_.c_str()));
		vBoxLayout->addWidget(titleWidget);

		//
		// table tool bar
		//
		createTableActions();
		tableToolBar_ = new QToolBar();
		tableToolBar_->addAction(addRowAction_);
		tableToolBar_->addAction(delRowAction_);
		vBoxLayout->addWidget(tableToolBar_);

		// table widget
		tableWidget_ = new QTableWidget(0,4);
		vBoxLayout->addWidget(tableWidget_);

		setLayout(vBoxLayout);

		//
		// actions
		//
		//connect(
		//	textWidget_, SIGNAL(textChanged(const QString&)),
		//	this, SLOT(onTextChangedTextWidget(const QString&))
		//)
	}

	ArgumentsWidget::~ArgumentsWidget(void)
	{
	}

	bool
	ArgumentsWidget::isValid(void)
	{
		return isValid_;
	}

	void
	ArgumentsWidget::nodeChange(NodeInfo* nodeInfo, BaseNodeClass::SPtr& arguments)
	{
		std::cout << "..." << std::endl;

		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullValue()) {
			std::cout << "value is null..." << std::endl;
			return;
		}

		// check value
		OpcUaDataValue dataValue;
		if (!baseNode->getValue(dataValue)) {
			std::cout << "get value error..." << std::endl;
			return;
		}

		std::cout << "value exist..." << std::endl;

		checkOn_ = false;
		isValid_ = checkValue();
		styleValue();
		checkOn_ = true;
	}

	void
	ArgumentsWidget::enabled(bool enabled)
	{
		tableWidget_->setEnabled(enabled);
	}

	void
	ArgumentsWidget::getValue(OpcUaByte& accessLevel)
	{
#if 0
		bool rc;
		accessLevel = textWidget_->text().toInt(&rc);
#endif
	}

	bool
	ArgumentsWidget::checkValue(void)
	{
		// FIXME: todo
		return true;
	}

	void
	ArgumentsWidget::styleValue(void)
	{
#if 0
		if (isValid_) {
			table_->setStyleSheet("background-color:none;");
		}
		else {
			table_->setStyleSheet("background-color:red;");
		}
#endif
	}

#if 0
	void
	ArgumentsWidget::onTextChangedTextWidget(const QString& text)
	{
		if (!checkOn_) return;

		OpcUaByte accessLevel;
		isValid_ = checkValue();
		styleValue();
		bool rc;
		accessLevel = textWidget_->text().toInt(&rc);
		emit valueChanged(accessLevel, isValid_);
	    emit update();
	}
#endif

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// table actions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	ArgumentsWidget::createTableActions(void)
	{
		addRowAction_ = new QAction("Add table row", this);
		addRowAction_->setIcon(QIcon(":images/Add.png"));
		connect(addRowAction_, SIGNAL(triggered()), this, SLOT(onAddRowAction()));

		delRowAction_ = new QAction("Delelete table row", this);
		delRowAction_->setIcon(QIcon(":images/Delete.png"));
		delRowAction_->setDisabled(true);
		connect(delRowAction_, SIGNAL(triggered()), this, SLOT(onDelRowAction()));
	}

    void
	ArgumentsWidget::onAddRowAction(void)
    {
    	// FIXME: todo
    }

    void
	ArgumentsWidget::onDelRowAction(void)
    {
    	// FIXME: todo
    }

}


