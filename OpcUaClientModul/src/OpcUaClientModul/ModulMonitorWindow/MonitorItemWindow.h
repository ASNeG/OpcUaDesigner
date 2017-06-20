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

#ifndef __OpcUaClientModul_MonitorItemWindow_h__
#define __OpcUaClientModul_MonitorItemWindow_h__

#include <QMainWindow>
#include <QString>
#include <QDockWidget>
#include <QStatusBar>
#include <QStringList>
#include <QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "OpcUaClientModul/Tools/OpcUaClientProvider.h"
#include "OpcUaClientModul/Base/BaseNode.h"

namespace OpcUaClientModul
{

	class MonitorItemWindow
	: public QMainWindow
	{
		Q_OBJECT

 	  public:
		MonitorItemWindow(OpcUaClientProvider* client);
		virtual ~MonitorItemWindow();

		bool create(void);
		bool open(void);

	  public slots:
		void createNewMonitorItem(BaseNode* baseNode);
		void updateMonitoredItem(OpcUaUInt32 clientHandle, OpcUaDataValue& dataValue);

	  private:
		void setDisplayName(BaseNode* baseNode, uint32_t row);
		void setNodeId(BaseNode* baseNode, uint32_t row);
		void setValue(BaseNode* baseNode, uint32_t row);
		void setSourceTimestamp(BaseNode* baseNode, uint32_t row);
		void setServerTimestamp(BaseNode* baseNode, uint32_t row);

		OpcUaClientProvider* client_;

		QTableWidget* monitorTable_;
	};

} /* namespace OpcUaClientModul */

#endif /* __OpcUaClientModul_MonitorItemWindow_h__ */
