/*
 Copyright 2016-2019 Samuel Huebl (samuel@huebl-sgh.de)

 Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
 Datei nur in Übereinstimmung mit der Lizenz erlaubt.
 Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

 Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
 erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
 GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

 Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
 im Rahmen der Lizenz finden Sie in der Lizenz.

 Autor: Samuel Huebl (samuel@huebl-sgh.de)
        Kai Huebl (kai@huebl-sgh.de)
 */

#include "OpcUaClientModul/ModulMainWidgets/ValueWidget.h"

using namespace OpcUaStackCore;

namespace OpcUaClientModul
{

	ValueWidget::ValueWidget()
	: QWidget()
	, baseNode_(nullptr)
	{
		QHBoxLayout* hBoxLayout;

		vBoxLayout_ = new QVBoxLayout();
		vBoxLayout_->setMargin(0);

		// set line widget
		LineWidget* lineWidget = new LineWidget();
		vBoxLayout_->addWidget(lineWidget);

		// set value layout
		QLabel* valueLabel = new QLabel("Value");
		valueLabel->setFixedWidth(140);

		valueEditWidget_ = new QLineEdit();
		valueEditWidget_->setFixedWidth(250);

		connect(
				valueEditWidget_, SIGNAL(returnPressed()),
				this, SLOT(slotWrite())
		);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->setSpacing(5);
		hBoxLayout->addWidget(valueLabel);
		hBoxLayout->addWidget(valueEditWidget_);
		hBoxLayout->addStretch();

		vBoxLayout_->addLayout(hBoxLayout);

		// set source time stamp layout
 		QLabel* sourceTimestampLabel = new QLabel("SourceTimestamp");
		sourceTimestampLabel->setFixedWidth(140);

		sourceTimestampWidget_ = new QLabel();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->setSpacing(5);
		hBoxLayout->addWidget(sourceTimestampLabel);
		hBoxLayout->addWidget(sourceTimestampWidget_);

		vBoxLayout_->addLayout(hBoxLayout);

		// set server time stamp layout
		QLabel* serverTimestampLabel = new QLabel("ServerTimestamp");
		serverTimestampLabel->setFixedWidth(140);

		serverTimestampWidget_ = new QLabel();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->setSpacing(5);
		hBoxLayout->addWidget(serverTimestampLabel);
		hBoxLayout->addWidget(serverTimestampWidget_);

		vBoxLayout_->addLayout(hBoxLayout);

//		// set status widget // TODO status für ein write anzeigen?
//		statusWidget_ = new QLabel("Success");
//		statusWidget_->setContentsMargins(140, 0, 0, 0);
//		statusWidget_->setStyleSheet("QLabel { color : green; }");
//
//		vBoxLayout_->addWidget(statusWidget_);

		// set layout
		setLayout(vBoxLayout_);

		// hide the widget
		hide();
	}

	ValueWidget::~ValueWidget()
	{
	}

	void
	ValueWidget::nodeChange(BaseNode* baseNode)
	{
		if (baseNode->dataValue() != nullptr)
		{
			// set ref
			baseNode_ = baseNode;

			// set value
			std::stringstream ss;
			baseNode->dataValue()->variant()->out(ss);
			valueEditWidget_->setText(ss.str().c_str());

			// set source and server time stamp
			std::stringstream sourceTimeStampSS;
			sourceTimeStampSS << baseNode->dataValue()->sourceTimestamp().dateTime();
			sourceTimestampWidget_->setText(sourceTimeStampSS.str().c_str());

			std::stringstream serverTimeStampSS;
			serverTimeStampSS << baseNode->dataValue()->serverTimestamp().dateTime();
			serverTimestampWidget_->setText(serverTimeStampSS.str().c_str());

			// show the widget
			show();
		}
		else
		{
			baseNode_ = nullptr;

			// hide the widget
			hide();
		}
	}

	void
	ValueWidget::slotWrite()
	{
		if (baseNode_ == nullptr)
		{
			return;
		}

		std::cout << "writeSignal" << std::endl;

		QString valueString = valueEditWidget_->text();
		OpcUaVariant::SPtr variant = baseNode_->dataValue()->variant();
		bool result = variant->fromString(variant->variantType(), variant->isArray(), valueString.toStdString());

		if (result)
		{
			emit signalWrite(baseNode_);
		}
		else
		{
			// TODO show error toast
		}

		std::cout << "writeSignal finished" << std::endl;
	}

} /* namespace OpcUaClientModul */
