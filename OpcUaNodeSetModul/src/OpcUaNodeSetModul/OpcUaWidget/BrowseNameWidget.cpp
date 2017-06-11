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

#include "OpcUaNodeSetModul/OpcUaWidget/BrowseNameWidget.h"

namespace OpcUaNodeSet
{


	BrowseNameWidget::BrowseNameWidget(QWidget* parent)
	: QWidget()
	, nodeSetNamespace_(NULL)
	, browseName_()
	, isValid_(false)
	{
		// widgets
		browseNameWidget_ = new QLineEdit();
		browseNameWidget_->setFixedWidth(400);

		namespaceWidget_ = new QComboBox();
		namespaceWidget_->setFixedWidth(400);

		// layout
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->addWidget(browseNameWidget_);
		vBoxLayout->addWidget(namespaceWidget_);
		vBoxLayout->addStretch();
		vBoxLayout->setMargin(0);
		setLayout(vBoxLayout);
	}

	BrowseNameWidget::~BrowseNameWidget(void)
	{
	}

	void
	BrowseNameWidget::setValue(NodeSetNamespace& nodeSetNamespace)
	{
		nodeSetNamespace_ = &nodeSetNamespace;
	}

	void
	BrowseNameWidget::setValue(OpcUaQualifiedName& browseName)
	{
		browseName_ = browseName;
	}

	void
	BrowseNameWidget::getValue(OpcUaQualifiedName& browseName)
	{
		browseName = browseName_;
	}

	bool
	BrowseNameWidget::isValid(void)
	{
		return isValid_;
	}

	void
	BrowseNameWidget::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullBrowseName()) {
			browseNameWidget_->setText(QString(".."));
			namespaceWidget_->clear();
			return;
		}

		// set browse name
		OpcUaQualifiedName browseName;
		baseNode->getBrowseName(browseName);
		browseNameWidget_->setText(QString(browseName.toString().c_str()));

		// set namespace
		namespaceWidget_->clear();
		for (uint32_t idx = 0; idx < nodeInfo->nodeSetNamespace_.globalNamespaceVec().size(); idx++) {
			namespaceWidget_->addItem(nodeInfo->nodeSetNamespace_.globalNamespaceVec()[idx].c_str());
		}
		namespaceWidget_->setCurrentIndex(browseName.namespaceIndex());
	}

}


