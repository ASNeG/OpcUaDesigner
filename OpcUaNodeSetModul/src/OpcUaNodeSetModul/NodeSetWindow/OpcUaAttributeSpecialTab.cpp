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
		NodeClassType nodeClass;
		baseNode->getNodeClass(nodeClass);

		switch (nodeClass)
		{
			case NodeClassType_Object:
				attributeObjectTab_->nodeChange(nodeInfo);
				specialAttributeWidget_->setCurrentIndex(0);
				break;
			case NodeClassType_Variable:
				attributeValueTab_->nodeChange(nodeInfo);
				specialAttributeWidget_->setCurrentIndex(1);
				break;
			case NodeClassType_VariableType:
				attributeValueTab_->nodeChange(nodeInfo);
				specialAttributeWidget_->setCurrentIndex(2);
				break;
			case NodeClassType_ObjectType:
				attributeObjectTypeTab_->nodeChange(nodeInfo);
				specialAttributeWidget_->setCurrentIndex(3);
				break;
			case NodeClassType_ReferenceType:
				attributeReferenceTypeTab_->nodeChange(nodeInfo);
				specialAttributeWidget_->setCurrentIndex(4);
				break;
			case NodeClassType_DataType:
				break;
			case NodeClassType_Method:
				break;
			case NodeClassType_View:
				break;
			default:
				break;
		}
	}

}


