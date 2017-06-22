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

#ifndef __OpcUaClientModul_ItemRow_h__
#define __OpcUaClientModul_ItemRow_h__

#include <QTableWidgetItem>

#include "OpcUaClientModul/Base/BaseNode.h"

namespace OpcUaClientModul
{

	class ItemRow
	{
	  public:
		ItemRow(BaseNode* baseNode);
		virtual ~ItemRow();

		BaseNode* baseNode(void);

		void clientHandle(uint32_t clientHandle);
		uint32_t clientHandle(void);

		void monitoredItemId(uint32_t monitorItemId);
		uint32_t monitoredItemId(void);

		void itemNodeId(QTableWidgetItem* itemNodeId);
		QTableWidgetItem* itemNodeId(void);

		void itemDataValue(QTableWidgetItem* itemDataValue);
		QTableWidgetItem* itemDataValue(void);

		void itemSourceTimestamp(QTableWidgetItem* itemSourceTimestamp);
		QTableWidgetItem* itemSourceTimestamp(void);

		void itemServerTimestamp(QTableWidgetItem* itemServerTimestamp);
		QTableWidgetItem* itemServerTimestamp(void);

	  private:
		BaseNode* baseNode_;

		uint32_t clientHandle_;
		uint32_t monitoredItemId_;

		QTableWidgetItem* itemNodeId_;
		QTableWidgetItem* itemDataValue_;
		QTableWidgetItem* itemSourceTimestamp_;
		QTableWidgetItem* itemServerTimestamp_;
	};

} /* namespace OpcUaClientModul */

#endif /* __OpcUaClientModul_ItemRow_h__ */
