/*
   Copyright 2017-2019 Kai Huebl (kai@huebl-sgh.de)

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

#ifndef __OpcUaNodeSet_OpcUaAttributeWindow_h__
#define __OpcUaNodeSet_OpcUaAttributeWindow_h__

#include "OpcUaStackServer/AddressSpaceModel/BaseNodeClass.h"
#include "OpcUaNodeSetModul/Base/NodeInfo.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeBaseTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeSpecialTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeRefTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeParentTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeChildTab.h"

#include <QWidget>
#include <QTabWidget>

namespace OpcUaNodeSet
{

	class OpcUaAttributeWindow
	: public QWidget
	{
		Q_OBJECT

	  public:
		OpcUaAttributeWindow(QWidget* parent = 0);
		virtual ~OpcUaAttributeWindow(void);

	  signals:
	    void updateTab(void);

	  public slots:
	    void onUpdateTab(void);
		void onNodeChanged(NodeInfo* nodeInfo);
		void onCurrendChanged(int index);

	  private:
		QTabWidget* opcUaAttributeTab_;
		OpcUaAttributeBaseTab* tabBase_;
		OpcUaAttributeSpecialTab* tabSpecial_;
		OpcUaAttributeParentTab* tabParent_;
		OpcUaAttributeChildTab* tabChild_;
		OpcUaAttributeRefTab* tabRef_;

		NodeInfo* nodeInfo_;
	};

}

#endif
