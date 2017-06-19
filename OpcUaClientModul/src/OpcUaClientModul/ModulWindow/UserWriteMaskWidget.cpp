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

#include <OpcUaClientModul/ModulWindow/UserWriteMaskWidget.h>

namespace OpcUaClientModul
{

	UserWriteMaskWidget::UserWriteMaskWidget()
	: QWidget()
	{
		userWriteMaskWidget_ = new QLabel();
		userWriteMaskWidget_->setFixedWidth(200);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->addWidget(userWriteMaskWidget_);
		hBoxLayout->addStretch();

		setLayout(hBoxLayout);
	}

	UserWriteMaskWidget::~UserWriteMaskWidget()
	{
	}

	void
	UserWriteMaskWidget::nodeChange(BaseNode* baseNode)
	{
		std::stringstream ss;
		ss << baseNode->userWriteMask();
		userWriteMaskWidget_->setText(ss.str().c_str());
	}

} /* namespace OpcUaClientModul */
