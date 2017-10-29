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

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QIcon>

#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackServer/InformationModel/InformationModelAccess.h"
#include "OpcUaNodeSetModul/OpcUaAttributeWidget/DataTypeWidget.h"
#include "OpcUaNodeSetModul/Dialog/SelectDataTypeDialog.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	DataTypeWidget::DataTypeWidget(QWidget* parent)
	: OpcUaNodeIdWidget()
	, nodeInfo_(nullptr)
	{
		connect(
			this, SIGNAL(selectDataType()),
			this, SLOT(onSelectDataType())
		);
	}

	DataTypeWidget::~DataTypeWidget(void)
	{
	}

	void
	DataTypeWidget::nodeChange(NodeInfo* nodeInfo)
	{
		nodeInfo_ = nodeInfo;

		rootNodeId(OpcUaNodeId(OpcUaId_BaseDataType));
		informationModel(nodeInfo->informationModel_);

		// get data type
		OpcUaNodeId dataTypeNodeId;
		nodeInfo->baseNode_->getDataTypeSync(dataTypeNodeId);
		setSavedValue(dataTypeNodeId);
	}

	void
	DataTypeWidget::onSelectDataType(void)
	{
		SelectDataTypeDialog dialog(nodeInfo_->informationModel_);
		dialog.exec();

		if (!dialog.itemSelected()) return;

		OpcUaNodeId dataType = dialog.dataType();
		setDisplayValue(dataType);
	}

}


