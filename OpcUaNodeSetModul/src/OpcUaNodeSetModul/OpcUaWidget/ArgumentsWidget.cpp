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

#include <sstream>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTableWidget>
#include <QMenu>
#include <QToolBar>

#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackCore/StandardDataTypes/Argument.h"
#include "OpcUaNodeSetModul/OpcUaWidget/ArgumentsWidget.h"

using namespace OpcUaStackCore;

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
		tableWidget_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
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
	ArgumentsWidget::nodeChange(NodeInfo* nodeInfo, BaseNodeClass::SPtr& baseNode)
	{
		writeHeader();

		//
		// check and get value
		//
		if (baseNode.get() == nullptr) {
			return;
		}
		if (baseNode->isNullValue()) {
			return;
		}
		if (!baseNode->isPartValue()) {
			return;
		}

		OpcUaDataValue dataValue;
		if (!baseNode->getValue(dataValue)) {
			return;
		}

		//
		// integrate arguments into table
		//
		if (dataValue.variant()->isNull()) {
			return;
		}
		if (dataValue.variant()->variantType() != OpcUaBuildInType_OpcUaExtensionObject) {
			return;
		}
		if (!dataValue.variant()->isArray()) {
			return;
		}

		OpcUaVariant::SPtr variant = dataValue.variant();

		checkOn_ = false;
		writeTable(variant);
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
	// write table content
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	ArgumentsWidget::writeHeader(void)
	{
		QStringList headerLabels;

		// reset table
		tableWidget_->setColumnCount(0);
		tableWidget_->setRowCount(0);

		// create table header
		tableWidget_->setColumnCount(5);
		headerLabels << "Name" << "DataType" << "ValueRank" << "ArrayDimensions" << "Description";

		tableWidget_->setHorizontalHeaderLabels(headerLabels);
	}

	void
	ArgumentsWidget::writeTable(OpcUaVariant::SPtr& variant)
	{
		std::stringstream ss;
		QTableWidgetItem* item;
		//std::cout << "value exist..." << variant->arrayLength() << std::endl;

		for (uint32_t idx=0; idx<variant->arrayLength(); idx++) {
			OpcUaExtensionObject::SPtr extensionObject = variant->getSPtr<OpcUaExtensionObject>(idx);

			if (extensionObject->typeId().nodeId<OpcUaUInt32>() != OpcUaId_Argument_Encoding_DefaultBinary) {
				continue;
			}
			Argument::SPtr argument = extensionObject->parameter<Argument>();

			tableWidget_->insertRow(tableWidget_->rowCount());

			// name
			item = new QTableWidgetItem();
			item->setText(QString(argument->name().toStdString().c_str()));
			tableWidget_->setItem(idx, 0, item);

			// dataType
			item = new QTableWidgetItem();
			item->setText(QString(argument->dataType().toString().c_str()));
			tableWidget_->setItem(idx, 1, item);

			// value rank
			ss.str("");
			ss << argument->valueRank();
			item = new QTableWidgetItem();
			item->setText(QString(ss.str().c_str()));
			tableWidget_->setItem(idx, 2, item);

			// array dimensions
			ss.str("");
			argument->arrayDimensions()->out(ss);
			item = new QTableWidgetItem();
			item->setText(QString(ss.str().c_str()));
			tableWidget_->setItem(idx, 3, item);

			// description
			item = new QTableWidgetItem();
			item->setText(QString(argument->description().toString().c_str()));
			tableWidget_->setItem(idx, 4, item);
		}

	}

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


