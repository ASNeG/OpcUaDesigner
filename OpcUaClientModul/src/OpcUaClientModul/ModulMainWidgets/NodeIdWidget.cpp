/*
 Copyright 2016-2019 Samuel Huebl (samuel@huebl-sgh.de)

 Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
 Datei nur in Übereinstimmung mit der Lizenz erlaubt.
 Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

 Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
 erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
 GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

 Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
 im Rahmen der Lizenz finden Sie in der Lizenz.

 Autor: Samuel Huebl (samuel@huebl-sgh.de)
        Kai Huebl (kai@huebl-sgh.de)
 */

#include "OpcUaClientModul/ModulMainWidgets/NodeIdWidget.h"

using namespace OpcUaStackCore;

namespace OpcUaClientModul
{

	NodeIdWidget::NodeIdWidget()
	: QWidget()
	{
		typeList_ << "Numeric" << "String" << "Guid" << "Oqaque" << "Unknown";

		typeWidget_ = new QLabel();
		typeWidget_->setFixedWidth(140);

		nodeIdWidget_ = new QLabel();
		nodeIdWidget_->setFixedWidth(280-5);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->setSpacing(5);
		hBoxLayout->addWidget(typeWidget_);
		hBoxLayout->addWidget(nodeIdWidget_);

		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->setMargin(0);
		vBoxLayout->addLayout(hBoxLayout);

		setLayout(vBoxLayout);
	}

	NodeIdWidget::~NodeIdWidget()
	{
	}

	void NodeIdWidget::nodeChange(BaseNode* baseNode)
	{
		OpcUaNodeId nodeId = baseNode->nodeId();

		switch (nodeId.nodeIdType())
		{
			case OpcUaBuildInType_OpcUaUInt32:
			{
				OpcUaUInt16 namespaceIndex;
				OpcUaUInt32 value;
				nodeId.get(value, namespaceIndex);
				typeWidget_->setText(typeList_[0]);
				nodeIdWidget_->setText(QString("%1").arg(value));
				break;
			}
			case OpcUaBuildInType_OpcUaString:
			{
				OpcUaUInt16 namespaceIndex;
				std::string value;
				nodeId.get(value, namespaceIndex);
				typeWidget_->setText(typeList_[1]);
				nodeIdWidget_->setText(value.c_str());
				break;
			}
			case OpcUaBuildInType_OpcUaGuid:
			{
				// FIXME: todo
				typeWidget_->setText(typeList_[2]);
				nodeIdWidget_->setText(QString("GUID not supported"));
				break;
			}
			default:
			{
				typeWidget_->setText(typeList_[4]);
				nodeIdWidget_->setText(QString("Type not supported"));
				break;
			}
		}
	}

} /* namespace OpcUaClientModul */
