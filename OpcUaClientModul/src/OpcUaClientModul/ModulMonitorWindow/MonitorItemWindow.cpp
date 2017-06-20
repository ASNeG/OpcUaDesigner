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

#include "OpcUaClientModul/ModulMonitorWindow/MonitorItemWindow.h"

namespace OpcUaClientModul
{

	MonitorItemWindow::MonitorItemWindow(OpcUaClientProvider* client)
	: QMainWindow()
	, client_(client)
	, rowItems_()
	{
		setWindowTitle(QString("OpcUaClientModul - MonitorItem Window"));

		statusBar()->addWidget(new QLabel("Connection: opc.tcp://127.0.0.1:8889")); // FIXME
		statusBar()->addWidget(new QLabel("| Connection Status: Connected"));

		monitorTable_ = new QTableWidget(0, 5);
		monitorTable_->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
		monitorTable_->setEditTriggers(QAbstractItemView::NoEditTriggers);
		monitorTable_->setSelectionBehavior(QAbstractItemView::SelectRows);
		monitorTable_->setContextMenuPolicy(Qt::CustomContextMenu);

		connect (
				monitorTable_, SIGNAL(customContextMenuRequested(const QPoint&)),
				this, SLOT(slotPrepareMenu(const QPoint&))
		);

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

	// ##################################################################
	//
	//  Create a new monitored item
	//
	// ##################################################################

	void
	MonitorItemWindow::slotCreateNewMonitorItem(BaseNode* baseNode)
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
		ItemRow* itemRow = addRowItem(baseNode, row);

		uint32_t monitoredItemId;
		if (client_->syncCreateMonitorItem(nodeId, itemRow->clientHandle(), monitoredItemId) != Success)
		{
			std::cout << "ERROR by creating monitored item" << std::endl;
			// TODO error by creating monitored item
		}
		itemRow->monitoredItemId(monitoredItemId);

		std::cout << "createNewMonitorItem finished" << std::endl;
	}

	// ##################################################################
	//
	//  Update a variable in the table
	//
	// ##################################################################

	void
	MonitorItemWindow::updateMonitoredItem(OpcUaUInt32 clientHandle, OpcUaDataValue& dataValue)
	{
		std::cout << "receive updateMonitoredItem" << std::endl;

		ItemRow* itemRow = getRowItem(clientHandle);
		if (itemRow == nullptr)
		{
			std::cout << "cannot find item for " << clientHandle << std::endl;
			return;
		}

		std::stringstream ss;
		dataValue.variant()->out(ss);
		monitorTable_->item(itemRow->rowIdx(), 2)->setText(ss.str().c_str());

		std::stringstream sourceTimeStampSS;
		sourceTimeStampSS << dataValue.sourceTimestamp().dateTime();
		monitorTable_->item(itemRow->rowIdx(), 3)->setText(sourceTimeStampSS.str().c_str());

		std::stringstream serverTimeStampSS;
		serverTimeStampSS << dataValue.serverTimestamp().dateTime();
		monitorTable_->item(itemRow->rowIdx(), 4)->setText(serverTimeStampSS.str().c_str());
	}

	// ##################################################################
	//
	//  Display information from the BaseNode into the table
	//
	// ##################################################################

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

	// ##################################################################
	//
	//  Handle row menu
	//
	// ##################################################################

	void
	MonitorItemWindow::slotPrepareMenu(const QPoint& pos)
	{
		QMenu menu(this);
		ItemRowMenuHandler* itemRowMenuHandler = new ItemRowMenuHandler(pos);

		QAction* attributeAction = new QAction(QIcon(":images/Delete.png"), tr("Remove Value"), this);
		connect(attributeAction, SIGNAL(triggered()), itemRowMenuHandler, SLOT(handleMenuActionRemove()));
		connect(itemRowMenuHandler, SIGNAL(signalMenuActionRemove(QPoint&)), this, SLOT(menuActionRemove(QPoint&)));
		menu.addAction(attributeAction);

		menu.exec(monitorTable_->mapToGlobal(pos));
	}

	void
	MonitorItemWindow::menuActionRemove(QPoint& pos)
	{
		QTableWidgetItem* item = monitorTable_->itemAt(pos);
		uint32_t row = monitorTable_->row(item);

		ItemRow* itemRow = findRowTimeByRowIdx(row);
		if (itemRow == nullptr)
		{
			return;
		}

		// stop monitoring
		if (client_->syncDeleteMonitorItem(itemRow->monitoredItemId()) != Success)
		{
			std::cout << "ERROR by creating monitored item" << std::endl;
			// TODO error by creating monitored item
		}

		// remove row from table
		monitorTable_->removeRow(row);

		// remove row from item map
		removeRowItem(itemRow->clientHandle());
	}

	// ##################################################################
	//
	//  Handle row items in a map
	//
	// ##################################################################

	ItemRow*
	MonitorItemWindow::addRowItem(BaseNode* baseNode, uint32_t row)
	{
		ItemRow* rowItem = new ItemRow();
		rowItem->set(row, baseNode);

		uint32_t clientHandle = generateClientHanlde();
		if (clientHandle == 0)
		{
			return nullptr;
		}
		rowItem->clientHandle(clientHandle);

		rowItems_.insert(std::make_pair(clientHandle, rowItem));
		return rowItem;
	}

	ItemRow*
	MonitorItemWindow::getRowItem(uint32_t clientHandle)
	{
		if (rowItems_.find(clientHandle) != rowItems_.end())
		{
			ItemRow* itemRow = rowItems_[clientHandle];
			return itemRow;
		}
		return nullptr;
	}

	void
	MonitorItemWindow::removeRowItem(uint32_t clientHandle)
	{
		ItemRow* itemRow = getRowItem(clientHandle);
		delete(itemRow);
		rowItems_.erase(clientHandle);
	}

	ItemRow*
	MonitorItemWindow::findRowTimeByRowIdx(uint32_t row)
	{
	    std::map<uint32_t, ItemRow*>::iterator it = rowItems_.begin();
	    while (it != rowItems_.end())
	    {
	        if (it->second->rowIdx() == row)
	        {
	        	return it->second;
	        }
	        it++;
	    }
	    return nullptr;
	}

	uint32_t
	MonitorItemWindow::generateClientHanlde(void)
	{
		for (uint32_t newClientHandle = 1; newClientHandle <= MAX_CLIENT_HANDLES; newClientHandle++)
		{
			if (rowItems_.find(newClientHandle) == rowItems_.end())
			{
				return newClientHandle;
			}
		}
		return 0;
	}

} /* namespace OpcUaClientModul */
