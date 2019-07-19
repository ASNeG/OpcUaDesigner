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
#include <QComboBox>
#include <QStringList>
#include <QString>

#include "OpcUaNodeSetModul/OpcUaAttributeWidget/ValueRankWidget.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	ValueRankWidget::ValueRankWidget(QWidget* parent)
	: QWidget()
	, checkOn_(true)
	, isValid_(true)
	, savedValue_(-1)
	, displayValue_(-1)
	{
		// widgets
		QStringList typeList;
		typeList << "Scalar" << "Array" << "Any" << "OneOrMoreDimensions" << "ScalarOrOnedimension";
		comboBoxWidget_ = new QComboBox();
		comboBoxWidget_->addItems(typeList);
		comboBoxWidget_->setFixedWidth(200);

		textWidget_ = new QLineEdit();
		textWidget_->setFixedWidth(195);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(comboBoxWidget_);
		hBoxLayout->addWidget(textWidget_);
		hBoxLayout->setMargin(0);

		//
		// actions
		//
		connect(
			comboBoxWidget_, SIGNAL(currentIndexChanged(int)),
			this, SLOT(onCurrentIndexChangedComboboxWidget(int))
		);
		connect(
			textWidget_, SIGNAL(textChanged(const QString&)),
			this, SLOT(onTextChangedTextWidget(const QString&))
		);

		setLayout(hBoxLayout);
	}

	ValueRankWidget::~ValueRankWidget(void)
	{
	}

	bool
	ValueRankWidget::isValid(void)
	{
		return isValid_;
	}

	void
	ValueRankWidget::nodeChange(NodeInfo* nodeInfo)
	{
		OpcUaInt32 valueRank;
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullValueRank()) {
			valueRank = -1;
		}
		else {
			baseNode->getValueRank(valueRank);
		}
		setSavedValue(valueRank);
	}

	void
	ValueRankWidget::enabled(bool enabled)
	{
		comboBoxWidget_->setEnabled(enabled);
		textWidget_->setEnabled(enabled);
	}

	void
	ValueRankWidget::setSavedValue(OpcUaInt32& savedValue)
	{
		savedValue_ = savedValue;

		checkOn_ = false;
		setDisplayValue(savedValue);
		checkOn_ = true;
	}

	void
	ValueRankWidget::setDisplayValue(OpcUaInt32& displayValue)
	{
		displayValue_ = displayValue;

		textWidget_->setText(QString("%1").arg((int32_t)displayValue));
		if (displayValue == -3) { // ScalarOrOnedimension
			comboBoxWidget_->setCurrentIndex(4);
			textWidget_->setVisible(false);
		}
		else if (displayValue == -2) { // Any
			comboBoxWidget_->setCurrentIndex(2);
			textWidget_->setVisible(false);
		}
		else if (displayValue == -1) { // Scalar
			comboBoxWidget_->setCurrentIndex(0);
			textWidget_->setVisible(false);
		}
		else if (displayValue == 0) { // OneOrMoreDimensions
			comboBoxWidget_->setCurrentIndex(3);
			textWidget_->setVisible(false);
		}
		else if (displayValue > 0) { // Array
			comboBoxWidget_->setCurrentIndex(1);
			textWidget_->setVisible(true);
		}
	}

	void
	ValueRankWidget::getSavedValue(OpcUaInt32& savedValue)
	{
		savedValue = savedValue_;
	}

	void
	ValueRankWidget::getDisplayValue(OpcUaInt32& displayValue)
	{
		displayValue = displayValue_;
	}

	bool
	ValueRankWidget::acceptValue(void)
	{
		if (savedValue_ != displayValue_) {
			savedValue_ = displayValue_;
			return true;
		}
		return false;
	}

	void
	ValueRankWidget::resetValue(void)
	{
		setDisplayValue(savedValue_);
	}

	void
	ValueRankWidget::styleValue(void)
	{
		if (isValid_) {
			textWidget_->setStyleSheet("background-color:none;");
		}
		else {
			textWidget_->setStyleSheet("background-color:red;");
		}
	}

	void
	ValueRankWidget::onTextChangedTextWidget(const QString& text)
	{
		if (!checkOn_) return;

		isValid_ = true;

		bool rc;
		OpcUaInt32 valueRank;
		valueRank = textWidget_->text().toInt(&rc);

		if (valueRank < 1) {
			isValid_ = false;
		}
		if (valueRank >= 0) {
			comboBoxWidget_->setCurrentIndex(1);
			displayValue_ = valueRank;
		}

		styleValue();

		if (savedValue_ != displayValue_) {
			emit update();
		}
	}

	void
	ValueRankWidget::onCurrentIndexChangedComboboxWidget(int index)
	{
		if (index == 4) { // ScalarOrOnedimension
			textWidget_->setVisible(false);
			displayValue_ = -3;
		}
		else if (index == 2) { // Any
			textWidget_->setVisible(false);
			displayValue_ = -2;
		}
		else if (index == 0) { // Scalar
			textWidget_->setVisible(false);
			displayValue_ = -1;
		}
		else if (index == 3) { // OneOrMoreDimensions
			textWidget_->setVisible(false);
			displayValue_ = 0;
		}
		else if (index == 1) { // Array
			textWidget_->setVisible(true);
			displayValue_ = 1;
			textWidget_->setText(QString("1"));
		}

		isValid_ = true;
		styleValue();

		if (savedValue_ != displayValue_) {
			emit update();
		}
	}

}


