/*
   Copyright 2017-2019 Kai Huebl (kai@huebl-sgh.de)

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

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{

	OpcUaBooleanWidget::OpcUaBooleanWidget(QWidget* parent)
	: QWidget()
	, checkOn_(true)
	, isValid_(true)
	, savedValue_(true)
	, displayValue_(true)
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
	OpcUaBooleanWidget::setSavedValue(OpcUaBoolean& savedValue)
	{
		savedValue_ = savedValue;

		checkOn_ = false;
		setDisplayValue(savedValue);
		checkOn_ = true;
	}

	void
	OpcUaBooleanWidget::setDisplayValue(OpcUaBoolean& displayValue)
	{
		displayValue_ = displayValue;

		if (displayValue_ == true) checkboxWidget_->setCheckState(Qt::Checked);
		else checkboxWidget_->setCheckState(Qt::Unchecked);
	}

	void
	OpcUaBooleanWidget::getSavedValue(OpcUaBoolean& savedValue)
	{
		savedValue = savedValue_;
	}

	void
	OpcUaBooleanWidget::getDisplayValue(OpcUaBoolean& displayValue)
	{
		displayValue = displayValue_;
	}

	bool
	OpcUaBooleanWidget::acceptValue(void)
	{
		if (savedValue_ != displayValue_) {
			savedValue_ = displayValue_;
			return true;
		}
		return false;
	}

	void
	OpcUaBooleanWidget::resetValue(void)
	{
		setDisplayValue(savedValue_);
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
			displayValue_ = true;
		}
		else {
			displayValue_ = false;
		}

		if (savedValue_ != displayValue_) {
			emit update();
		}
	}

}


