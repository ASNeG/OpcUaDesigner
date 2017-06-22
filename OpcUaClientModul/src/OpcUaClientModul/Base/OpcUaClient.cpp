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

#include "OpcUaClientModul/Base/OpcUaClient.h"

using namespace OpcUaStackClient;

namespace OpcUaClientModul
{
	OpcUaClient::OpcUaClient()
	: QWidget()
	, client_()
	, sessionName_("")
	, endpointUrl_("")
	, subscriptionId_(0)
	{
		qRegisterMetaType<OpcUaUInt32>("OpcUaUInt32");
		qRegisterMetaType<OpcUaDataValue>("OpcUaDataValue&");
	}

	OpcUaClient::~OpcUaClient()
	{
	}

	bool
	OpcUaClient::connectToServer(void)
	{
	    OpcUaStatusCode statusCode;
	    ConnectContext connectContext;

	    //
	    // connect to the opc ua server
	    //
	    connectContext.endpointUrl_ = endpointUrl_;
	    connectContext.sessionName_ = sessionName_;
	    statusCode = client_.syncConnect(connectContext);
	    if (statusCode != Success) {
	        std::cout << std::endl << "**** connect to opc ua server error ****" << statusCode << std::endl;
	        return false;
	    }

	    statusCode = syncCreateSubscription();
	    if (statusCode != Success)
	    {
	    	std::cout << std::endl << "**** connect to opc ua server error ****" << statusCode << std::endl;
	    	return false;
	    }

	    std::cout << std::endl << "**** connect to opc ua server success ****" << std::endl;
	    return true;
	}

	bool
	OpcUaClient::disconnectFromServer(void)
	{
	    OpcUaStatusCode statusCode;

	    //
	    // diconnect from the opc ua server
	    //
	    statusCode = client_.syncDisconnect();
	    if (statusCode != Success) {
	        std::cout << std::endl << "**** disconnect from opc ua server error ****" << statusCode << std::endl;
		return false;
	    }

	    std::cout << std::endl << "**** disconnect from opc ua server success ****" << std::endl;
	    return true;
	}

	OpcUaStatusCode
	OpcUaClient::syncBrowse(OpcUaNodeId::SPtr& nodeId, ReferenceDescriptionArray::SPtr& references)
	{
		return client_.syncViewServiceBrowse(nodeId, references);
	}

	OpcUaStatusCode
	OpcUaClient::syncRead(OpcUaNodeId& nodeId, OpcUaDataValue& dataValue, AttributeId attributeId)
	{
		std::cout << "read" << std::endl;

		ReadContext readContext;
		readContext.attributeId_ = attributeId;
		return client_.syncRead(nodeId, dataValue, readContext);
	}

	OpcUaStatusCode
	OpcUaClient::syncWrite(OpcUaNodeId& nodeId, OpcUaDataValue& dataValue)
	{
		return client_.syncWrite(nodeId, dataValue);
	}

	OpcUaStatusCode
	OpcUaClient::syncCreateSubscription(void)
	{
		// set data change callback
		client_.setDataChangeCallback(
			boost::bind(&OpcUaClient::dataChangeCallback, this, _1, _2)
		);

		// create subscription
		return client_.syncCreateSubscription(subscriptionId_);
	}

	void
	OpcUaClient::dataChangeCallback(OpcUaUInt32 clientHandle, OpcUaDataValue& dataValue)
	{
		std::cout << "dataChangeCallback " << clientHandle << std::endl;
		emit signalUpdateMonitoredItem(clientHandle, dataValue);
	}

	OpcUaStatusCode
	OpcUaClient::syncCreateMonitorItem(OpcUaNodeId& nodeId, uint32_t clientHandle, uint32_t& monitoredItemId)
	{
		return client_.syncCreateMonitoredItem(nodeId, subscriptionId_, clientHandle, monitoredItemId);
	}

	OpcUaStatusCode
	OpcUaClient::syncDeleteMonitorItem(uint32_t monitoredItemId)
	{
		return client_.syncDeleteMonitoredItem(subscriptionId_, monitoredItemId);
	}

	void
	OpcUaClient::sessionName(std::string& sessionName)
	{
		sessionName_ = sessionName;
	}

	std::string
	OpcUaClient::sessionName(void)
	{
		return sessionName_;
	}

	void
	OpcUaClient::endpointUrl(std::string& endpointURL)
	{
		endpointUrl_ = endpointURL;
	}

	std::string
	OpcUaClient::endpointUrl(void)
	{
		return endpointUrl_;
	}

}
