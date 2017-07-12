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

#ifndef __OpcUaNodeSet_DataTypeStructTable_h__
#define __OpcUaNodeSet_DataTypeStructTable_h__

#include <QWidget>

#include "OpcUaStackCore/DataType/DataTypeDefinition.h"
#include "OpcUaNodeSetModul/Base/NodeInfo.h"

using namespace OpcUaStackServer;

class QTableWidget;

namespace OpcUaNodeSet
{

	class DataTypeStructTable
	: public QWidget
	{
		Q_OBJECT

	  public:
		DataTypeStructTable(QWidget* parent = 0);
		virtual ~DataTypeStructTable(void);

		void nodeChange(NodeInfo* nodeInfo);

	  private:
		void setName(uint32_t row, DataTypeField::SPtr& dataField);
		void setDataType(uint32_t row, DataTypeField::SPtr& dataField);
		void setValueRank(uint32_t row, DataTypeField::SPtr& dataField);
		void setDescription(uint32_t row, DataTypeField::SPtr& dataField);
		void setIsOptional(uint32_t row, DataTypeField::SPtr& dataField);

		QTableWidget* structTable_;
	};

}

#endif
