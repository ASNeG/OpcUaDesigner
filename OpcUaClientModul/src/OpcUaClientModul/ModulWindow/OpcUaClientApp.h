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

#ifndef __OpcUaClientModul_OpcUaClientApp_h__
#define __OpcUaClientModul_OpcUaClientApp_h__

#include "OpcUaStackClient/ValueBasedInterface/VBIClient.h"

using namespace OpcUaStackClient;

namespace OpcUaClientModul
{

	class OpcUaClientApp
	{
	  public:
		OpcUaClientApp();
		virtual ~OpcUaClientApp();

		void test(void);

		void sessionName(std::string& sessionName);
		std::string sessionName(void);
		void endpointUrl(std::string& endpointURL);
		std::string endpointUrl(void);

	  private:
		std::string sessionName_;
		std::string endpointUrl_;

		VBIClient client_;

		bool connectToServer(void);
		bool disconnectFromServer(void);

	};
}

#endif /* __OpcUaClientModul_OpcUaClientApp_h__ */
