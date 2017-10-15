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

#include "OpcUaNodeSetModul/OpcUaWidget/ArrayDimensionsWidget.h"

namespace OpcUaNodeSet
{


	ArrayDimensionsWidget::ArrayDimensionsWidget(QWidget* parent)
	: QWidget()
	, checkOn_(true)
	, isValid_(true)
	{
		// widgets
		textWidget_ = new QLineEdit();
		textWidget_->setFixedWidth(400);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(textWidget_);
		hBoxLayout->setMargin(0);

		//
		// actions
		//
		connect(
			textWidget_, SIGNAL(textChanged(const QString&)),
			this, SLOT(onTextChangedTextWidget(const QString&))
		);

		setLayout(hBoxLayout);
	}

	ArrayDimensionsWidget::~ArrayDimensionsWidget(void)
	{
	}

	bool
	ArrayDimensionsWidget::isValid(void)
	{
		return isValid_;
	}

	void
	ArrayDimensionsWidget::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullArrayDimensions()) {
			textWidget_->setText(QString(""));
		}

		checkOn_ = false;
		OpcUaUInt32Array arrayDimensions;
		baseNode->getArrayDimensions(arrayDimensions);
		std::stringstream ss;
		arrayDimensions.out(ss);
		textWidget_->setText(QString(ss.str().c_str()));
		isValid_ = checkValue();
		styleValue();
		checkOn_ = true;
	}

	void
	ArrayDimensionsWidget::enabled(bool enabled)
	{
		textWidget_->setEnabled(enabled);
	}

	void
	ArrayDimensionsWidget::getValue(OpcUaByte& accessLevel)
	{
		bool rc;
		accessLevel = textWidget_->text().toInt(&rc);
	}

	bool
	ArrayDimensionsWidget::checkValue(void)
	{
		// FIXME: todo
		return true;
	}

	void
	ArrayDimensionsWidget::styleValue(void)
	{
		if (isValid_) {
			textWidget_->setStyleSheet("background-color:none;");
		}
		else {
			textWidget_->setStyleSheet("background-color:red;");
		}
	}

	void
	ArrayDimensionsWidget::onTextChangedTextWidget(const QString& text)
	{
		if (!checkOn_) return;

		OpcUaUInt32Array arrayDimensions;
		isValid_ = checkValue();
		styleValue();
		// FIXME: todo
		emit valueChanged(arrayDimensions, isValid_);
	    emit update();
	}

}

