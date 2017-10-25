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
#include <QLineEdit>
#include <QComboBox>
#include <QStringList>
#include <QString>

#include "OpcUaNodeSetModul/OpcUaAttributeWidget/QualifiedNameWidget.h"

namespace OpcUaNodeSet
{


	QualifiedNameWidget::QualifiedNameWidget(QWidget* parent)
	: QWidget()
	{
		// widgets
		textWidget_ = new QLineEdit();
		textWidget_->setFixedWidth(400);

		namespaceWidget_ = new QComboBox();
		namespaceWidget_->setFixedWidth(400);

		// layout
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->addWidget(textWidget_);
		vBoxLayout->addWidget(namespaceWidget_);
		vBoxLayout->addStretch();
		vBoxLayout->setMargin(0);
		setLayout(vBoxLayout);
	}

	QualifiedNameWidget::~QualifiedNameWidget(void)
	{
	}

	void
	QualifiedNameWidget::nodeChange(void)
	{
		textWidget_->setText(QString(""));
		namespaceWidget_->clear();
	}

	void
	QualifiedNameWidget::nodeChange(NodeInfo* nodeInfo, OpcUaQualifiedName& qualifiedName)
	{
		nodeChange();

		// set browse name
		textWidget_->setText(QString(qualifiedName.name().value().c_str()));

		// set namespace
		namespaceWidget_->clear();
		for (uint32_t idx = 0; idx < nodeInfo->nodeSetNamespace_.globalNamespaceVec().size(); idx++) {
			namespaceWidget_->addItem(nodeInfo->nodeSetNamespace_.globalNamespaceVec()[idx].c_str());
		}
		namespaceWidget_->setCurrentIndex(qualifiedName.namespaceIndex());
	}

}


