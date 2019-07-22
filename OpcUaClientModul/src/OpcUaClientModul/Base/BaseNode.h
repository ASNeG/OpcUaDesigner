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

#ifndef __OpcUaClientModul_BaseNode_h__
#define __OpcUaClientModul_BaseNode_h__

#include <QMetaType>

#include "OpcUaStackCore/StandardDataTypes/NodeClass.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/ServiceSet/ReferenceDescription.h"

using namespace OpcUaStackCore;

namespace OpcUaClientModul
{

	class BaseNode
	{
	  public:
		BaseNode();
		BaseNode(ReferenceDescription::SPtr refDescription);
		virtual ~BaseNode();

		void expandedNodeId(const OpcUaExpandedNodeId::SPtr nodeId);
		void nodeId(OpcUaNodeId& nodeId);
		OpcUaNodeId& nodeId(void);
		OpcUaNodeId::SPtr nodeIdSPtr(void);

		void browseName(const OpcUaQualifiedName& browseName);
		OpcUaQualifiedName& browseName(void);

		void displayName(const OpcUaLocalizedText& displayName);
		OpcUaLocalizedText& displayName(void);

		void nodeClass(const NodeClass::Enum nodeClass);
		NodeClass::Enum nodeClass(void);

		void typeDefinition(const OpcUaExpandedNodeId::SPtr typeDefinition);
		OpcUaExpandedNodeId::SPtr typeDefinition(void) const;

		void description(OpcUaLocalizedText::SPtr description);
		OpcUaLocalizedText::SPtr description(void);

		void writeMask(OpcUaUInt32 writeMask);
		OpcUaUInt32 writeMask(void);

		void userWriteMask(OpcUaUInt32 userMask);
		OpcUaUInt32 userWriteMask(void);

		void dataValue(OpcUaDataValue::SPtr opcUaDataValue);
		OpcUaDataValue::SPtr dataValue(void);

	  private:
		OpcUaNodeId nodeId_;
		OpcUaLocalizedText displayName_;
		OpcUaQualifiedName browseName_;
		NodeClass::Enum nodeClass_;
		OpcUaBuildInType nodeIdType_;
		OpcUaExpandedNodeId::SPtr typeDefinition_;

		OpcUaLocalizedText::SPtr description_;

		OpcUaUInt32 writeMask_;
		OpcUaUInt32 userMask_;

		OpcUaDataValue::SPtr opcUaDataValue_;
	};

} /* namespace OpcUaClientModul */

Q_DECLARE_METATYPE(OpcUaClientModul::BaseNode*);

#endif /* __OpcUaClientModul_BaseNode_h__ */
