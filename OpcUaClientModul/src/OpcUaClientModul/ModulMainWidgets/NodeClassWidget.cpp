/*
 Copyright 2016-2010 Samuel Huebl (samuel@huebl-sgh.de)

 Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
 Datei nur in Übereinstimmung mit der Lizenz erlaubt.
 Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

 Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
 erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
 GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

 Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
 im Rahmen der Lizenz finden Sie in der Lizenz.

 Autor: Samuel Huebl (samuel@huebl-sgh.de),
        Kai Huebl (kai@huebl-sgh.de)
 */

#include "OpcUaClientModul/ModulMainWidgets/NodeClassWidget.h"

namespace OpcUaClientModul
{

	NodeClassWidget::NodeClassWidget()
	: QWidget()
	{
		nodeClassWidget_ = new QLabel();
		nodeClassWidget_->setFixedWidth(200);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->addWidget(nodeClassWidget_);
		hBoxLayout->addStretch();

		setLayout(hBoxLayout);
	}

	NodeClassWidget::~NodeClassWidget()
	{
	}

	void
	NodeClassWidget::nodeChange(BaseNode* baseNode)
	{
		NodeClass::Enum nodeClass = baseNode->nodeClass();
		nodeClassWidget_->setText(NodeClass::enum2Str(nodeClass).c_str());
	}

} /* namespace OpcUaClientModul */
