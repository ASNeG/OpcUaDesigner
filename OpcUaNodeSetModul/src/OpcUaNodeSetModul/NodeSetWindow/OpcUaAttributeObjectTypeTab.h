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

#ifndef __OpcUaNodeSet_OpcUaAttributeObjectTypeTab_h__
#define __OpcUaNodeSet_OpcUaAttributeObjectTypeTab_h__

#include <QWidget>

#include "OpcUaNodeSetModul/Base/NodeInfo.h"
#include "OpcUaNodeSetModul/OpcUaAttributeWidget/IsAbstractWidget.h"

class QLineEdit;
class QToolBar;

namespace OpcUaNodeSet
{

	class OpcUaAttributeObjectTypeTab
	: public QWidget
	{
		Q_OBJECT

	  public:
		OpcUaAttributeObjectTypeTab(QWidget* parent = 0);
		virtual ~OpcUaAttributeObjectTypeTab(void);

		void nodeChange(NodeInfo* nodeInfo);

	  signals:
		void updateTab(void);

	  public slots:
	  	//
	    // toolbar menu
	    //
		void onOrderOkAction(void);
		void onOrderDeleteAction(void);

	    //
	    // widgets
	    //
		void update(void);

	  private:
		//
		// toolbar menu
		//
		void createToolBarActions(void);

		QToolBar* tableToolBar_;
		QAction* orderOkAction_;
		QAction* orderDeleteAction_;

		NodeInfo* nodeInfo_;
		IsAbstractWidget* isAbstractWidget_;
	};

}

#endif
