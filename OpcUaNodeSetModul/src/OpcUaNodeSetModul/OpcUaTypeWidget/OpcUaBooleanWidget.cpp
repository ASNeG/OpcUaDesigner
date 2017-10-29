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
#include <QCheckBox>

#include "OpcUaNodeSetModul/OpcUaTypeWidget/OpcUaBooleanWidget.h"

namespace OpcUaNodeSet
{

	OpcUaBooleanWidget::OpcUaBooleanWidget(QWidget* parent)
	: QWidget()
	, checkOn_(true)
	, isValid_(true)
	, value_(true)
	, newValue_(true)
	{
		// widgets
		checkboxWidget_ = new QCheckBox();

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(checkboxWidget_);
		hBoxLayout->setMargin(0);

		//
		// actions
		//
		connect(
			checkboxWidget_, SIGNAL(stateChanged(int)),
			this, SLOT(onStateChanged(int))
		);

		setLayout(hBoxLayout);
	}

	OpcUaBooleanWidget::~OpcUaBooleanWidget(void)
	{
	}

	bool
	OpcUaBooleanWidget::isValid(void)
	{
		return isValid_;
	}

	void
	OpcUaBooleanWidget::enabled(bool enabled)
	{
		checkboxWidget_->setEnabled(enabled);
	}

	void
	OpcUaBooleanWidget::setValue(OpcUaBoolean& value)
	{
		value_ = value;
		newValue_ = value;

		checkOn_ = false;
		if (value == true) checkboxWidget_->setCheckState(Qt::Checked);
		else checkboxWidget_->setCheckState(Qt::Unchecked);
		isValid_ = checkValue();
		styleValue();
		checkOn_ = true;
	}

	void
	OpcUaBooleanWidget::getOldValue(OpcUaBoolean& value)
	{
		value = value_;
	}

	void
	OpcUaBooleanWidget::getNewValue(OpcUaBoolean& value)
	{
		value = newValue_;
	}

	bool
	OpcUaBooleanWidget::acceptValue(void)
	{
		if (value_ == newValue_) return false;
		value_ = newValue_;
		return true;
	}

	void
	OpcUaBooleanWidget::resetValue(void)
	{
		setValue(value_);
	}

	bool
	OpcUaBooleanWidget::checkValue(void)
	{
		return true;
	}

	void
	OpcUaBooleanWidget::styleValue(void)
	{
		// nothing to do
	}

	void
	OpcUaBooleanWidget::onStateChanged(int stateCheckBox)
	{
		if (!checkOn_) return;

		isValid_ = checkValue();
		styleValue();

		if (checkboxWidget_->checkState() == Qt::Checked) {
			newValue_ = true;
		}
		else {
			newValue_ = false;
		}

		if (value_ != newValue_) {
			emit update();
		}
	}

}


