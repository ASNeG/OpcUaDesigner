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
#include "OpcUaNodeSetModul/OpcUaTypeWidget/OpcUaStatusCodeWidget.h"

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

		// status code
		QHBoxLayout* statusCodeLayout = new QHBoxLayout();
		label = new QLabel(QString("StatusCode"));
		label->setFixedWidth(80);
		statusCodeLayout->addWidget(label);

		statusCodeExistWidget_ = new QCheckBox();
		statusCodeLayout->addWidget(statusCodeExistWidget_);

		statusCodeWidget_ = new OpcUaStatusCodeWidget();
		statusCodeLayout->addWidget(statusCodeWidget_);

		statusCodeLayout->addStretch();


		// source time
		QHBoxLayout* sourceTimeLayout = new QHBoxLayout();
		label = new QLabel(QString("SourceTime"));
		label->setFixedWidth(80);
		sourceTimeLayout->addWidget(label);

		sourceTimeExistWidget_ = new QCheckBox();
		sourceTimeLayout->addWidget(sourceTimeExistWidget_);

		sourceTimeValueWidget_ = new QDateTimeEdit();
		sourceTimeLayout->addWidget(sourceTimeValueWidget_);

		sourceTimeLayout->addStretch();


		// source time
		QHBoxLayout* serverTimeLayout = new QHBoxLayout();
		label = new QLabel(QString("ServerTime"));
		label->setFixedWidth(80);
		serverTimeLayout->addWidget(label);

		serverTimeExistWidget_ = new QCheckBox();
		serverTimeLayout->addWidget(serverTimeExistWidget_);

		serverTimeValueWidget_ = new QDateTimeEdit();
		serverTimeLayout->addWidget(serverTimeValueWidget_);

		serverTimeLayout->addStretch();


		// variable
		QHBoxLayout* variableLayout = new QHBoxLayout();
		label = new QLabel(QString("Variable"));
		label->setFixedWidth(80);
		variableLayout->addWidget(label);

		variableExistWidget_ = new QCheckBox();
		variableLayout->addWidget(variableExistWidget_);

		variableLayout->addStretch();


		// layout
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->addLayout(statusCodeLayout);
		vBoxLayout->addLayout(sourceTimeLayout);
		vBoxLayout->addLayout(serverTimeLayout);
		vBoxLayout->addLayout(variableLayout);
		vBoxLayout->setMargin(0);
		setLayout(vBoxLayout);

		//
		// actions
		//
		connect(
			statusCodeWidget_, SIGNAL(update()),
			this, SLOT(onUpdateStatusCode())
		);

	}

	OpcUaDataValueWidget::~OpcUaDataValueWidget(void)
	{
	}

	void
	OpcUaDataValueWidget::enabled(bool enabled)
	{
		statusCodeWidget_->setEnabled(enabled);
	}

	void
	OpcUaDataValueWidget::setSavedValue(OpcUaDataValue& savedValue)
	{
		savedValue_ = savedValue;

		OpcUaStatusCode statusCode;
		statusCode = savedValue_.statusCode();
		statusCodeWidget_->setSavedValue(statusCode);
	}

	void
	OpcUaDataValueWidget::setDisplayValue(OpcUaDataValue& displayValue)
	{
		displayValue_ = displayValue;

		OpcUaStatusCode statusCode;
		statusCode = savedValue_.statusCode();
		statusCodeWidget_->setDisplayValue(statusCode);
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
		return
		    statusCodeWidget_->isValid();
	}

	bool
	OpcUaDataValueWidget::acceptValue(void)
	{
		if (savedValue_ != displayValue_) {
			savedValue_ = displayValue_;

			statusCodeWidget_->acceptValue();

			return true;
		}
		return false;
	}


	void
	OpcUaDataValueWidget::resetValue(void)
	{
		statusCodeWidget_->resetValue();
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// added slots
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	OpcUaDataValueWidget::onUpdateStatusCode(void)
	{
		OpcUaStatusCode statusCode;
		statusCodeWidget_->getDisplayValue(statusCode);
		displayValue_.statusCode(statusCode);

		emit update();
	}

}


