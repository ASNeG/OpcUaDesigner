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
#include <QLineEdit>
#include <QComboBox>
#include <QStringList>
#include <QString>

#include "OpcUaNodeSetModul/OpcUaWidget/NodeClassWidget.h"

namespace OpcUaNodeSet
{


	NodeClassWidget::NodeClassWidget(QWidget* parent)
	: QWidget(parent)
	, nodeClassType_()
	, nodeClassList_()
	, isValid_(false)
	, checkOn_(true)
	{
		nodeClassList_ << "Object" << "Variable" << "Method" << "ObjectType"
			<< "VariableType" << "ReferenceType" << "DataType" << "View";

		nodeClassType_ = NodeClass::toNodeClassType(nodeClassList_[0].toStdString());

		createLayout();

	}

	NodeClassWidget::NodeClassWidget(QStringList& nodeClassList, QWidget* parent)
	: QWidget(parent)
	, nodeClassType_(NodeClassType_Object)
	, nodeClassList_(nodeClassList)
	, isValid_(false)
	, checkOn_(true)
	{
		if (nodeClassList_.size() > 0) {
			nodeClassType_ = NodeClass::toNodeClassType(nodeClassList_[0].toStdString());
		}

		createLayout();
	}

	NodeClassWidget::~NodeClassWidget(void)
	{
	}

	void
	NodeClassWidget::setValue(QStringList& nodeClassList)
	{
		nodeClassList_ = nodeClassList;

		nodeClassWidget_->clear();
		nodeClassWidget_->addItems(nodeClassList_);
	}

	void
	NodeClassWidget::setValue(NodeClassType nodeClassType)
	{
		nodeClassType_ = nodeClassType;

		showValue();
		isValid_ = checkValue();
		styleValue();
		emit valueChanged(nodeClassType_, isValid_);
	}

	void
	NodeClassWidget::getValue(NodeClassType& nodeClassType)
	{
		nodeClassType = nodeClassType_;
	}

	bool
	NodeClassWidget::isValid(void)
	{
		return isValid_;
	}

	void
	NodeClassWidget::enabled(bool enabled)
	{
		nodeClassWidget_->setEnabled(enabled);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	NodeClassWidget::showValue(void)
	{
		nodeClassWidget_->setCurrentText(QString(NodeClass::toString(nodeClassType_).c_str()));
	}

	bool
	NodeClassWidget::checkValue(void)
	{
		if (nodeClassType_ == NodeClassType_Unspecified) return false;

		NodeClassType nodeClassType;
		nodeClassType = NodeClass::toNodeClassType(nodeClassWidget_->currentText().toStdString());
		return nodeClassType_ == nodeClassType;
	}

	void
	NodeClassWidget::styleValue(void)
	{
		if (isValid_) {
			nodeClassWidget_->setStyleSheet("background-color:none;");
		}
		else {
			nodeClassWidget_->setStyleSheet("background-color:red;");
		}
	}

	void
	NodeClassWidget::createLayout(void)
	{
		//
		// node class widget
		//
		nodeClassWidget_ = new QComboBox();
		nodeClassWidget_->clear();
		nodeClassWidget_->addItems(nodeClassList_);
		nodeClassWidget_->setFixedWidth(120);

		//
		// actions
		//
		connect(
			nodeClassWidget_, SIGNAL(currentIndexChanged(int)),
			this, SLOT(onCurrentIndexChanged(int))
		);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->addWidget(nodeClassWidget_);
		hBoxLayout->addStretch();
		setLayout(hBoxLayout);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// slots
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	NodeClassWidget::onCurrentIndexChanged(int index)
	{
		if (!checkOn_) return;

		nodeClassType_ = NodeClass::toNodeClassType(nodeClassWidget_->currentText().toStdString());

		isValid_ = checkValue();
		styleValue();
		emit valueChanged(nodeClassType_, isValid_);
	}

}


