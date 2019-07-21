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

#include <QVBoxLayout>
#include <QStackedWidget>

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeSpecialTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeObjectTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeValueTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeValueTypeTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeObjectTypeTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeReferenceTypeTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeDataTypeTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeMethodTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeViewTab.h"

namespace OpcUaNodeSet
{


	OpcUaAttributeSpecialTab::OpcUaAttributeSpecialTab(QWidget* parent)
	: QWidget()
	{
		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		// create stacked widget
		specialAttributeWidget_ = new QStackedWidget();

		// create and add special widgets
		attributeObjectTab_ = new OpcUaAttributeObjectTab();
		specialAttributeWidget_->addWidget(attributeObjectTab_);

		attributeValueTab_ = new OpcUaAttributeValueTab();
		specialAttributeWidget_->addWidget(attributeValueTab_);

		attributeValueTypeTab_ = new OpcUaAttributeValueTypeTab();
		specialAttributeWidget_->addWidget(attributeValueTypeTab_);

		attributeObjectTypeTab_ = new OpcUaAttributeObjectTypeTab();
		specialAttributeWidget_->addWidget(attributeObjectTypeTab_);

		attributeReferenceTypeTab_ = new OpcUaAttributeReferenceTypeTab();
		specialAttributeWidget_->addWidget(attributeReferenceTypeTab_);

		attributeDataTypeTab_ = new OpcUaAttributeDataTypeTab();
		specialAttributeWidget_->addWidget(attributeDataTypeTab_);

		attributeMethodTab_ = new OpcUaAttributeMethodTab();
		specialAttributeWidget_->addWidget(attributeMethodTab_);

		attributeViewTab_ = new OpcUaAttributeViewTab();
		specialAttributeWidget_->addWidget(attributeViewTab_);

		// add widget to  tab window
		vBoxLayout->addWidget(specialAttributeWidget_);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);
	}

	OpcUaAttributeSpecialTab::~OpcUaAttributeSpecialTab(void)
	{
	}

	void
	OpcUaAttributeSpecialTab::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		NodeClass::Enum nodeClass;
		baseNode->getNodeClass(nodeClass);

		switch (nodeClass)
		{
			case NodeClass::EnumObject:
				attributeObjectTab_->nodeChange(nodeInfo);
				specialAttributeWidget_->setCurrentIndex(0);
				break;
			case NodeClass::EnumVariable:
				attributeValueTab_->nodeChange(nodeInfo);
				specialAttributeWidget_->setCurrentIndex(1);
				break;
			case NodeClass::EnumVariableType:
				attributeValueTypeTab_->nodeChange(nodeInfo);
				specialAttributeWidget_->setCurrentIndex(2);
				break;
			case NodeClass::EnumObjectType:
				attributeObjectTypeTab_->nodeChange(nodeInfo);
				specialAttributeWidget_->setCurrentIndex(3);
				break;
			case NodeClass::EnumReferenceType:
				attributeReferenceTypeTab_->nodeChange(nodeInfo);
				specialAttributeWidget_->setCurrentIndex(4);
				break;
			case NodeClass::EnumDataType:
				attributeDataTypeTab_->nodeChange(nodeInfo);
				specialAttributeWidget_->setCurrentIndex(5);
				break;
			case NodeClass::EnumMethod:
				attributeMethodTab_->nodeChange(nodeInfo);
				specialAttributeWidget_->setCurrentIndex(6);
				break;
			case NodeClass::EnumView:
				attributeViewTab_->nodeChange(nodeInfo);
				specialAttributeWidget_->setCurrentIndex(7);
				break;
			default:
				break;
		}
	}

}


