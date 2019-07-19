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
#include <QLineEdit>

#include "OpcUaNodeSetModul/OpcUaAttributeWidget/DisplayNameWidget.h"

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{


	DisplayNameWidget::DisplayNameWidget(QWidget* parent)
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

	DisplayNameWidget::~DisplayNameWidget(void)
	{
	}

	void
	DisplayNameWidget::setValue(OpcUaLocalizedText& displayName)
	{
		displayName_ = displayName;
		checkOn_ = false;
		showValue();
		checkOn_ = true;
		isValid_ = checkValue();
		styleValue();
		//emit valueChanged(displayName_, isValid_);
	}

	void
	DisplayNameWidget::getValue(OpcUaLocalizedText& displayName)
	{
		displayName = displayName_;
	}

	bool
	DisplayNameWidget::isValid(void)
	{
		return isValid_;
	}

	void
	DisplayNameWidget::enabled(bool enabled)
	{
		localeWidget_->setEnabled(enabled);
		textWidget_->setEnabled(enabled);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	DisplayNameWidget::showValue(void)
	{
		std::string locale;
		std::string text;
		displayName_.get(locale, text);

		localeWidget_->setText(locale.c_str());
		textWidget_->setText(text.c_str());
	}

	bool
	DisplayNameWidget::checkValue(void)
	{
		if (textWidget_->text().length() == 0) return false;
		return true;
	}

	void
	DisplayNameWidget::styleValue(void)
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
	DisplayNameWidget::onTextChangedLocale(const QString& text)
	{
		if (!checkOn_) return;
		isValid_ = checkValue();
		styleValue();

		// set value
		if (isValid_) {
			displayName_.set(
				localeWidget_->text().toStdString(),
				textWidget_->text().toStdString()
			);
		}
		emit valueChanged(displayName_, isValid_);
		emit update();
	}

	void
	DisplayNameWidget::onTextChangedText(const QString& text)
	{
		if (!checkOn_) return;
		isValid_ = checkValue();
		styleValue();

		// set value
		if (isValid_) {
			displayName_.set(
				localeWidget_->text().toStdString(),
				textWidget_->text().toStdString()
			);
		}
		emit valueChanged(displayName_, isValid_);
		emit update();
	}


}


