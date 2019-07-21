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

#include <QLabel>
#include <QVBoxLayout>

#include "OpcUaStackCore/StandardDataTypes/DataTypeDefinition.h"
#include "OpcUaStackServer/AddressSpaceModel/DataTypeNodeClass.h"
#include "OpcUaNodeSetModul/NodeSetWindow/DataTypeNoneTable.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{

	DataTypeNoneTable::DataTypeNoneTable(QWidget* parent)
	: QWidget()
	{
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->addWidget(new QLabel("no definition"));

		this->setLayout(vBoxLayout);
	}

	DataTypeNoneTable::~DataTypeNoneTable(void)
	{
	}

	void
	DataTypeNoneTable::nodeChange(NodeInfo* nodeInfo)
	{
	}

	void
	DataTypeNoneTable::enabled(bool enabled)
	{
		// nothing to do
	}

}


