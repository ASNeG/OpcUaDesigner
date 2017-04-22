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

#include <OpcUaClientModul/ModulWindow/MonitorItemWindow.h>

namespace OpcUaClientModul
{

	MonitorItemWindow::MonitorItemWindow(OpcUaClientProvider* client)
	: QMainWindow()
	, client_(client)
	{
		setWindowTitle(QString("OpcUaClientModul - MonitorItem Window"));

		statusBar()->addWidget(new QLabel("Connection: opc.tcp://127.0.0.1:8889"));
		statusBar()->addWidget(new QLabel("| Connection Status: Connected"));

		QScrollArea* scrollArea = new QScrollArea();
		this->setCentralWidget(scrollArea);
	}

	MonitorItemWindow::~MonitorItemWindow()
	{
	}

	bool
	MonitorItemWindow::create(void)
	{
		return false;
	}

	bool
	MonitorItemWindow::open(void)
	{
		return false;
	}

	void
	MonitorItemWindow::createNewMonitorItem(NodeInfo* nodeInfo)
	{
		std::cout << "monitor item" << std::endl;
	}

} /* namespace OpcUaClientModul */
