/*
   Copyright 2016 Kai Huebl (kai@huebl-sgh.de)

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

#ifndef __OpcUaGui_Application_h__
#define __OpcUaGui_Application_h__

#include <string>

namespace OpcUaStackCore
{
    class Config;
    class FileLogger;
}

namespace OpcUaGui
{

	class Application
	{
	  public:
		Application(void);
		virtual ~Application(void);

		std::string errorString(void) const;
		OpcUaStackCore::Config* config(void);
		std::string libraryConfigPath(void) const;

		bool parseConfig(const std::string& configFile);
		bool initLogging(void);

	  private:
		std::string errorString_;
		OpcUaStackCore::Config* config_;
		OpcUaStackCore::FileLogger* fileLogger_;

		std::string libraryConfigPath_;
	};

}

#endif
