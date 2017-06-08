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
#include <QComboBox>
#include <QStringList>
#include <QString>

#include "OpcUaNodeSetModul/OpcUaWidget/ObjectTypeWidget.h"

namespace OpcUaNodeSet
{

	ObjectTypeWidget::ObjectTypeWidget(QWidget* parent)
	: QWidget(parent)
	{
		// widgets
		QStringList typeList;
		typeList << "Numeric" << "String" << "Guid" << "Oqaque" << "Unknown";
		typeWidget_ = new QComboBox();
		typeWidget_->addItems(typeList);
		typeWidget_->setFixedWidth(120);

		nodeIdWidget_ = new QLineEdit();
		nodeIdWidget_->setFixedWidth(280-5);

		namespaceWidget_ = new QComboBox();
		namespaceWidget_->setFixedWidth(400);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->setSpacing(5);
		hBoxLayout->addWidget(typeWidget_);
		hBoxLayout->addWidget(nodeIdWidget_);
		hBoxLayout->addStretch();
		hBoxLayout->setMargin(0);

		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->addLayout(hBoxLayout);
		vBoxLayout->addWidget(namespaceWidget_);
		vBoxLayout->setMargin(0);

		setLayout(vBoxLayout);
	}

	ObjectTypeWidget::~ObjectTypeWidget(void)
	{
	}

	void
	ObjectTypeWidget::nodeChange(NodeInfo* nodeInfo)
	{
		// get base node
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullObjectType()) {
			typeWidget_->setCurrentIndex(4);
			nodeIdWidget_->setText(QString(""));
			return;
		}

		// set node id
		OpcUaObjectType nodeId;
		baseNode->getObjectType(nodeId);

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
				nodeIdWidget_->setText(QString("Type not supported"));
				break;
			}
		}

		// set namespace
		namespaceWidget_->clear();
		for (uint32_t idx = 0; idx < nodeInfo->nodeSetNamespace_.globalNamespaceVec().size(); idx++) {
			namespaceWidget_->addItem(nodeInfo->nodeSetNamespace_.globalNamespaceVec()[idx].c_str());
		}
		namespaceWidget_->setCurrentIndex(nodeId.namespaceIndex());

	}

}


