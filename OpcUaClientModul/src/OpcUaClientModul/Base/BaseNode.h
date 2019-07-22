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
        Kai Huebl (kai@huebl-sgh.de)
 */

#ifndef __OpcUaClientModul_BaseNode_h__
#define __OpcUaClientModul_BaseNode_h__

#include <QMetaType>

#include "OpcUaStackCore/StandardDataTypes/NodeClass.h"
#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"
#include "OpcUaStackCore/ServiceSet/ReferenceDescription.h"

namespace OpcUaClientModul
{

	class BaseNode
	{
	  public:
		BaseNode();
		BaseNode(OpcUaStackCore::ReferenceDescription::SPtr refDescription);
		virtual ~BaseNode();

		void expandedNodeId(const OpcUaStackCore::OpcUaExpandedNodeId::SPtr nodeId);
		void nodeId(OpcUaStackCore::OpcUaNodeId& nodeId);
		OpcUaStackCore::OpcUaNodeId& nodeId(void);
		OpcUaStackCore::OpcUaNodeId::SPtr nodeIdSPtr(void);

		void browseName(const OpcUaStackCore::OpcUaQualifiedName& browseName);
		OpcUaStackCore::OpcUaQualifiedName& browseName(void);

		void displayName(const OpcUaStackCore::OpcUaLocalizedText& displayName);
		OpcUaStackCore::OpcUaLocalizedText& displayName(void);

		void nodeClass(const OpcUaStackCore::NodeClass::Enum nodeClass);
		OpcUaStackCore::NodeClass::Enum nodeClass(void);

		void typeDefinition(const OpcUaStackCore::OpcUaExpandedNodeId::SPtr typeDefinition);
		OpcUaStackCore::OpcUaExpandedNodeId::SPtr typeDefinition(void) const;

		void description(OpcUaStackCore::OpcUaLocalizedText::SPtr description);
		OpcUaStackCore::OpcUaLocalizedText::SPtr description(void);

		void writeMask(OpcUaStackCore::OpcUaUInt32 writeMask);
		OpcUaStackCore::OpcUaUInt32 writeMask(void);

		void userWriteMask(OpcUaStackCore::OpcUaUInt32 userMask);
		OpcUaStackCore::OpcUaUInt32 userWriteMask(void);

		void dataValue(OpcUaStackCore::OpcUaDataValue::SPtr opcUaDataValue);
		OpcUaStackCore::OpcUaDataValue::SPtr dataValue(void);

	  private:
		OpcUaStackCore::OpcUaNodeId nodeId_;
		OpcUaStackCore::OpcUaLocalizedText displayName_;
		OpcUaStackCore::OpcUaQualifiedName browseName_;
		OpcUaStackCore::NodeClass::Enum nodeClass_;
		OpcUaStackCore::OpcUaBuildInType nodeIdType_;
		OpcUaStackCore::OpcUaExpandedNodeId::SPtr typeDefinition_;

		OpcUaStackCore::OpcUaLocalizedText::SPtr description_;

		OpcUaStackCore::OpcUaUInt32 writeMask_;
		OpcUaStackCore::OpcUaUInt32 userMask_;

		OpcUaStackCore::OpcUaDataValue::SPtr opcUaDataValue_;
	};

} /* namespace OpcUaClientModul */

Q_DECLARE_METATYPE(OpcUaClientModul::BaseNode*);

#endif /* __OpcUaClientModul_BaseNode_h__ */
