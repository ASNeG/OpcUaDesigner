/*
   Copyright 2017 Kai Huebl (kai@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Kai Huebl (kai@huebl-sgh.de)
 */

#ifndef __OpcUaNodeSet_OpcUaTreeWindow_h__
#define __OpcUaNodeSet_OpcUaTreeWindow_h__

#include <QWidget>

#include "OpcUaStackServer/AddressSpaceModel/BaseNodeClass.h"
#include "OpcUaNodeSetModul/NodeSetWindow/NodeInfo.h"
#include "OpcUaNodeSetModul/Model/DataModel.h"

class QTreeWidget;
class QTreeWidgetItem;
class QMenu;

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{

	class OpcUaTreeWindow
	: public QWidget
	{
		Q_OBJECT

	  public:
		OpcUaTreeWindow(QWidget* parent = 0);
		virtual ~OpcUaTreeWindow(void);

		void dataModel(DataModel* dataModel);
		bool show(void);

	  public slots:
	    void onCurrentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previos);

	    //
	  	// context menu
	    //
	    void onCustomContextMenuRequested(const QPoint& pos);
	    void onNewAction(void);
	    void onDeleteAction(void);

	  signals:
	    void nodeChanged(NodeInfo* nodeInfo);

	  private:
	    //
	    // context menu
	    //
	    void createNewMenu(QMenu& menu, NodeInfo* nodeInfo);
	    void createDeleteMenu(QMenu& menu, NodeInfo* nodeInfo);

		void addNode(
			InformationModel::SPtr& informationModel,
			QTreeWidgetItem* parentItem,
			BaseNodeClass::SPtr& baseNode
		);
		void removeNode(QTreeWidgetItem* item);

		DataModel* dataModel_;

		QTreeWidget* opcUaTree_;
		QTreeWidgetItem* rootItem_;
		QTreeWidgetItem* actItem_;
	};

}

#endif
