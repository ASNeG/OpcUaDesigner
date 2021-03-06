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

#ifndef __OpcUaClientModul_ModulMainWindow_h__
#define __OpcUaClientModul_ModulMainWindow_h__

#include <QMainWindow>
#include <QString>
#include <QDockWidget>
#include <QStatusBar>

#include "OpcUaClientModul/Base/BaseNode.h"
#include "OpcUaClientModul/Base/OpcUaClient.h"
#include "OpcUaClientModul/ModulMainWidgets/AttributeWidget.h"
#include "OpcUaClientModul/ModulMainWidgets/ConnectionInfoWidget.h"
#include "OpcUaClientModul/ModulMainWidgets/TreeNodeWidget.h"

namespace OpcUaClientModul
{
	class ModulMainWindow
	: public QMainWindow
	{
		Q_OBJECT

	  public:
		ModulMainWindow(QMainWindow* parentMainWindow, OpcUaClient* client);
		virtual ~ModulMainWindow();

		bool create(void);
		bool open(void);

		void modulName(const std::string& modulName);
		std::string modulName(void);

	  public slots:
		void nodeChange(BaseNode* baseNode, int raw);
		void slotCreateNewMonitorItem(BaseNode* baseNode);

	  signals:
		void signalCreateNewMonitorItem(BaseNode* baseNode);

	  private:
		std::string modulName_;

		OpcUaClient* client_;

		QMainWindow* parentMainWindow_;
		TreeNodeWidget* treeNodeWidget_;
		AttributeWidget* attributeWidget_;
		ConnectionInfoWidget* connectionInfoWidget_;
	};
}

#endif /* __OpcUaClientModul_ModulMainWindow_h__ */
