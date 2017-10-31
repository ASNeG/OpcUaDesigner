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
#include <QLineEdit>

#include "OpcUaNodeSetModul/OpcUaAttributeWidget/ValueWidget.h"

namespace OpcUaNodeSet
{


	ValueWidget::ValueWidget(QWidget* parent)
	: QWidget()
	, checkOn_(true)
	, isValid_(true)
	{
		// widgets
		textWidget_ = new QLineEdit();
		textWidget_->setFixedWidth(400);

		// layout
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->addWidget(textWidget_);
		vBoxLayout->setMargin(0);

		//
		// actions
		//
		connect(
			textWidget_, SIGNAL(textChanged(const QString&)),
			this, SLOT(onTextChangedTextWidget(const QString&))
		);

		setLayout(vBoxLayout);
	}

	ValueWidget::~ValueWidget(void)
	{
	}

	bool
	ValueWidget::isValid(void)
	{
		return isValid_;
	}

	void
	ValueWidget::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullValue()) {
			textWidget_->setText(QString(""));
		}

		checkOn_ = false;
		OpcUaDataValue dataValue;
		baseNode->getValue(dataValue);
		std::stringstream ss;
		dataValue.out(ss);
		textWidget_->setText(QString(ss.str().c_str()));
		isValid_ = checkValue();
		styleValue();
		checkOn_ = true;
	}

	void
	ValueWidget::enabled(bool enabled)
	{
		textWidget_->setEnabled(enabled);
	}

	void
	ValueWidget::getValue(OpcUaDataValue& dataValue)
	{
		std::string str = textWidget_->text().toStdString();
		// FIXME: todo
	}

	bool
	ValueWidget::checkValue(void)
	{
		// FIXME: todo
		return true;
	}

	void
	ValueWidget::styleValue(void)
	{
		if (isValid_) {
			textWidget_->setStyleSheet("background-color:none;");
		}
		else {
			textWidget_->setStyleSheet("background-color:red;");
		}
	}

	void
	ValueWidget::onTextChangedTextWidget(const QString& text)
	{
		if (!checkOn_) return;

		OpcUaDataValue dataValue;
		isValid_ = checkValue();
		styleValue();
		// FIXME: todo
	    emit update();
	}

}


