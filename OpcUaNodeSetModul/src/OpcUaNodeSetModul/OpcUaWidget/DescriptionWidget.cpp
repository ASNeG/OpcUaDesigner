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

#include "OpcUaNodeSetModul/OpcUaWidget/DescriptionWidget.h"

namespace OpcUaNodeSet
{


	DescriptionWidget::DescriptionWidget(QWidget* parent)
	: QWidget()
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

	DescriptionWidget::~DescriptionWidget(void)
	{
	}

	void
	DescriptionWidget::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullDescription()) {
			localeWidget_->setText(QString(""));
			textWidget_->setText(QString(""));
		}

		OpcUaLocalizedText description;
		baseNode->getDescription(description);
		localeWidget_->setText(QString(description.locale().value().c_str()));
		textWidget_->setText(QString(description.text().value().c_str()));
	}

}


