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

#include "OpcUaNodeSetModul/OpcUaWidget/MinimumSamplingIntervalWidget.h"

namespace OpcUaNodeSet
{


	MinimumSamplingIntervalWidget::MinimumSamplingIntervalWidget(QWidget* parent)
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

	MinimumSamplingIntervalWidget::~MinimumSamplingIntervalWidget(void)
	{
	}

	bool
	MinimumSamplingIntervalWidget::isValid(void)
	{
		return isValid_;
	}

	void
	MinimumSamplingIntervalWidget::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullMinimumSamplingInterval()) {
			textWidget_->setText(QString("0"));
		}

		checkOn_ = false;
		OpcUaDouble minimumSamplingInterval;
		baseNode->getMinimumSamplingInterval(minimumSamplingInterval);
		textWidget_->setText(QString("%1").arg((double)minimumSamplingInterval));
		isValid_ = checkValue();
		styleValue();
		checkOn_ = true;
	}

	void
	MinimumSamplingIntervalWidget::enabled(bool enabled)
	{
		textWidget_->setEnabled(enabled);
	}

	void
	MinimumSamplingIntervalWidget::getValue(OpcUaDouble& minimumSamplingInterval)
	{
		bool rc;
		minimumSamplingInterval = textWidget_->text().toDouble(&rc);
	}

	bool
	MinimumSamplingIntervalWidget::checkValue(void)
	{
		textWidget_->text().toDouble(&isValid_);
		return isValid_;
	}

	void
	MinimumSamplingIntervalWidget::styleValue(void)
	{
		if (isValid_) {
			textWidget_->setStyleSheet("background-color:none;");
		}
		else {
			textWidget_->setStyleSheet("background-color:red;");
		}
	}

	void
	MinimumSamplingIntervalWidget::onTextChangedTextWidget(const QString& text)
	{
		if (!checkOn_) return;

		OpcUaDouble minimumSamplingInterval;
		isValid_ = checkValue();
		styleValue();
		bool rc;
		minimumSamplingInterval = textWidget_->text().toDouble(&rc);
		emit valueChanged(minimumSamplingInterval, isValid_);
	    emit update();
	}

}


