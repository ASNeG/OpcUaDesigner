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
#include <QIcon>

#include "OpcUaNodeSetModul/OpcUaTypeWidget/OpcUaVariantWidget.h"

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{


	OpcUaVariantWidget::OpcUaVariantWidget(QWidget* parent)
	: QWidget()
	, savedValue_()
	, displayValue_()
	, isValid_(false)
	, checkOn_(true)
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
			this, SLOT(onTextChanged(const QString&))
		);

		setLayout(hBoxLayout);
	}

	OpcUaVariantWidget::~OpcUaVariantWidget(void)
	{
	}

	void
	OpcUaVariantWidget::enabled(bool enabled)
	{
		textWidget_->setEnabled(enabled);
	}

	void
	OpcUaVariantWidget::setSavedValue(OpcUaVariant& savedValue)
	{
		savedValue_ = savedValue;

		checkOn_ = false;
		setDisplayValue(savedValue);
		checkOn_ = true;
	}

	void
	OpcUaVariantWidget::setDisplayValue(OpcUaVariant& displayValue)
	{
		displayValue_ = displayValue;

		styleValue();
	}

	void
	OpcUaVariantWidget::getSavedValue(OpcUaVariant& savedValue)
	{
		savedValue = savedValue_;
	}

	void
	OpcUaVariantWidget::getDisplayValue(OpcUaVariant& displayValue)
	{
		displayValue = displayValue_;
	}

	bool
	OpcUaVariantWidget::isValid(void)
	{
		return isValid_;
	}

	bool
	OpcUaVariantWidget::acceptValue(void)
	{
		if (savedValue_ != displayValue_) {
			savedValue_ = displayValue_;
			return true;
		}
		return false;
	}


	void
	OpcUaVariantWidget::resetValue(void)
	{
		setDisplayValue(savedValue_);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// added slots
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	OpcUaVariantWidget::onTextChanged(const QString& text)
	{
		if (!checkOn_) return;

		styleValue();
		if (savedValue_ != displayValue_) {
			emit update();
		}
	}

	void
	OpcUaVariantWidget::onClicked(void)
	{
		emit selectDataType();
	}


	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	OpcUaVariantWidget::styleValue(void)
	{
		if (isValid_) {
			textWidget_->setStyleSheet("background-color:none;");
		}
		else {
			textWidget_->setStyleSheet("background-color:red;");
		}
	}

}


