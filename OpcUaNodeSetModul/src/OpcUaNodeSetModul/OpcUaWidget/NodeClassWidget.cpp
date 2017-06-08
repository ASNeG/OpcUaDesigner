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

#include "OpcUaNodeSetModul/OpcUaWidget/NodeClassWidget.h"

namespace OpcUaNodeSet
{


	NodeClassWidget::NodeClassWidget(QWidget* parent)
	: QWidget(parent)
	, nodeClassList_()
	{
		nodeClassList_ << "Error" <<  "Object" << "Variable" << "Method" << "ObjectType"
			<< "VariableType" << "ReferenceType" << "DataType" << "View";
		createLayout();

	}

	NodeClassWidget::NodeClassWidget(QStringList& nodeClassList, QWidget* parent)
	: QWidget(parent)
	, nodeClassList_(nodeClassList)
	{
		createLayout();
	}

	NodeClassWidget::~NodeClassWidget(void)
	{
	}

	void
	NodeClassWidget::createLayout(void)
	{
		nodeClassWidget_ = new QComboBox();
		nodeClassWidget_->addItems(nodeClassList_);
		nodeClassWidget_->setFixedWidth(120);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->addWidget(nodeClassWidget_);
		hBoxLayout->addStretch();
		setLayout(hBoxLayout);
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


