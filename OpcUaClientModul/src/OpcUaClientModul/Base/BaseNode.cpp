/*
 Copyright 2016-2019 Samuel Huebl (samuel@huebl-sgh.de)

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

#include <OpcUaClientModul/Base/BaseNode.h>

using namespace OpcUaStackCore;

namespace OpcUaClientModul
{

	BaseNode::BaseNode()
	: typeDefinition_(constructSPtr<OpcUaExpandedNodeId>())
	, opcUaDataValue_(constructSPtr<OpcUaDataValue>())
	, nodeId_()
    , browseName_()
	, displayName_()
	, description_(constructSPtr<OpcUaLocalizedText>())
	, writeMask_((OpcUaUInt32) 0)
	, userMask_((OpcUaUInt32) 0)
	, nodeIdType_(OpcUaBuildInType_Unknown)
	, nodeClass_(NodeClass::EnumUnspecified)
	{
	}

	BaseNode::BaseNode(ReferenceDescription::SPtr refDescription)
	: opcUaDataValue_(constructSPtr<OpcUaDataValue>())
	, description_(constructSPtr<OpcUaLocalizedText>())
	, writeMask_((OpcUaUInt32) 0)
	, userMask_((OpcUaUInt32) 0)
	, nodeIdType_(OpcUaBuildInType_Unknown)
	{
		expandedNodeId(refDescription->expandedNodeId());
		typeDefinition_ = refDescription->typeDefinition();
		browseName_ = refDescription->browseName();
		displayName_ = refDescription->displayName();
		nodeClass_ = refDescription->nodeClass();
	}

	BaseNode::~BaseNode()
	{
	}

	void
	BaseNode::expandedNodeId(const OpcUaExpandedNodeId::SPtr expandedNodeId)
	{
		nodeId_.nodeIdValue(expandedNodeId->nodeIdValue());
		nodeId_.namespaceIndex(expandedNodeId->namespaceIndex());
		nodeIdType_ = expandedNodeId->nodeIdType();
	}

	void
	BaseNode::nodeId(OpcUaNodeId& nodeId)
	{
		nodeId_ = nodeId;
	}

	OpcUaNodeId&
	BaseNode::nodeId(void)
	{
		return nodeId_;
	}

	OpcUaNodeId::SPtr
	BaseNode::nodeIdSPtr(void)
	{
		OpcUaNodeId::SPtr nodeIdSPtr = constructSPtr<OpcUaNodeId>();
		nodeIdSPtr->copyFrom(nodeId_);
		return nodeIdSPtr;
	}

	void
	BaseNode::browseName(const OpcUaQualifiedName& browseName)
	{
		browseName_ = browseName;
	}

	OpcUaQualifiedName&
	BaseNode::browseName(void)
	{
		return browseName_;
	}

	void
	BaseNode::displayName(const OpcUaLocalizedText& displayName)
	{
		displayName_ = displayName;
	}

	OpcUaLocalizedText&
	BaseNode::displayName(void)
	{
		return displayName_;
	}

	void
	BaseNode::nodeClass(const NodeClass::Enum nodeClass)
	{
		nodeClass_ = nodeClass;
	}

	NodeClass::Enum
	BaseNode::nodeClass(void)
	{
		return nodeClass_;
	}

	void
	BaseNode::typeDefinition(const OpcUaExpandedNodeId::SPtr typeDefinition)
	{
		typeDefinition_ = typeDefinition;
	}

	OpcUaExpandedNodeId::SPtr
	BaseNode::typeDefinition(void) const
	{
		return typeDefinition_;
	}

	void
	BaseNode::description(OpcUaLocalizedText::SPtr description)
	{
		description_ = description;
	}

	OpcUaLocalizedText::SPtr
	BaseNode::description(void)
	{
		return description_;
	}

	void
	BaseNode::writeMask(OpcUaUInt32 writeMask)
	{
		writeMask_ = writeMask;
	}

	OpcUaUInt32
	BaseNode::writeMask(void)
	{
		return writeMask_;
	}

	void
	BaseNode::userWriteMask(OpcUaUInt32 userMask)
	{
		userMask_ = userMask;
	}

	OpcUaUInt32
	BaseNode::userWriteMask(void)
	{
		return userMask_;
	}

	void
	BaseNode::dataValue(OpcUaDataValue::SPtr opcUaDataValue)
	{
		opcUaDataValue_ = opcUaDataValue;
	}

	OpcUaDataValue::SPtr
	BaseNode::dataValue(void)
	{
		return opcUaDataValue_;
	}

} /* namespace OpcUaClientModul */
