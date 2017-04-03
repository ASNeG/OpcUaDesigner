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

#ifndef __OpcUaNodeSet_OpcUaAttributeSpecialTab_h__
#define __OpcUaNodeSet_OpcUaAttributeSpecialTab_h__

#include "OpcUaNodeSetModul/NodeSetWindow/NodeInfo.h"

#include <QWidget>

class QLineEdit;
class QStackedWidget;

namespace OpcUaNodeSet
{

	class OpcUaAttributeObjectTab;
	class OpcUaAttributeValueTab;
	class OpcUaAttributeValueTypeTab;
	class OpcUaAttributeObjectTypeTab;
	class OpcUaAttributeReferenceTypeTab;
	class OpcUaAttributeDataTypeTab;
	class OpcUaAttributeMethodTab;

	class OpcUaAttributeSpecialTab
	: public QWidget
	{
		Q_OBJECT

	  public:
		OpcUaAttributeSpecialTab(QWidget* parent = 0);
		virtual ~OpcUaAttributeSpecialTab(void);

		void nodeChange(NodeInfo* nodeInfo);

	  private:
		QStackedWidget* specialAttributeWidget_;
		OpcUaAttributeObjectTab* attributeObjectTab_;
		OpcUaAttributeValueTab* attributeValueTab_;
		OpcUaAttributeValueTypeTab* attributeValueTypeTab_;
		OpcUaAttributeObjectTypeTab* attributeObjectTypeTab_;
		OpcUaAttributeReferenceTypeTab* attributeReferenceTypeTab_;
		OpcUaAttributeDataTypeTab* attributeDataTypeTab_;
		OpcUaAttributeMethodTab* attributeMethodTab_;
	};

}

#endif
