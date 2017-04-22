/*
 Copyright 2016-2017 Samuel Huebl (samuel@huebl-sgh.de)

 Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
 Datei nur in Übereinstimmung mit der Lizenz erlaubt.
 Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

 Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
 erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
 GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

 Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
 im Rahmen der Lizenz finden Sie in der Lizenz.

 Autor: Samuel Huebl (samuel@huebl-sgh.de)
 */

#include <OpcUaClientModul/ModulWindow/BrowseNameWidget.h>

namespace OpcUaClientModul
{

	BrowseNameWidget::BrowseNameWidget()
	: QWidget()
	{
		QLabel* qualifiedNameLabel = new QLabel("QualifiedName:");
		qualifiedNameLabel->setFixedWidth(140);

		QLabel* namespaceLabel = new QLabel("NamespaceIndex:");
		namespaceLabel->setFixedWidth(140);

		browseNameWidget_ = new QLabel();
		namespaceWidget_ = new QLabel();

		// layout
		QHBoxLayout* hBoxLayoutQN = new QHBoxLayout();
		hBoxLayoutQN->setMargin(0);
		hBoxLayoutQN->setSpacing(5);
		hBoxLayoutQN->addWidget(qualifiedNameLabel);
		hBoxLayoutQN->addWidget(browseNameWidget_);

		QHBoxLayout* hBoxLayoutNI = new QHBoxLayout();
		hBoxLayoutNI->setMargin(0);
		hBoxLayoutNI->setSpacing(5);
		hBoxLayoutNI->addWidget(namespaceLabel);
		hBoxLayoutNI->addWidget(namespaceWidget_);

		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->setMargin(0);
		vBoxLayout->addLayout(hBoxLayoutQN);
		vBoxLayout->addLayout(hBoxLayoutNI);

		setLayout(vBoxLayout);
	}

	BrowseNameWidget::~BrowseNameWidget()
	{
	}

	void
	BrowseNameWidget::nodeChange(NodeInfo* nodeInfo)
	{
		ReferenceDescription::SPtr refDescription = nodeInfo->reference_;

		OpcUaQualifiedName browseName = refDescription->browseName();

		// set browse name
		std::stringstream ss1;
		ss1 << browseName.name();
		browseNameWidget_->setText(ss1.str().c_str());

		// set namespace
		std::stringstream ss2;
		ss2 << browseName.namespaceIndex();
		namespaceWidget_->setText(ss2.str().c_str());
	}

} /* namespace OpcUaClientModul */
