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

		statusBar()->addWidget(new QLabel("Connection: opc.tcp://127.0.0.1:8889")); // FIXME
		statusBar()->addWidget(new QLabel("| Connection Status: Connected"));

		monitorTable_ = new QTableWidget(0, 5);
		monitorTable_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

		this->setCentralWidget(monitorTable_);

		QStringList headerLabels;
		headerLabels << "DisplayName" << "NodeId" << "Value" << "SourceTimestamp" << "ServerTimestamp";
		monitorTable_->setHorizontalHeaderLabels(headerLabels);
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
	MonitorItemWindow::createNewMonitorItem(BaseNode* baseNode)
	{
		std::cout << "createNewMonitorItem" << std::endl;

		uint32_t row = monitorTable_->rowCount();
		monitorTable_->insertRow(row);

		setDisplayName(baseNode, row);
		setNodeId(baseNode, row);
		setValue(baseNode, row);
		setSourceTimestamp(baseNode, row);
		setServerTimestamp(baseNode, row);

		monitorTable_->resizeColumnsToContents();

		OpcUaNodeId nodeId = baseNode->nodeId();

		// TODO save monitoredItemId
		// TODO do not use row for clientHanlde -.- only for testing

		uint32_t monitoredItemId;
		if (client_->syncCreateMonitorItem(nodeId, row, monitoredItemId) != Success)
		{
			std::cout << "ERROR by creating monitored item" << std::endl;
			// TODO error by creating monitored item
		}

		std::cout << "createNewMonitorItem finished" << std::endl;
	}

	void
	MonitorItemWindow::updateMonitoredItem(OpcUaUInt32 clientHandle, OpcUaDataValue& dataValue)
	{
		std::stringstream ss;
		dataValue.variant()->out(ss);
		monitorTable_->item(clientHandle, 2)->setText(ss.str().c_str());

		std::stringstream sourceTimeStampSS;
		sourceTimeStampSS << dataValue.sourceTimestamp().dateTime();
		monitorTable_->item(clientHandle, 3)->setText(sourceTimeStampSS.str().c_str());

		std::stringstream serverTimeStampSS;
		serverTimeStampSS << dataValue.serverTimestamp().dateTime();
		monitorTable_->item(clientHandle, 4)->setText(serverTimeStampSS.str().c_str());
	}

	void
	MonitorItemWindow::setDisplayName(BaseNode* baseNode, uint32_t row)
	{
		std::string displayName = baseNode->displayName().text();
		QTableWidgetItem* item = new QTableWidgetItem(displayName.c_str());
		monitorTable_->setItem(row, 0, item);
	}

	void
	MonitorItemWindow::setNodeId(BaseNode* baseNode, uint32_t row)
	{
		std::stringstream ss;
		baseNode->nodeId().out(ss);
		QTableWidgetItem* item = new QTableWidgetItem(ss.str().c_str());
		monitorTable_->setItem(row, 1, item);
	}

	void
	MonitorItemWindow::setValue(BaseNode* baseNode, uint32_t row)
	{
		QTableWidgetItem* item = new QTableWidgetItem("---");
		if (baseNode->dataValue() != nullptr)
		{
			std::stringstream ss;
			baseNode->dataValue()->variant()->out(ss);
			item->setText(ss.str().c_str());
		}
		monitorTable_->setItem(row, 2, item);
	}

	void
	MonitorItemWindow::setSourceTimestamp(BaseNode* baseNode, uint32_t row)
	{
		QTableWidgetItem* item = new QTableWidgetItem("---");
		if (baseNode->dataValue() != nullptr)
		{
			std::stringstream ss;
			ss << baseNode->dataValue()->sourceTimestamp().dateTime();
			item->setText(ss.str().c_str());
		}
		monitorTable_->setItem(row, 3, item);
	}

	void
	MonitorItemWindow::setServerTimestamp(BaseNode* baseNode, uint32_t row)
	{
		QTableWidgetItem* item = new QTableWidgetItem("---");
		if (baseNode->dataValue() != nullptr)
		{
			std::stringstream ss;
			ss << baseNode->dataValue()->serverTimestamp().dateTime();
			item->setText(ss.str().c_str());
		}
		monitorTable_->setItem(row, 4, item);
	}

} /* namespace OpcUaClientModul */
