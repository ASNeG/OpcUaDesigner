/*
 Copyright 2016-2017 Samuel Huebl (samuel@huebl-sgh.de)

 Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
 Datei nur in Übereinstimmung mit der Lizenz erlaubt.
 Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

 Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
 erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
 GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

 Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
 im Rahmen der Lizenz finden Sie in der Lizenz.

 Autor: Samuel Huebl (samuel@huebl-sgh.de)
 */

#include "OpcUaClientModul/ModulMainWidgets/AttributeWidget.h"

using namespace OpcUaStackCore;

namespace OpcUaClientModul
{

	AttributeWidget::AttributeWidget(OpcUaClientProvider* client)
	: QWidget()
	, client_(client)
	{
		LineWidget* lineWidget;
		QHBoxLayout* hBoxLayout;
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->setMargin(25);

		lineWidget = new LineWidget();
		vBoxLayout->addWidget(lineWidget);

		// NodeId
		QLabel* nodeIdLabel = new QLabel("NodeId");
		nodeIdLabel->setFixedWidth(140);

		nodeIdWidget_ = new NodeIdWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->addWidget(nodeIdLabel);
		hBoxLayout->addWidget(nodeIdWidget_);

		vBoxLayout->addLayout(hBoxLayout);

		// NodeClass
		QLabel* nodeClassLabel = new QLabel("NodeClass");
		nodeClassLabel->setFixedWidth(140);

		nodeClassWidget_ = new NodeClassWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->addWidget(nodeClassLabel);
		hBoxLayout->addWidget(nodeClassWidget_);

		vBoxLayout->addLayout(hBoxLayout);

		// BrowseName
		QLabel* browseNameLabel = new QLabel("BrowseName");
		browseNameLabel->setFixedWidth(140);

		browseNameWidget_ = new BrowseNameWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->addWidget(browseNameLabel);
		hBoxLayout->addWidget(browseNameWidget_);

		vBoxLayout->addLayout(hBoxLayout);

		// Description
		QLabel* descriptionLabel = new QLabel("Description");
		descriptionLabel->setFixedWidth(140);

		descriptionWidget_ = new DescriptionWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->addWidget(descriptionLabel);
		hBoxLayout->addWidget(descriptionWidget_);

		vBoxLayout->addLayout(hBoxLayout);

		// Line Widget
		lineWidget = new LineWidget();
		vBoxLayout->addWidget(lineWidget);

		// Write Mask
		QLabel* writeMaskLabel = new QLabel("WriteMask");
		writeMaskLabel->setFixedWidth(140);

		writeMaskWidget_ = new WriteMaskWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->addWidget(writeMaskLabel);
		hBoxLayout->addWidget(writeMaskWidget_);

		vBoxLayout->addLayout(hBoxLayout);

		// User Write Mask
		QLabel* userWriteMaskLabel = new QLabel("UserWriteMask");
		userWriteMaskLabel->setFixedWidth(140);

		userWriteMaskWidget_ = new UserWriteMaskWidget();

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->addWidget(userWriteMaskLabel);
		hBoxLayout->addWidget(userWriteMaskWidget_);

		vBoxLayout->addLayout(hBoxLayout);

		// Value
		valueWidget_ = new ValueWidget();

		connect(
				valueWidget_, SIGNAL(signalWrite(BaseNode*)),
				this, SLOT(slotWrite(BaseNode*))
		);

		hBoxLayout = new QHBoxLayout();
		hBoxLayout->setMargin(0);
		hBoxLayout->addWidget(valueWidget_);

		vBoxLayout->addLayout(hBoxLayout);

		// Line Widget
		lineWidget = new LineWidget();
		vBoxLayout->addWidget(lineWidget);

		// Complete Attribute layout
		vBoxLayout->addStretch();

		setLayout(vBoxLayout);
	}

	AttributeWidget::~AttributeWidget()
	{
	}

	void
	AttributeWidget::readAttributesFromServer(BaseNode* baseNode)
	{
		std::cout << "readAttributeFromServer" << std::endl;

		OpcUaStatusCode result;

		OpcUaNodeId nodeId = baseNode->nodeId();

		OpcUaDataValue descriptionDataValue;
		result = client_->syncRead(nodeId, descriptionDataValue, Description);
		if (result == Success
				&& descriptionDataValue.statusCode() == Success
				&& descriptionDataValue.variant()->variantType() == OpcUaBuildInType_OpcUaLocalizedText)
		{
			baseNode->description(descriptionDataValue.variant()->variantSPtr<OpcUaLocalizedText>());
		}

		OpcUaDataValue writeMaskDataValue;
		result = client_->syncRead(nodeId, writeMaskDataValue, WriteMask);
		if (result == Success
				&& writeMaskDataValue.statusCode() == Success
				&& writeMaskDataValue.variant()->variantType() == OpcUaBuildInType_OpcUaUInt32)
		{
			baseNode->writeMask(writeMaskDataValue.variant()->variant<OpcUaUInt32>());
		}

		OpcUaDataValue userWriteMaskDataValue;
		result = client_->syncRead(nodeId, userWriteMaskDataValue, UserWriteMask);
		if (result == Success
				&& userWriteMaskDataValue.statusCode() == Success
				&& userWriteMaskDataValue.variant()->variantType() == OpcUaBuildInType_OpcUaUInt32)
		{
			baseNode->userWriteMask(userWriteMaskDataValue.variant()->variant<OpcUaUInt32>());
		}

		OpcUaDataValue dataValue;
		result = client_->syncRead(nodeId, dataValue, Value);
		if (result == Success && dataValue.statusCode() == Success)
		{
			baseNode->dataValue()->copyFrom(dataValue);
		}

		std::cout << "readAttributeFromServer finished" << std::endl;
	}

	void
	AttributeWidget::slotWrite(BaseNode* baseNode)
	{
		std::cout << "write to server" << std::endl;

		OpcUaNodeId nodeId = baseNode->nodeId();

		boost::posix_time::ptime ptime = boost::posix_time::second_clock::local_time();
		OpcUaDateTime timestamp;
		timestamp.dateTime(ptime);

		OpcUaDataValue dataValue;
		dataValue.variant()->copyFrom(*baseNode->dataValue()->variant());
		dataValue.sourceTimestamp(timestamp);
		dataValue.serverTimestamp(timestamp);

		if (client_->syncWrite(nodeId, dataValue) == Success)
		{
			nodeChange(baseNode);
		}

		std::cout << "write to server finished" << std::endl;
	}

	void
	AttributeWidget::nodeChange(BaseNode* baseNode)
	{
		readAttributesFromServer(baseNode);

		nodeIdWidget_->nodeChange(baseNode);
		nodeClassWidget_->nodeChange(baseNode);
		browseNameWidget_->nodeChange(baseNode);
		descriptionWidget_->nodeChange(baseNode);
		writeMaskWidget_->nodeChange(baseNode);
		userWriteMaskWidget_->nodeChange(baseNode);
		valueWidget_->nodeChange(baseNode);
	}

} /* namespace OpcUaClientModul */
