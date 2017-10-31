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
#include <QDateTimeEdit>
#include <QLabel>
#include <QIcon>

#include "OpcUaNodeSetModul/OpcUaTypeWidget/OpcUaDataValueWidget.h"

namespace OpcUaNodeSet
{


	OpcUaDataValueWidget::OpcUaDataValueWidget(QWidget* parent)
	: QWidget()
	, savedValue_()
	, displayValue_()
	, isValid_(false)
	, checkOn_(true)
	{
		QLabel* label;

		// --------------------------------------------------------------------
		// --------------------------------------------------------------------
		//
		// widgets
		//
		// --------------------------------------------------------------------
		// --------------------------------------------------------------------


#if 0
		textWidget_ = new QLineEdit();
		textWidget_->setFixedWidth(365);

		buttonWidget_ = new QPushButton();
		buttonWidget_->setIcon(QIcon(":/images/Tree.png"));
		buttonWidget_->setFixedWidth(30);
#endif


		// source time
		QHBoxLayout* sourceTimeLayout = new QHBoxLayout();
		label = new QLabel(QString("SourceTime"));
		sourceTimeLayout->addWidget(label);

		sourceTimeExistWidget_ = new QCheckBox();
		sourceTimeLayout->addWidget(sourceTimeExistWidget_);

		sourceTimeValueWidget_ = new QDateTimeEdit();
		sourceTimeLayout->addWidget(sourceTimeValueWidget_);


		// source time
		QHBoxLayout* serverTimeLayout = new QHBoxLayout();
		label = new QLabel(QString("ServerTime"));
		serverTimeLayout->addWidget(label);

		serverTimeExistWidget_ = new QCheckBox();
		serverTimeLayout->addWidget(serverTimeExistWidget_);

		serverTimeValueWidget_ = new QDateTimeEdit();
		serverTimeLayout->addWidget(serverTimeValueWidget_);


		// layout
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->addLayout(sourceTimeLayout);
		vBoxLayout->addLayout(serverTimeLayout);
		vBoxLayout->setMargin(0);
		setLayout(vBoxLayout);

		//
		// actions
		//
#if 0
		connect(
			textWidget_, SIGNAL(textChanged(const QString&)),
			this, SLOT(onTextChanged(const QString&))
		);
		connect(
			buttonWidget_, SIGNAL(clicked()),
			this, SLOT(onClicked())
		);
#endif
	}

	OpcUaDataValueWidget::~OpcUaDataValueWidget(void)
	{
	}

	void
	OpcUaDataValueWidget::enabled(bool enabled)
	{
		//textWidget_->setEnabled(enabled);
		//buttonWidget_->setEnabled(enabled);
	}

	void
	OpcUaDataValueWidget::setSavedValue(OpcUaDataValue& savedValue)
	{
		savedValue_ = savedValue;

		checkOn_ = false;
		setDisplayValue(savedValue);
		checkOn_ = true;
	}

	void
	OpcUaDataValueWidget::setDisplayValue(OpcUaDataValue& displayValue)
	{
		displayValue_ = displayValue;

		styleValue();
	}

	void
	OpcUaDataValueWidget::getSavedValue(OpcUaDataValue& savedValue)
	{
		savedValue = savedValue_;
	}

	void
	OpcUaDataValueWidget::getDisplayValue(OpcUaDataValue& displayValue)
	{
		displayValue = displayValue_;
	}

	bool
	OpcUaDataValueWidget::isValid(void)
	{
		return isValid_;
	}

	bool
	OpcUaDataValueWidget::acceptValue(void)
	{
		if (savedValue_ != displayValue_) {
			savedValue_ = displayValue_;
			return true;
		}
		return false;
	}


	void
	OpcUaDataValueWidget::resetValue(void)
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
	OpcUaDataValueWidget::onTextChanged(const QString& text)
	{
		if (!checkOn_) return;

		styleValue();
		if (savedValue_ != displayValue_) {
			emit update();
		}
	}

	void
	OpcUaDataValueWidget::onClicked(void)
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
	OpcUaDataValueWidget::styleValue(void)
	{
		if (isValid_) {
			//textWidget_->setStyleSheet("background-color:none;");
		}
		else {
			//textWidget_->setStyleSheet("background-color:red;");
		}
	}

}


