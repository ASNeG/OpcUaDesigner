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
#include <QStackedWidget>

#include "OpcUaStackServer/AddressSpaceModel/DataTypeNodeClass.h"
#include "OpcUaStackServer/NodeSet/DataTypeDefinition.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeDataTypeTab.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	OpcUaAttributeDataTypeTab::OpcUaAttributeDataTypeTab(QWidget* parent)
	: QWidget()
	{
		QHBoxLayout* hBoxLayout;
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		QGridLayout* gridLayout = new QGridLayout();


		// IsAbstract
		QLabel* isAbstractLabel = new QLabel("IsAbstract");
		gridLayout->addWidget(isAbstractLabel, 0, 0);

		isAbstractLineEdit_ = new QLineEdit();
		isAbstractLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(isAbstractLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 0, 1);


		// UserWriteMask
		QLabel* userWriteMaskLabel = new QLabel("UserWriteMask");
		gridLayout->addWidget(userWriteMaskLabel, 1, 0);

		userWriteMaskLineEdit_ = new QLineEdit();
		userWriteMaskLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(userWriteMaskLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 1, 1);


		// WriteMask
		QLabel* writeMaskLabel = new QLabel("WriteMask");
		gridLayout->addWidget(writeMaskLabel, 2, 0);

		writeMaskLineEdit_ = new QLineEdit();
		writeMaskLineEdit_->setFixedWidth(300);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(writeMaskLineEdit_);
		hBoxLayout->addStretch();

		gridLayout->addLayout(hBoxLayout, 2, 1);

		vBoxLayout->addLayout(gridLayout);

		// definition
		definitionWidget_ = new QStackedWidget();

		noneDefinitionWidget_ = new DataTypeNoneTable();
		definitionWidget_->addWidget(noneDefinitionWidget_);

		enumDefinitionWidget_ = new DataTypeEnumTable();
		definitionWidget_->addWidget(enumDefinitionWidget_);

		structDefinitionWidget_ = new DataTypeStructTable();
		definitionWidget_->addWidget(structDefinitionWidget_);

		vBoxLayout->addWidget(definitionWidget_);


		vBoxLayout->addStretch();

		setLayout(vBoxLayout);
	}

	OpcUaAttributeDataTypeTab::~OpcUaAttributeDataTypeTab(void)
	{
	}

	void
	OpcUaAttributeDataTypeTab::nodeChange(NodeInfo* nodeInfo)
	{
		setIsAbstract(nodeInfo);
		setUserWriteMask(nodeInfo);
		setWriteMask(nodeInfo);
		setDefinition(nodeInfo);
	}

	void
	OpcUaAttributeDataTypeTab::setIsAbstract(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullIsAbstract()) {
			isAbstractLineEdit_->setText(QString(""));
		}
		else {
			OpcUaBoolean isAbstract;
			baseNode->getIsAbstract(isAbstract);
			isAbstractLineEdit_->setText(isAbstract == 1 ? QString("True") : QString("False"));
		}
	}

	void
	OpcUaAttributeDataTypeTab::setUserWriteMask(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullUserWriteMask()) {
			userWriteMaskLineEdit_->setText(QString(""));
		}
		else {
			OpcUaUInt32 userWriteMask;
			baseNode->getUserWriteMask(userWriteMask);
			userWriteMaskLineEdit_->setText(QString("%1").arg((uint32_t)userWriteMask));
		}
	}

	void
	OpcUaAttributeDataTypeTab::setWriteMask(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullWriteMask()) {
			writeMaskLineEdit_->setText(QString(""));
		}
		else {
			OpcUaUInt32 writeMask;
			baseNode->getWriteMask(writeMask);
			writeMaskLineEdit_->setText(QString("%1").arg((uint32_t)writeMask));
		}
	}

	void
	OpcUaAttributeDataTypeTab::setDefinition(NodeInfo* nodeInfo)
	{
		// get data type node
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		DataTypeNodeClass::SPtr dataTypeNode = boost::static_pointer_cast<DataTypeNodeClass>(baseNode);

		// get definition object
		Object::SPtr object = dataTypeNode->dataTypeDefinition();
		if (object.get() == nullptr) {
			noneDefinitionWidget_->nodeChange(nodeInfo);
			definitionWidget_->setCurrentIndex(0);
			return;
		}

		// cast to definition type
		DataTypeDefinition::SPtr definition = boost::static_pointer_cast<DataTypeDefinition>(object);
		if (definition->dataSubType() == Enumeration) {
			enumDefinitionWidget_->nodeChange(nodeInfo);
			definitionWidget_->setCurrentIndex(1);
		}
		else {
			structDefinitionWidget_->nodeChange(nodeInfo);
			definitionWidget_->setCurrentIndex(2);
		}
	}

}

