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

#include "OpcUaNodeSetModul/OpcUaWidget/DisplayNameWidget.h"

namespace OpcUaNodeSet
{


	DisplayNameWidget::DisplayNameWidget(QWidget* parent)
	: QWidget()
	, displayName_()
	, isValid_(false)
	, checkOn_(true)
	{
		// widgets
		localeWidget_ = new QLineEdit();
		localeWidget_->setFixedWidth(50);

		textWidget_ = new QLineEdit();
		textWidget_->setFixedWidth(350-5);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(localeWidget_);
		hBoxLayout->addWidget(textWidget_);
		hBoxLayout->setMargin(0);

		setLayout(hBoxLayout);
	}

	DisplayNameWidget::~DisplayNameWidget(void)
	{
	}

	void
	DisplayNameWidget::setValue(OpcUaLocalizedText& displayName)
	{
		displayName_ = displayName;
	}

	void
	DisplayNameWidget::getValue(OpcUaLocalizedText& displayName)
	{
		displayName = displayName_;
	}

	bool
	DisplayNameWidget::isValid(void)
	{
		return isValid_;
	}

	void
	DisplayNameWidget::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullDisplayName()) {
			localeWidget_->setText(QString(""));
			textWidget_->setText(QString(""));
		}

		OpcUaLocalizedText displayName;
		baseNode->getDisplayName(displayName);
		localeWidget_->setText(QString(displayName.locale().value().c_str()));
		textWidget_->setText(QString(displayName.text().value().c_str()));
	}

}


