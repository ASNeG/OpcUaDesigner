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

#ifndef __OpcUaNodeSet_OpcUaAttributeDataTypeTab_h__
#define __OpcUaNodeSet_OpcUaAttributeDataTypeTab_h__

#include <QWidget>

#include "OpcUaNodeSetModul/NodeSetWindow/NodeInfo.h"
#include "OpcUaNodeSetModul/NodeSetWindow/DataTypeNoneTable.h"
#include "OpcUaNodeSetModul/NodeSetWindow/DataTypeEnumTable.h"
#include "OpcUaNodeSetModul/NodeSetWindow/DataTypeStructTable.h"

class QLineEdit;
class QStackedWidget;

namespace OpcUaNodeSet
{

	class OpcUaAttributeDataTypeTab
	: public QWidget
	{
		Q_OBJECT

	  public:
		OpcUaAttributeDataTypeTab(QWidget* parent = 0);
		virtual ~OpcUaAttributeDataTypeTab(void);

		void nodeChange(NodeInfo* nodeInfo);

	  private:
		void setIsAbstract(NodeInfo* nodeInfo);
		void setUserWriteMask(NodeInfo* nodeInfo);
		void setWriteMask(NodeInfo* nodeInfo);
		void setDefinition(NodeInfo* nodeInfo);

		QLineEdit* isAbstractLineEdit_;
		QLineEdit* userWriteMaskLineEdit_;
		QLineEdit* writeMaskLineEdit_;

		QStackedWidget* definitionWidget_;
		DataTypeNoneTable* noneDefinitionWidget_;
		DataTypeEnumTable* enumDefinitionWidget_;
		DataTypeStructTable* structDefinitionWidget_;
	};

}

#endif
