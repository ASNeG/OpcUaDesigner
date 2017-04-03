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
#include <QLabel>
#include <QLineEdit>

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeMethodTab.h"

namespace OpcUaNodeSet
{


	OpcUaAttributeMethodTab::OpcUaAttributeMethodTab(QWidget* parent)
	: QWidget()
	{
		QHBoxLayout* hBoxLayout;
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		QGridLayout* gridLayout = new QGridLayout();


		// Executable
		QLabel* executableLabel = new QLabel("Executable");
		gridLayout->addWidget(executableLabel, 0, 0);

		executableLineEdit_ = new QLineEdit();
		executableLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(executableLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 0, 1);


		// UserExecutable
		QLabel* userExecutableLabel = new QLabel("UserExecutable");
		gridLayout->addWidget(userExecutableLabel, 1, 0);

		userExecutableLineEdit_ = new QLineEdit();
		userExecutableLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(userExecutableLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);


		// UserWriteMask
		QLabel* userWriteMaskLabel = new QLabel("UserWriteMask");
		gridLayout->addWidget(userWriteMaskLabel, 2, 0);

		userWriteMaskLineEdit_ = new QLineEdit();
		userWriteMaskLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(userWriteMaskLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 2, 1);


		// WriteMask
		QLabel* writeMaskLabel = new QLabel("WriteMask");
		gridLayout->addWidget(writeMaskLabel, 3, 0);

		writeMaskLineEdit_ = new QLineEdit();
		writeMaskLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(writeMaskLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 3, 1);


		vBoxLayout->addLayout(gridLayout);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);
	}

	OpcUaAttributeMethodTab::~OpcUaAttributeMethodTab(void)
	{
	}

	void
	OpcUaAttributeMethodTab::nodeChange(NodeInfo* nodeInfo)
	{
		// FIXME: todo
	}

}


