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
#include <QHBoxLayout>
#include <QGridLayout>

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeBaseTab.h"

#include <QLabel>
#include <QLineEdit>

namespace OpcUaNodeSet
{


	OpcUaAttributeBaseTab::OpcUaAttributeBaseTab(QWidget* parent)
	: QWidget()
	{
		QHBoxLayout* hBoxLayout;
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		QGridLayout* gridLayout = new QGridLayout();


		// NodeId
		QLabel* nodeIdLabel = new QLabel("NodeId");
		gridLayout->addWidget(nodeIdLabel, 0, 0);

		QLineEdit* nodeIdLineEdit = new QLineEdit();
		nodeIdLineEdit->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(nodeIdLineEdit);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 0, 1);


		// NodeClass
		QLabel* nodeClassLabel = new QLabel("NodeClass");
		gridLayout->addWidget(nodeClassLabel, 1, 0);

		QLineEdit* nodeClassLineEdit = new QLineEdit();
		nodeClassLineEdit->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(nodeClassLineEdit);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);


		// BrowseName
		QLabel* browseNameLabel = new QLabel("BrowseName");
		gridLayout->addWidget(browseNameLabel, 2, 0);

		QLineEdit* browseNameLineEdit = new QLineEdit();
		browseNameLineEdit->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(browseNameLineEdit);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 2, 1);


		// DisplayName
		QLabel* displayNameLabel = new QLabel("DisplayName");
		gridLayout->addWidget(displayNameLabel, 3, 0);

		QLineEdit* displayNameLineEdit = new QLineEdit();
		displayNameLineEdit->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(displayNameLineEdit);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 3, 1);


		// Description
		QLabel* descriptionLabel = new QLabel("Description");
		gridLayout->addWidget(descriptionLabel, 4, 0);

		QLineEdit* descriptionLineEdit = new QLineEdit();
		descriptionLineEdit->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(descriptionLineEdit);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 4, 1);


		// WriteMask
		QLabel* writeMaskLabel = new QLabel("WriteMask");
		gridLayout->addWidget(writeMaskLabel, 5, 0);

		QLineEdit* writeMaskLineEdit = new QLineEdit();
		writeMaskLineEdit->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(writeMaskLineEdit);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 5, 1);


		// UserWriteMask
		QLabel* userWriteMaskLabel = new QLabel("UserWriteMask");
		gridLayout->addWidget(userWriteMaskLabel, 6, 0);

		QLineEdit* userWriteMaskLineEdit = new QLineEdit();
		userWriteMaskLineEdit->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(userWriteMaskLineEdit);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 6, 1);


		vBoxLayout->addLayout(gridLayout);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);
	}

	OpcUaAttributeBaseTab::~OpcUaAttributeBaseTab(void)
	{
	}

}


