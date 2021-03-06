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

#ifndef __OpcUaClientModul_OpcUaClientProvider_h__
#define __OpcUaClientModul_OpcUaClientProvider_h__

#include <QWidget>

#include "OpcUaStackClient/ValueBasedInterface/VBIClient.h"

namespace OpcUaClientModul
{

	enum AttributeId
	{
		NodeId = 1,
		NodeClass = 2,
		BrowseName = 3,
		DisplayName = 4,
		Description = 5,
		WriteMask = 6,
		UserWriteMask = 7,
		IsAbstract = 8,
		Symmetric = 9,
		InverseName = 10,
		ContainsNoLoops = 11,
		EventNotifier = 12,
		Value = 13,
		DataType = 14,
		ValueRank = 15,
		ArrayDimensions = 16,
		AccessLevel = 17,
		UserAccessLevel = 18,
		MinimumSamplingInterval = 19,
		Historizing = 20,
		Executable = 21,
		UserExecutable = 22
	};

	class OpcUaClient
	: public QWidget
	{
		Q_OBJECT

	  public:
		OpcUaClient();
		virtual ~OpcUaClient();

		bool connectToServer(void);
		bool disconnectFromServer(void);

		OpcUaStackCore::OpcUaStatusCode syncBrowse(
			OpcUaStackCore::OpcUaNodeId::SPtr& nodeId,
			OpcUaStackCore::ReferenceDescriptionArray::SPtr& references
		);
		OpcUaStackCore::OpcUaStatusCode syncRead(
			OpcUaStackCore::OpcUaNodeId& nodeId,
			OpcUaStackCore::OpcUaDataValue& dataValue,
			AttributeId attributeId
		);
		OpcUaStackCore::OpcUaStatusCode syncWrite(
			OpcUaStackCore::OpcUaNodeId& nodeId,
			OpcUaStackCore::OpcUaDataValue&  dataValue
		);

		OpcUaStackCore::OpcUaStatusCode syncCreateSubscription(void);

		OpcUaStackCore::OpcUaStatusCode syncCreateMonitorItem(
			OpcUaStackCore::OpcUaNodeId& nodeId,
			uint32_t clientHandle,
			uint32_t& monitoredItemId
		);
		OpcUaStackCore::OpcUaStatusCode syncDeleteMonitorItem(
			uint32_t monitoredItemId
		);

		void sessionName(std::string& sessionName);
		std::string sessionName(void);
		void endpointUrl(std::string& endpointURL);
		std::string endpointUrl(void);

	  signals:
		void signalUpdateMonitoredItem(
			OpcUaStackCore::OpcUaUInt32 clientHandle,
			OpcUaStackCore::OpcUaDataValue& dataValue
		);

	  private:
		std::string sessionName_;
		std::string endpointUrl_;

		uint32_t subscriptionId_;

		VBIClient client_;
	};
}

#endif /* __OpcUaClientModul_OpcUaClientProvider_h__ */
