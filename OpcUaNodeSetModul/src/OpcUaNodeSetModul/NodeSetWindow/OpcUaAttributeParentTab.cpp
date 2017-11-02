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

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "OpcUaStackServer/InformationModel/InformationModelAccess.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeParentTab.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	OpcUaAttributeParentTab::OpcUaAttributeParentTab(QWidget* parent)
	: QWidget()
	{
		QHBoxLayout* hBoxLayout;
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		QGridLayout* gridLayout = new QGridLayout();


		// DisplayName
		QLabel* displayNameLabel = new QLabel("DisplayName");
		gridLayout->addWidget(displayNameLabel, 1, 0, Qt::AlignTop);

		displayNameLineEdit_ = new QLineEdit();
		displayNameLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(displayNameLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);


		// NodeId
		QLabel* nodeIdLabel = new QLabel("NodeId");
		gridLayout->addWidget(nodeIdLabel, 2, 0, Qt::AlignTop);

		nodeIdLineEdit_ = new QLineEdit();
		nodeIdLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(nodeIdLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 2, 1);

		// BrowseName
		QLabel* browseNameLabel = new QLabel("BrowseName");
		gridLayout->addWidget(browseNameLabel, 3, 0, Qt::AlignTop);

		browseNameLineEdit_ = new QLineEdit();
		browseNameLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(browseNameLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 3, 1);


		// Reference
		QLabel* referenceLabel = new QLabel("Reference");
		gridLayout->addWidget(referenceLabel, 4, 0, Qt::AlignTop);

		referenceLineEdit_ = new QLineEdit();
		referenceLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(referenceLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 4, 1);


		vBoxLayout->addLayout(gridLayout);
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);
	}

	OpcUaAttributeParentTab::~OpcUaAttributeParentTab(void)
	{
	}

	void
	OpcUaAttributeParentTab::nodeChange(NodeInfo* nodeInfo)
	{
		setDisplayName(nodeInfo);
		setNodeId(nodeInfo);
		setBrowseName(nodeInfo);
		setReference(nodeInfo);
	}

	void
	OpcUaAttributeParentTab::setDisplayName(NodeInfo* nodeInfo)
	{
		bool success;

		// get parent base node
		BaseNodeClass::Vec childBaseNodeClassVec;
		InformationModelAccess ima(nodeInfo->informationModel_);
		success = ima.getParent(nodeInfo->baseNode_, childBaseNodeClassVec);
		if (!success || childBaseNodeClassVec.size() == 0) {
			displayNameLineEdit_->setText(QString(""));
			return;
		}

		// set display name
		BaseNodeClass::SPtr baseNode = childBaseNodeClassVec[0];
		if (baseNode->isNullDisplayName()) {
			displayNameLineEdit_->setText(QString(""));
		}
		else {
			OpcUaLocalizedText displayName;
			baseNode->getDisplayName(displayName);
			displayNameLineEdit_->setText(QString(displayName.toString().c_str()));
		}

	}

	void
	OpcUaAttributeParentTab::setNodeId(NodeInfo* nodeInfo)
	{
		bool success;

		// get parent base node
		BaseNodeClass::Vec childBaseNodeClassVec;
		InformationModelAccess ima(nodeInfo->informationModel_);
		success = ima.getParent(nodeInfo->baseNode_, childBaseNodeClassVec);
		if (!success || childBaseNodeClassVec.size() == 0) {
			nodeIdLineEdit_->setText(QString(""));
			return;
		}

		// set node id
		BaseNodeClass::SPtr baseNode = childBaseNodeClassVec[0];
		if (baseNode->isNullNodeId()) {
			nodeIdLineEdit_->setText(QString(""));
		}
		else {
			OpcUaNodeId nodeId;
			baseNode->getNodeId(nodeId);
			nodeIdLineEdit_->setText(QString(nodeId.toString().c_str()));
		}
	}

	void
	OpcUaAttributeParentTab::setBrowseName(NodeInfo* nodeInfo)
	{
		bool success;

		// get parent base node
		BaseNodeClass::Vec childBaseNodeClassVec;
		InformationModelAccess ima(nodeInfo->informationModel_);
		success = ima.getParent(nodeInfo->baseNode_, childBaseNodeClassVec);
		if (!success || childBaseNodeClassVec.size() == 0) {
			browseNameLineEdit_->setText(QString(""));
			return;
		}

		BaseNodeClass::SPtr baseNode = childBaseNodeClassVec[0];
		if (baseNode->isNullBrowseName()) {
			browseNameLineEdit_->setText(QString(".."));
		}
		else {
			OpcUaQualifiedName browseName;
			baseNode->getBrowseName(browseName);
			browseNameLineEdit_->setText(QString(browseName.toString().c_str()));
		}
	}

	void
	OpcUaAttributeParentTab::setReference(NodeInfo* nodeInfo)
	{
		bool success;

		// get parent base node
		ReferenceItem::Vec referenceItemVec;
		std::vector<OpcUaNodeId> referenceTypeNodeIdVec;
		InformationModelAccess ima(nodeInfo->informationModel_);
		success = ima.getParentReference(nodeInfo->baseNode_, referenceTypeNodeIdVec, referenceItemVec);
		if (!success || referenceTypeNodeIdVec.size() == 0) {
			referenceLineEdit_->setText(QString(""));
			return;
		}

		// set reference type
		OpcUaNodeId nodeId = referenceTypeNodeIdVec[0];
		std::string referenceTypeString = ReferenceTypeMap::typeToString(ReferenceTypeMap::nodeIdToReferenceType(nodeId));
		if (referenceTypeString == "Unknown") referenceTypeString = nodeId.toString();
		referenceLineEdit_->setText(QString(referenceTypeString.c_str()));
	}

}


