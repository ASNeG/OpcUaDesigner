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

#include <vector>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QIcon>

#include "OpcUaStackCore/BuildInTypes/OpcUaStatusCode.h"
#include "OpcUaNodeSetModul/OpcUaTypeWidget/OpcUaStatusCodeWidget.h"

namespace OpcUaNodeSet
{


	OpcUaStatusCodeWidget::OpcUaStatusCodeWidget(QWidget* parent)
	: QWidget()
	, savedValue_()
	, displayValue_()
	, isValid_(false)
	, checkOn_(true)
	{
		std::vector<std::string> statucCodeVec;
		std::vector<std::string>::iterator it;
		OpcUaStatusCodeMap::getStatusCodeVec(statucCodeVec);
		for (it = statucCodeVec.begin(); it != statucCodeVec.end(); it++) {
			statusCodeList_ << QString(it->c_str());
		}
		statusCodeList_ << "Error";

		// widgets
		comboBoxWidget_ = new QComboBox();
		comboBoxWidget_->addItems(statusCodeList_);
		comboBoxWidget_->setFixedWidth(290);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(comboBoxWidget_);
		hBoxLayout->setMargin(0);

		//
		// actions
		//
		connect(
			comboBoxWidget_, SIGNAL(currentTextChanged(const QString&)),
			this, SLOT(onCurrentTextChanged(const QString&))
		);

		setLayout(hBoxLayout);
	}

	OpcUaStatusCodeWidget::~OpcUaStatusCodeWidget(void)
	{
	}

	void
	OpcUaStatusCodeWidget::enabled(bool enabled)
	{
		comboBoxWidget_->setEnabled(enabled);
	}

	void
	OpcUaStatusCodeWidget::setSavedValue(OpcUaStatusCode& savedValue)
	{
		savedValue_ = savedValue;

		checkOn_ = false;
		setDisplayValue(savedValue);
		checkOn_ = true;
	}

	void
	OpcUaStatusCodeWidget::setDisplayValue(OpcUaStatusCode& displayValue)
	{
		displayValue_ = displayValue;

		std::string statusCodeString = OpcUaStatusCodeMap::shortString(displayValue);
		if (statusCodeString == "") statusCodeString = "Error";
		comboBoxWidget_->setCurrentText(QString(statusCodeString.c_str()));

		styleValue();
	}

	void
	OpcUaStatusCodeWidget::getSavedValue(OpcUaStatusCode& savedValue)
	{
		savedValue = savedValue_;
	}

	void
	OpcUaStatusCodeWidget::getDisplayValue(OpcUaStatusCode& displayValue)
	{
		displayValue = displayValue_;
	}

	bool
	OpcUaStatusCodeWidget::isValid(void)
	{
		return isValid_;
	}

	bool
	OpcUaStatusCodeWidget::acceptValue(void)
	{
		if (savedValue_ != displayValue_) {
			savedValue_ = displayValue_;
			return true;
		}
		return false;
	}


	void
	OpcUaStatusCodeWidget::resetValue(void)
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
	OpcUaStatusCodeWidget::onCurrentTextChanged(const QString& text)
	{
		if (!checkOn_) return;

		displayValue_ = OpcUaStatusCodeMap::statusCode(text.toStdString());
		if (displayValue_ == BadStatusCodeUnknown) {
			isValid_ = false;
		}
		else {
			isValid_ = true;
		}

		std::cout << "isValid=" << isValid_ << std::endl;
		styleValue();
		if (savedValue_ != displayValue_) {
			emit update();
		}
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	OpcUaStatusCodeWidget::styleValue(void)
	{
		// nothing to do
	}

}


