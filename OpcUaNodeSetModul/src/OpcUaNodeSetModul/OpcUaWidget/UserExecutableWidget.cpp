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

#include "OpcUaNodeSetModul/OpcUaWidget/UserExecutableWidget.h"

namespace OpcUaNodeSet
{


	UserExecutableWidget::UserExecutableWidget(QWidget* parent)
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

	UserExecutableWidget::~UserExecutableWidget(void)
	{
	}

	bool
	UserExecutableWidget::isValid(void)
	{
		return isValid_;
	}

	void
	UserExecutableWidget::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullUserExecutable()) {
			checkboxWidget_->setCheckState(Qt::Unchecked);
		}

		checkOn_ = false;
		OpcUaBoolean userExecutable;
		baseNode->getUserExecutable(userExecutable);
		if (userExecutable == true) checkboxWidget_->setCheckState(Qt::Checked);
		else checkboxWidget_->setCheckState(Qt::Unchecked);
		isValid_ = checkValue();
		styleValue();
		checkOn_ = true;
	}

	void
	UserExecutableWidget::enabled(bool enabled)
	{
		checkboxWidget_->setEnabled(enabled);
	}

	void
	UserExecutableWidget::getValue(OpcUaBoolean& userExecutable)
	{
		Qt::CheckState state = checkboxWidget_->checkState();
		if (state == Qt::Checked) userExecutable = true;
		else userExecutable = false;
	}

	bool
	UserExecutableWidget::checkValue(void)
	{
		return true;
	}

	void
	UserExecutableWidget::styleValue(void)
	{
		// nothing to do
	}

	void
	UserExecutableWidget::onStateChanged(int stateCheckBox)
	{
		if (!checkOn_) return;

		OpcUaBoolean userExecutable;
		isValid_ = checkValue();
		styleValue();
		Qt::CheckState state = checkboxWidget_->checkState();
		if (state == Qt::Checked) userExecutable = true;
		else userExecutable = false;
		emit valueChanged(userExecutable, isValid_);
	    emit update();
	}

}


