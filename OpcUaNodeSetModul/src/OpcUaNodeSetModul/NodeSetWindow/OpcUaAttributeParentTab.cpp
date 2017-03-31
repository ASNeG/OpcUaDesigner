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

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeParentTab.h"

#include <QLabel>
#include <QLineEdit>

namespace OpcUaNodeSet
{


	OpcUaAttributeParentTab::OpcUaAttributeParentTab(QWidget* parent)
	: QWidget()
	{
		QHBoxLayout* hBoxLayout;
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		QGridLayout* gridLayout = new QGridLayout();


		// DisplayName
		QLabel* displayNameLabel = new QLabel("DisplayName");
		gridLayout->addWidget(displayNameLabel, 1, 0);

		displayNameLineEdit_ = new QLineEdit();
		displayNameLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(displayNameLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);


		// NodeId
		QLabel* nodeIdLabel = new QLabel("NodeId");
		gridLayout->addWidget(nodeIdLabel, 2, 0);

		nodeIdLineEdit_ = new QLineEdit();
		nodeIdLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(nodeIdLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 2, 1);

		// BrowseName
		QLabel* browseNameLabel = new QLabel("BrowseName");
		gridLayout->addWidget(browseNameLabel, 3, 0);

		browseNameLineEdit_ = new QLineEdit();
		browseNameLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(browseNameLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 3, 1);


		// Reference
		QLabel* referenceLabel = new QLabel("Reference");
		gridLayout->addWidget(referenceLabel, 4, 0);

		referenceLineEdit_ = new QLineEdit();
		referenceLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(referenceLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 4, 1);


		vBoxLayout->addLayout(gridLayout);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);
	}

	OpcUaAttributeParentTab::~OpcUaAttributeParentTab(void)
	{
	}

	void
	OpcUaAttributeParentTab::nodeChange(NodeInfo* nodeInfo)
	{
		// FIXME: todo


	}

}


