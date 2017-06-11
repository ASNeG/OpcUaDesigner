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
#include <QPushButton>

#include "OpcUaNodeSetModul/OpcUaWidget/ObjectTypeWidget.h"

namespace OpcUaNodeSet
{


	ObjectTypeWidget::ObjectTypeWidget(QWidget* parent)
	: QWidget()
	, informationModel_()
	, objectType_()
	, isValid_(false)
	, checkOn_(true)
	{
		// widgets
		textWidget_ = new QLineEdit();
		textWidget_->setFixedWidth(370-5);

		buttonWidget_ = new QPushButton();
		buttonWidget_->setFixedWidth(30);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(textWidget_);
		hBoxLayout->addWidget(buttonWidget_);
		hBoxLayout->setMargin(0);

		//
		// actions
		//
		connect(
			textWidget_, SIGNAL(textChanged(const QString&)),
			this, SLOT(onTextChanged(const QString&))
		);
		connect(
			buttonWidget_, SIGNAL(clicked()),
			this, SLOT(onClicked())
		);

		setLayout(hBoxLayout);
	}

	ObjectTypeWidget::~ObjectTypeWidget(void)
	{
	}

	void
	ObjectTypeWidget::setValue(InformationModel::SPtr& informationModel)
	{
		informationModel_ = informationModel;
	}

	void
	ObjectTypeWidget::setValue(OpcUaNodeId& objectType)
	{
		objectType_ = objectType;
		checkOn_ = false;
		showValue();
		checkOn_ = true;
		isValid_ = checkValue();
		styleValue();
		emit valueChanged(objectType_, isValid_);
	}

	void
	ObjectTypeWidget::getValue(OpcUaNodeId& objectType)
	{
		objectType = objectType_;
	}

	bool
	ObjectTypeWidget::isValid(void)
	{
		return isValid_;
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	ObjectTypeWidget::showValue(void)
	{
		// FIXME: todo
	}

	bool
	ObjectTypeWidget::checkValue(void)
	{
		// FIXME: todo
		return true;
	}

	void
	ObjectTypeWidget::styleValue(void)
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
	ObjectTypeWidget::onTextChanged(const QString& text)
	{
		if (!checkOn_) return;
		isValid_ = checkValue();
		styleValue();
		emit valueChanged(objectType_, isValid_);
	}

	void
	ObjectTypeWidget::onClicked(void)
	{
		emit selectObjectType();
	}


}


