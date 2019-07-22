/*
 Copyright 2016-2019 Samuel Huebl (samuel@huebl-sgh.de)

 Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
 Datei nur in Übereinstimmung mit der Lizenz erlaubt.
 Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

 Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
 erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
 GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

 Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
 im Rahmen der Lizenz finden Sie in der Lizenz.

 Autor: Samuel Huebl (samuel@huebl-sgh.de)
        Kai Huebl (kai@huebl-sgh.de)
 */

#ifndef __OpcUaClientModul_TreeNodeWidget_h__
#define __OpcUaClientModul_TreeNodeWidget_h__

#include <QWidget>
#include <QHeaderView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QVariant>
#include <QPoint>
#include <QAction>
#include <QMenu>

#include "OpcUaStackCore/StandardDataTypes/NodeClass.h"
#include "OpcUaClientModul/Base/BaseNode.h"
#include "OpcUaClientModul/Base/OpcUaClient.h"
#include "OpcUaClientModul/ModulMainWidgets/TreeMenuHandler.h"

namespace OpcUaClientModul
{
	class TreeNodeWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		TreeNodeWidget(OpcUaClient* client);
		virtual ~TreeNodeWidget();

		bool create(void);

	  public slots:
		void myItemDoubleClicked(QTreeWidgetItem* parentItem, int row);
		void myItemClicked(QTreeWidgetItem* item, int row);
		void prepareMenu(const QPoint& point);

		void menuActionMonitor(QPoint& pos);
		void menuActionBrowse(QPoint& pos);
		void menuActionAttribute(QPoint& pos);

	  signals:
	  	void nodeChanged(BaseNode* baseNode);
	  	void signalCreateNewMonitorItem(BaseNode* baseNode);

	  private:
		QIcon createQIcon(NodeClass::Enum nodeClass, OpcUaExpandedNodeId::SPtr typeNodeId);

		void browseNextElements(QTreeWidgetItem* parentItem);
		void addNode(QTreeWidgetItem* parentItem, ReferenceDescriptionArray::SPtr& references);

		QTreeWidget* opcUaTree_;
		OpcUaClient* client_;
	};
} /* namespace OpcUaClientModul */

#endif /* __OpcUaClientModul_TreeNodeWidget_h__ */
