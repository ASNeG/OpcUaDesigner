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

#include "OpcUaNodeSetModul/Widget/NodeClassWidget.h"

namespace OpcUaNodeSet
{


	NodeClassWidget::NodeClassWidget(QWidget* parent)
	: QWidget()
	{
		// widgets
		QStringList nodeClassList;

		nodeClassList << "Error" <<  "Object" << "Variable" << "Method" << "ObjectType"
			<< "VariableType" << "ReferenceType" << "DataType" << "View";
		nodeClassWidget_ = new QComboBox();
		nodeClassWidget_->addItems(nodeClassList);
		nodeClassWidget_->setFixedWidth(100);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->addWidget(nodeClassWidget_);
		hBoxLayout->addStretch();
		setLayout(hBoxLayout);
	}

	NodeClassWidget::~NodeClassWidget(void)
	{
	}

	void
	NodeClassWidget::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullNodeClass()) {
			nodeClassWidget_->setCurrentText("Error");
			return;
		}

		NodeClassType nodeClass;
		baseNode->getNodeClass(nodeClass);
		nodeClassWidget_->setCurrentText(NodeClass::toString(nodeClass).c_str());
	}

}


