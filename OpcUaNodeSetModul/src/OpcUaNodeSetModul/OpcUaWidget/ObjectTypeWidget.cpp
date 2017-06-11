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

#include "OpcUaNodeSetModul/OpcUaWidget/ObjectTypeWidget.h"

namespace OpcUaNodeSet
{


	ObjectTypeWidget::ObjectTypeWidget(QWidget* parent)
	: QWidget()
	, displayName_()
	, isValid_(false)
	, checkOn_(true)
	{
		// widgets
		localeWidget_ = new QLineEdit();
		localeWidget_->setFixedWidth(50);

		textWidget_ = new QLineEdit();
		textWidget_->setFixedWidth(350-5);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(localeWidget_);
		hBoxLayout->addWidget(textWidget_);
		hBoxLayout->setMargin(0);

		//
		// actions
		//
		connect(
			localeWidget_, SIGNAL(textChanged(const QString&)),
			this, SLOT(onTextChangedLocale(const QString&))
		);
		connect(
			textWidget_, SIGNAL(textChanged(const QString&)),
			this, SLOT(onTextChangedText(const QString&))
		);

		setLayout(hBoxLayout);
	}

	ObjectTypeWidget::~ObjectTypeWidget(void)
	{
	}

	void
	ObjectTypeWidget::setValue(OpcUaLocalizedText& displayName)
	{
		displayName_ = displayName;
		checkOn_ = false;
		showValue();
		checkOn_ = true;
		isValid_ = checkValue();
		styleValue();
		emit valueChanged(displayName_, isValid_);
	}

	void
	ObjectTypeWidget::getValue(OpcUaLocalizedText& displayName)
	{
		displayName = displayName_;
	}

	bool
	ObjectTypeWidget::isValid(void)
	{
		return isValid_;
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	ObjectTypeWidget::showValue(void)
	{
		std::string locale;
		std::string text;
		displayName_.get(locale, text);

		localeWidget_->setText(locale.c_str());
		textWidget_->setText(text.c_str());
	}

	bool
	ObjectTypeWidget::checkValue(void)
	{
		if (textWidget_->text().length() == 0) return false;
		return true;
	}

	void
	ObjectTypeWidget::styleValue(void)
	{
		if (isValid_) {
			textWidget_->setStyleSheet("background-color:none;");
		}
		else {
			textWidget_->setStyleSheet("background-color:red;");
		}
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// added slots
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	ObjectTypeWidget::onTextChangedLocale(const QString& text)
	{
		if (!checkOn_) return;
		isValid_ = checkValue();
		styleValue();
		emit valueChanged(displayName_, isValid_);
	}

	void
	ObjectTypeWidget::onTextChangedText(const QString& text)
	{
		if (!checkOn_) return;
		isValid_ = checkValue();
		styleValue();
		emit valueChanged(displayName_, isValid_);
	}


}


