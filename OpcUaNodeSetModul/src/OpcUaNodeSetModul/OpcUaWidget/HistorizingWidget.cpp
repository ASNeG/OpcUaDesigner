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

#include "OpcUaNodeSetModul/OpcUaWidget/HistorizingWidget.h"

namespace OpcUaNodeSet
{


	HistorizingWidget::HistorizingWidget(QWidget* parent)
	: QWidget()
	, checkOn_(true)
	, isValid_(true)
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

	HistorizingWidget::~HistorizingWidget(void)
	{
	}

	bool
	HistorizingWidget::isValid(void)
	{
		return isValid_;
	}

	void
	HistorizingWidget::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullHistorizing()) {
			checkboxWidget_->setCheckState(Qt::Unchecked);
		}

		checkOn_ = false;
		OpcUaBoolean historizing;
		baseNode->getHistorizing(historizing);
		if (historizing == true) checkboxWidget_->setCheckState(Qt::Checked);
		else checkboxWidget_->setCheckState(Qt::Unchecked);
		isValid_ = checkValue();
		styleValue();
		checkOn_ = true;
	}

	void
	HistorizingWidget::enabled(bool enabled)
	{
		checkboxWidget_->setEnabled(enabled);
	}

	void
	HistorizingWidget::getValue(OpcUaBoolean& historizing)
	{
		Qt::CheckState state = checkboxWidget_->checkState();
		if (state == Qt::Checked) historizing = true;
		else historizing = false;
	}

	bool
	HistorizingWidget::checkValue(void)
	{
		return true;
	}

	void
	HistorizingWidget::styleValue(void)
	{
		// nothing to do
	}

	void
	HistorizingWidget::onStateChanged(int stateCheckBox)
	{
		if (!checkOn_) return;

		OpcUaBoolean historizing;
		isValid_ = checkValue();
		styleValue();
		Qt::CheckState state = checkboxWidget_->checkState();
		if (state == Qt::Checked) historizing = true;
		else historizing = false;
		emit valueChanged(historizing, isValid_);
	    emit update();
	}

}


