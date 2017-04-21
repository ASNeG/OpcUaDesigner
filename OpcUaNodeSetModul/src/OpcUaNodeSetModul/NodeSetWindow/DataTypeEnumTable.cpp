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

#include <QLineEdit>
#include <QVBoxLayout>

#include "OpcUaStackServer/AddressSpaceModel/DataTypeNodeClass.h"
#include "OpcUaStackServer/NodeSet/DataTypeDefinition.h"
#include "OpcUaNodeSetModul/NodeSetWindow/DataTypeEnumTable.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	DataTypeEnumTable::DataTypeEnumTable(QWidget* parent)
	: QWidget()
	{
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		definitionLineEdit_ = new QLineEdit("Enumeration");
		vBoxLayout->addWidget(definitionLineEdit_);

		this->setLayout(vBoxLayout);
	}

	DataTypeEnumTable::~DataTypeEnumTable(void)
	{
	}

	void
	DataTypeEnumTable::nodeChange(NodeInfo* nodeInfo)
	{
	}

}


