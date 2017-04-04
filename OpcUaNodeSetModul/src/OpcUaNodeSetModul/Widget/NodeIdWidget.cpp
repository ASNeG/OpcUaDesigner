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

#include "OpcUaNodeSetModul/Widget/NodeIdWidget.h"

namespace OpcUaNodeSet
{


	NodeIdWidget::NodeIdWidget(QWidget* parent)
	: QWidget()
	{
		nodeIdLineEdit_ = new QLineEdit();
		nodeIdLineEdit_->setFixedWidth(300);

		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(nodeIdLineEdit_);
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
			nodeIdLineEdit_->setText(QString(""));
		}
		else {
			OpcUaNodeId nodeId;
			baseNode->getNodeId(nodeId);
			nodeIdLineEdit_->setText(QString(nodeId.toString().c_str()));
		}
	}

}


