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

#include "OpcUaNodeSetModul/Widget/NodeIdWidget.h"

namespace OpcUaNodeSet
{


	NodeIdWidget::NodeIdWidget(QWidget* parent)
	: QWidget()
	{
		// widgets
		QStringList typeList;
		typeList << "Numeric" << "String" << "Guid" << "Oqaque" << "Unknown";
		typeWidget_ = new QComboBox();
		typeWidget_->addItems(typeList);
		typeWidget_->setFixedWidth(100);

		nodeIdWidget_ = new QLineEdit();
		nodeIdWidget_->setFixedWidth(200);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->addWidget(typeWidget_);
		hBoxLayout->addWidget(nodeIdWidget_);
		hBoxLayout->addStretch();
		setLayout(hBoxLayout);
	}

	NodeIdWidget::~NodeIdWidget(void)
	{
	}

	void
	NodeIdWidget::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullNodeId()) {
			typeWidget_->setCurrentIndex(4);
			nodeIdWidget_->setText(QString(""));
			return;
		}

		OpcUaNodeId nodeId;
		baseNode->getNodeId(nodeId);

		switch (nodeId.nodeIdType())
		{
			case OpcUaBuildInType_OpcUaUInt32:
			{
				OpcUaUInt16 namespaceIndex;
				OpcUaUInt32 value;
				nodeId.get(value, namespaceIndex);
				typeWidget_->setCurrentIndex(0);
				nodeIdWidget_->setText(QString("%1").arg(value));
				break;
			}
			case OpcUaBuildInType_OpcUaString:
			{
				OpcUaUInt16 namespaceIndex;
				std::string value;
				nodeId.get(value, namespaceIndex);
				typeWidget_->setCurrentIndex(1);
				nodeIdWidget_->setText(value.c_str());
				break;
			}
			case OpcUaBuildInType_OpcUaGuid:
			{
				// FIXME: todo
				typeWidget_->setCurrentIndex(2);
				nodeIdWidget_->setText(QString("GUID not supported"));
				break;
			}
			default:
			{
				typeWidget_->setCurrentIndex(4);
				nodeIdWidget_->setText(QString(""));
				break;
			}
		}
	}

}


