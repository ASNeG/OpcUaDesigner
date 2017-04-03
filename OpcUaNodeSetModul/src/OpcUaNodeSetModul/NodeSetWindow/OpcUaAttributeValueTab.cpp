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

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeValueTab.h"

#include <QLabel>
#include <QLineEdit>

namespace OpcUaNodeSet
{


	OpcUaAttributeValueTab::OpcUaAttributeValueTab(QWidget* parent)
	: QWidget()
	{
		QHBoxLayout* hBoxLayout;
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		QGridLayout* gridLayout = new QGridLayout();


		// AccessLevel
		QLabel* accessLevelLabel = new QLabel("AccessLevel");
		gridLayout->addWidget(accessLevelLabel, 0, 0);

		accessLevelLineEdit_ = new QLineEdit();
		accessLevelLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(accessLevelLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 0, 1);


		// ArrayDimensions
		QLabel* arrayDimensionsLabel = new QLabel("ArrayDimensions");
		gridLayout->addWidget(arrayDimensionsLabel, 1, 0);

		arrayDimensionsLineEdit_ = new QLineEdit();
		arrayDimensionsLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(arrayDimensionsLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);


		// DataType
		QLabel* dataTypeLabel = new QLabel("DataType");
		gridLayout->addWidget(dataTypeLabel, 2, 0);

		dataTypeLineEdit_ = new QLineEdit();
		dataTypeLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(dataTypeLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 2, 1);


		// Historizing
		QLabel* historizingLabel = new QLabel("Historizing");
		gridLayout->addWidget(historizingLabel, 3, 0);

		historizingLineEdit_ = new QLineEdit();
		historizingLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(historizingLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 3, 1);


		// MinimumSamplingInterval
		QLabel* minimumSamplingIntervalLabel = new QLabel("MinimumSamplingInterval");
		gridLayout->addWidget(minimumSamplingIntervalLabel, 4, 0);

		minimumSamplingIntervalLineEdit_ = new QLineEdit();
		minimumSamplingIntervalLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(minimumSamplingIntervalLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 4, 1);


		// UserWriteMask
		QLabel* userWriteMaskLabel = new QLabel("UserWriteMask");
		gridLayout->addWidget(userWriteMaskLabel, 5, 0);

		userWriteMaskLineEdit_ = new QLineEdit();
		userWriteMaskLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(userWriteMaskLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 5, 1);


		// Value
		QLabel* valueLabel = new QLabel("Value");
		gridLayout->addWidget(valueLabel, 6, 0);

		valueLineEdit_ = new QLineEdit();
		valueLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(valueLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 6, 1);


		// ValueRank
		QLabel* valueRankLabel = new QLabel("ValueRank");
		gridLayout->addWidget(valueRankLabel, 7, 0);

		valueRankLineEdit_ = new QLineEdit();
		valueRankLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(valueRankLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 7, 1);


		// WriteMask
		QLabel* writeMaskLabel = new QLabel("WriteMask");
		gridLayout->addWidget(writeMaskLabel, 8, 0);

		writeMaskLineEdit_ = new QLineEdit();
		writeMaskLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(writeMaskLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 8, 1);



		vBoxLayout->addLayout(gridLayout);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);
	}

	OpcUaAttributeValueTab::~OpcUaAttributeValueTab(void)
	{
	}

	void
	OpcUaAttributeValueTab::nodeChange(NodeInfo* nodeInfo)
	{
		// FIXME: todo
	}

}


