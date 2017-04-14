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

#include <OpcUaClientModul/ModulWindow/OpcUaClientApp.h>

using namespace OpcUaStackClient;

namespace OpcUaClientModul
{
	OpcUaClientApp::OpcUaClientApp()
	: client_()
	, sessionName_("")
	, endpointUrl_("")
	{
	}

	OpcUaClientApp::~OpcUaClientApp()
	{
	}

	void
	OpcUaClientApp::test()
	{
		// set endpointUrl and sessionName
		std::string endpointUrlStr = "opc.tcp://127.0.0.1:8889";
		endpointUrl(endpointUrlStr);
		std::string sessionNameStr = "urn:127.0.0.1:ASNeG.de:DesignerClient";
		sessionName(sessionNameStr);

		// connect to server
		if (!connectToServer())
		{
			return;
		}


		// disconnect from server
		disconnectFromServer();
	}

	bool
	OpcUaClientApp::connectToServer(void)
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
	        std::cout << std::endl << "**** connect to opc ua server error ****" << std::endl;
	        return false;
	    }

	    std::cout << std::endl << "**** connect to opc ua server success ****" << std::endl;
	    return true;
	}

	bool
	OpcUaClientApp::disconnectFromServer(void)
	{
	    OpcUaStatusCode statusCode;

	    //
	    // diconnect from the opc ua server
	    //
	    statusCode = client_.syncDisconnect();
	    if (statusCode != Success) {
	        std::cout << std::endl << "**** disconnect from opc ua server error ****" << std::endl;
		return false;
	    }

	    std::cout << std::endl << "**** disconnect from opc ua server success ****" << std::endl;
	    return true;
	}

	void
	OpcUaClientApp::sessionName(std::string& sessionName)
	{
		sessionName_ = sessionName;
	}

	std::string
	OpcUaClientApp::sessionName(void)
	{
		return sessionName_;
	}

	void
	OpcUaClientApp::endpointUrl(std::string& endpointURL)
	{
		endpointUrl_ = endpointURL;
	}

	std::string
	OpcUaClientApp::endpointUrl(void)
	{
		return endpointUrl_;
	}

}
