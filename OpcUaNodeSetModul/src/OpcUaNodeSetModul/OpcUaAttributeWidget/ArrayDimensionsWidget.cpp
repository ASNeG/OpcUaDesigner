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
#include <QLabel>
#include <QPushButton>

#include "OpcUaNodeSetModul/OpcUaAttributeWidget/ArrayDimensionsWidget.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	ArrayDimensionsWidget::ArrayDimensionsWidget(QWidget* parent)
	: QWidget()
	, checkOn_(true)
	, isValid_(true)
	{
		// widgets
		buttonWidget_ = new QPushButton();
		buttonWidget_->setIcon(QIcon(":/images/Tree.png"));
		buttonWidget_->setFixedWidth(30);

		labelWidget_ = new QLabel();
		labelWidget_->setFixedWidth(365);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(buttonWidget_);
		hBoxLayout->addWidget(labelWidget_);
		hBoxLayout->setMargin(0);

		//
		// actions
		//
		connect(
			buttonWidget_, SIGNAL(clicked()),
			this, SLOT(onClicked())
		);

		setLayout(hBoxLayout);
	}

	ArrayDimensionsWidget::~ArrayDimensionsWidget(void)
	{
	}

	bool
	ArrayDimensionsWidget::isValid(void)
	{
		return isValid_;
	}

	void
	ArrayDimensionsWidget::nodeChange(NodeInfo* nodeInfo)
	{
		arrayDimensions_.reset();

		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullArrayDimensions()) {
			labelWidget_->setText(QString("---"));
			return;
		}

		checkOn_ = false;
		OpcUaUInt32Array arrayDimensions;
		baseNode->getArrayDimensions(arrayDimensions);

		arrayDimensions_ = constructSPtr<OpcUaUInt32Array>();
		arrayDimensions.copyTo(*arrayDimensions_);

		if (arrayDimensions.isNull()) {
			labelWidget_->setText(QString("---"));
			return;
		}

		std::stringstream ss;
		arrayDimensions.out(ss);
		labelWidget_->setText(QString(ss.str().c_str()));
		isValid_ = checkValue();
		styleValue();
		checkOn_ = true;
	}

	void
	ArrayDimensionsWidget::nodeChange(OpcUaUInt32Array::SPtr& arrayDimensions)
	{
		arrayDimensions_.reset();

		if (arrayDimensions.get() == nullptr) {
			labelWidget_->setText(QString("---"));

			emit valueChanged(arrayDimensions_, isValid_);
		    emit update();

			return;
		}

		arrayDimensions_ = constructSPtr<OpcUaUInt32Array>();
		arrayDimensions->copyTo(*arrayDimensions_);

		if (arrayDimensions_->isNull()) {
			labelWidget_->setText(QString("---"));

			emit valueChanged(arrayDimensions_, isValid_);
		    emit update();

			return;
		}

		std::stringstream ss;
		arrayDimensions->out(ss);
		labelWidget_->setText(QString(ss.str().c_str()));
		isValid_ = checkValue();
		styleValue();
		checkOn_ = true;

		emit valueChanged(arrayDimensions_, isValid_);
	    emit update();
	}

	void
	ArrayDimensionsWidget::enabled(bool enabled)
	{
		buttonWidget_->setEnabled(enabled);
	}

	void
	ArrayDimensionsWidget::getValue(OpcUaUInt32Array::SPtr& arrayDimensions)
	{
		arrayDimensions.reset();

		if (arrayDimensions_.get() == nullptr) {
			return;
		}

		arrayDimensions = constructSPtr<OpcUaUInt32Array>();
		arrayDimensions_->copyTo(*arrayDimensions);
	}

	bool
	ArrayDimensionsWidget::checkValue(void)
	{
		// FIXME: todo
		return true;
	}

	void
	ArrayDimensionsWidget::styleValue(void)
	{
		if (isValid_) {
			labelWidget_->setStyleSheet("background-color:none;");
		}
		else {
			labelWidget_->setStyleSheet("background-color:red;");
		}
	}

	void
	ArrayDimensionsWidget::onClicked(void)
	{
		emit selectDimensionArray(arrayDimensions_);
	}

#if 0
	void
	ArrayDimensionsWidget::onTextChangedTextWidget(const QString& text)
	{
		if (!checkOn_) return;

		OpcUaUInt32Array arrayDimensions;
		isValid_ = checkValue();
		styleValue();
		// FIXME: todo
		emit valueChanged(arrayDimensions, isValid_);
	    emit update();
	}
#endif

}


