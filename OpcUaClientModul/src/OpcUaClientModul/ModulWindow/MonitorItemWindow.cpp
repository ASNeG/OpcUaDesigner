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
	MonitorItemWindow::createNewMonitorItem(NodeInfo* nodeInfo)
	{
		std::cout << "createNewMonitorItem" << std::endl;

		uint32_t row = monitorTable_->rowCount();
		monitorTable_->insertRow(row);

		setDisplayName(nodeInfo, row);
		setNodeId(nodeInfo, row);
		setValue(nodeInfo, row);
		setSourceTimestamp(nodeInfo, row);
		setServerTimestamp(nodeInfo, row);

		monitorTable_->resizeColumnsToContents();

		OpcUaExpandedNodeId::SPtr expNodeId = nodeInfo->reference_->expandedNodeId();
		OpcUaNodeId nodeId;
		nodeId.nodeIdValue(expNodeId->nodeIdValue());
		nodeId.namespaceIndex(expNodeId->namespaceIndex());

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
	MonitorItemWindow::setDisplayName(NodeInfo* nodeInfo, uint32_t row)
	{
		std::string displayName = nodeInfo->reference_->displayName().text();
		QTableWidgetItem* item = new QTableWidgetItem(displayName.c_str());
		monitorTable_->setItem(row, 0, item);
	}

	void
	MonitorItemWindow::setNodeId(NodeInfo* nodeInfo, uint32_t row)
	{
		std::stringstream ss;
		nodeInfo->reference_->expandedNodeId()->out(ss);
		QTableWidgetItem* item = new QTableWidgetItem(ss.str().c_str());
		monitorTable_->setItem(row, 1, item);
	}

	void
	MonitorItemWindow::setValue(NodeInfo* nodeInfo, uint32_t row)
	{
		QTableWidgetItem* item = new QTableWidgetItem("---");
		if (nodeInfo->dataValue_ != nullptr)
		{
			std::stringstream ss;
			nodeInfo->dataValue_->variant()->out(ss);
			item->setText(ss.str().c_str());
		}
		monitorTable_->setItem(row, 2, item);
	}

	void
	MonitorItemWindow::setSourceTimestamp(NodeInfo* nodeInfo, uint32_t row)
	{
		QTableWidgetItem* item = new QTableWidgetItem("---");
		if (nodeInfo->dataValue_ != nullptr)
		{
			std::stringstream ss;
			ss << nodeInfo->dataValue_->sourceTimestamp().dateTime();
			item->setText(ss.str().c_str());
		}
		monitorTable_->setItem(row, 3, item);
	}

	void
	MonitorItemWindow::setServerTimestamp(NodeInfo* nodeInfo, uint32_t row)
	{
		QTableWidgetItem* item = new QTableWidgetItem("---");
		if (nodeInfo->dataValue_ != nullptr)
		{
			std::stringstream ss;
			ss << nodeInfo->dataValue_->serverTimestamp().dateTime();
			item->setText(ss.str().c_str());
		}
		monitorTable_->setItem(row, 4, item);
	}

} /* namespace OpcUaClientModul */
