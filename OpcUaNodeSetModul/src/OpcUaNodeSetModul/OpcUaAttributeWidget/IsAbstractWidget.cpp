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
#include <QCheckBox>

#include "OpcUaNodeSetModul/OpcUaAttributeWidget/IsAbstractWidget.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{

	IsAbstractWidget::IsAbstractWidget(QWidget* parent)
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

	IsAbstractWidget::~IsAbstractWidget(void)
	{
	}

	bool
	IsAbstractWidget::isValid(void)
	{
		return isValid_;
	}

	void
	IsAbstractWidget::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullIsAbstract()) {
			checkboxWidget_->setCheckState(Qt::Unchecked);
		}

		checkOn_ = false;
		OpcUaBoolean isAbstract;
		baseNode->getIsAbstract(isAbstract);
		if (isAbstract == true) checkboxWidget_->setCheckState(Qt::Checked);
		else checkboxWidget_->setCheckState(Qt::Unchecked);
		isValid_ = checkValue();
		styleValue();
		checkOn_ = true;
	}

	void
	IsAbstractWidget::enabled(bool enabled)
	{
		checkboxWidget_->setEnabled(enabled);
	}

	void
	IsAbstractWidget::getValue(OpcUaBoolean& isAbstract)
	{
		Qt::CheckState state = checkboxWidget_->checkState();
		if (state == Qt::Checked) isAbstract = true;
		else isAbstract = false;
	}

	bool
	IsAbstractWidget::checkValue(void)
	{
		return true;
	}

	void
	IsAbstractWidget::styleValue(void)
	{
		// nothing to do
	}

	void
	IsAbstractWidget::onStateChanged(int stateCheckBox)
	{
		if (!checkOn_) return;

		OpcUaBoolean isAbstract;
		isValid_ = checkValue();
		styleValue();
		Qt::CheckState state = checkboxWidget_->checkState();
		if (state == Qt::Checked) isAbstract = true;
		else isAbstract = false;
		emit valueChanged(isAbstract, isValid_);
	    emit update();
	}

}


