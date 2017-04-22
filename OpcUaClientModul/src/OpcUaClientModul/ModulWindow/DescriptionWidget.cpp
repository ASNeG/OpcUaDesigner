/*
 Copyright 2016-2017 Samuel Huebl (samuel@huebl-sgh.de)

 Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
 Datei nur in Übereinstimmung mit der Lizenz erlaubt.
 Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

 Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
 erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
 GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

 Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
 im Rahmen der Lizenz finden Sie in der Lizenz.

 Autor: Samuel Huebl (samuel@huebl-sgh.de)
 */

#include <OpcUaClientModul/ModulWindow/DescriptionWidget.h>

namespace OpcUaClientModul
{

	DescriptionWidget::DescriptionWidget()
	: QWidget()
	{
		descriptionWidget_ = new QLabel();
		descriptionWidget_->setFixedWidth(250);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->addWidget(descriptionWidget_);
		hBoxLayout->addStretch();

		setLayout(hBoxLayout);
	}

	DescriptionWidget::~DescriptionWidget()
	{
	}

	void
	DescriptionWidget::nodeChange(NodeInfo* nodeInfo)
	{
		if (nodeInfo->description_ != nullptr)
		{
			descriptionWidget_->setText(nodeInfo->description_->text().value().c_str());
		}
	}

} /* namespace OpcUaClientModul */
