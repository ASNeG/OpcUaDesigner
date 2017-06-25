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

#include "OpcUaClientModul/ModulMainWidgets/ConnectionInfoWidget.h"

namespace OpcUaClientModul
{
	ConnectionInfoWidget::ConnectionInfoWidget()
	: QWidget()
	{
		std::cout << "create ConnectionInfoWidget" << std::endl;

		QLabel* connectionInfoLabel = new QLabel("Connection:");
		connectionInfoLabel->setFixedWidth(140);

		QLabel* connectionStatusLabel = new QLabel("ConnectionStatus:");
		connectionStatusLabel->setFixedWidth(140);

		connectionInfo_ = new QLabel("TODO - IP:PORT");
		connectionStatus_ = new QLabel("TODO - ConnectionState");

		// layout
		QHBoxLayout* hBoxLayoutCI = new QHBoxLayout();
		hBoxLayoutCI->setMargin(0);
		hBoxLayoutCI->setSpacing(5);
		hBoxLayoutCI->addWidget(connectionInfoLabel);
		hBoxLayoutCI->addWidget(connectionInfo_);

		QHBoxLayout* hBoxLayoutCS = new QHBoxLayout();
		hBoxLayoutCS->setMargin(0);
		hBoxLayoutCS->setSpacing(5);
		hBoxLayoutCS->addWidget(connectionStatusLabel);
		hBoxLayoutCS->addWidget(connectionStatus_);

		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->setMargin(10);
		vBoxLayout->addLayout(hBoxLayoutCI);
		vBoxLayout->addLayout(hBoxLayoutCS);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);

		std::cout << "create ConnectionInfoWidget finished" << std::endl;
	}

	ConnectionInfoWidget::~ConnectionInfoWidget()
	{
	}

	void
	ConnectionInfoWidget::nodeChange(BaseNode* baseNode)
	{
		/// TODO
	}
}
