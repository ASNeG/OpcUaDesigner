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

#include <OpcUaClientModul/ModulMonitorWindow/ItemRow.h>

namespace OpcUaClientModul
{

	ItemRow::ItemRow(BaseNode* baseNode)
	: baseNode_(baseNode)
	, clientHandle_(0)
	, monitoredItemId_(0)
	, itemNodeId_(nullptr)
	, itemDataValue_(nullptr)
	, itemSourceTimestamp_(nullptr)
	, itemServerTimestamp_(nullptr)
	{
	}

	ItemRow::~ItemRow()
	{
	}

	BaseNode*
	ItemRow::baseNode(void)
	{
		return baseNode_;
	}

	void
	ItemRow::clientHandle(uint32_t clientHandle)
	{
		clientHandle_ = clientHandle;
	}

	uint32_t
	ItemRow::clientHandle(void)
	{
		return clientHandle_;
	}

	void
	ItemRow::monitoredItemId(uint32_t monitoredItemId)
	{
		monitoredItemId_ = monitoredItemId;
	}

	uint32_t
	ItemRow::monitoredItemId(void)
	{
		return monitoredItemId_;
	}

	void
	ItemRow::itemNodeId(QTableWidgetItem* itemNodeId)
	{
		itemNodeId_ = itemNodeId;
	}

	QTableWidgetItem*
	ItemRow::itemNodeId(void)
	{
		return itemNodeId_;
	}

	void
	ItemRow::itemDataValue(QTableWidgetItem* itemDataValue)
	{
		itemDataValue_ = itemDataValue;
	}

	QTableWidgetItem*
	ItemRow::itemDataValue(void)
	{
		return itemDataValue_;
	}

	void
	ItemRow::itemSourceTimestamp(QTableWidgetItem* itemSourceTimestamp)
	{
		itemSourceTimestamp_ = itemSourceTimestamp;
	}

	QTableWidgetItem*
	ItemRow::itemSourceTimestamp(void)
	{
		return itemSourceTimestamp_;
	}

	void
	ItemRow::itemServerTimestamp(QTableWidgetItem* itemServerTimestamp)
	{
		itemServerTimestamp_ = itemServerTimestamp;
	}

	QTableWidgetItem*
	ItemRow::itemServerTimestamp(void)
	{
		return itemServerTimestamp_;
	}

} /* namespace OpcUaClientModul */
