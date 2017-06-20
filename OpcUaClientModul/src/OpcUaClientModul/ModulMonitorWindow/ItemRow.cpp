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

	ItemRow::ItemRow()
	: baseNode_(nullptr)
	, rowIdx_(0)
	, clientHandle_(0)
	, monitoredItemId_(0)
	{
	}

	ItemRow::~ItemRow()
	{
	}

	void
	ItemRow::set(uint32_t rowIdx, BaseNode* baseNode)
	{
		rowIdx_ = rowIdx;
		baseNode_ = baseNode;
	}

	BaseNode*
	ItemRow::baseNode(void)
	{
		return baseNode_;
	}

	uint32_t
	ItemRow::rowIdx(void)
	{
		return rowIdx_;
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

} /* namespace OpcUaClientModul */
