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

#include "OpcUaNodeSetModul/OpcUaAttributeWidget/AccessLevelWidget.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	AccessLevelWidget::AccessLevelWidget(QWidget* parent)
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

	AccessLevelWidget::~AccessLevelWidget(void)
	{
	}

	bool
	AccessLevelWidget::isValid(void)
	{
		return isValid_;
	}

	void
	AccessLevelWidget::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullAccessLevel()) {
			textWidget_->setText(QString("0"));
		}

		checkOn_ = false;
		OpcUaByte accessLevel;
		baseNode->getAccessLevel(accessLevel);
		textWidget_->setText(QString("%1").arg((uint32_t)accessLevel));
		isValid_ = checkValue();
		styleValue();
		checkOn_ = true;
	}

	void
	AccessLevelWidget::enabled(bool enabled)
	{
		textWidget_->setEnabled(enabled);
	}

	void
	AccessLevelWidget::getValue(OpcUaByte& accessLevel)
	{
		bool rc;
		accessLevel = textWidget_->text().toInt(&rc);
	}

	bool
	AccessLevelWidget::checkValue(void)
	{
		textWidget_->text().toInt(&isValid_);
		return isValid_;
	}

	void
	AccessLevelWidget::styleValue(void)
	{
		if (isValid_) {
			textWidget_->setStyleSheet("background-color:none;");
		}
		else {
			textWidget_->setStyleSheet("background-color:red;");
		}
	}

	void
	AccessLevelWidget::onTextChangedTextWidget(const QString& text)
	{
		if (!checkOn_) return;

		OpcUaByte accessLevel;
		isValid_ = checkValue();
		styleValue();
		bool rc;
		accessLevel = textWidget_->text().toInt(&rc);
		emit valueChanged(accessLevel, isValid_);
	    emit update();
	}

}


