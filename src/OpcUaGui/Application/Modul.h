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

#ifndef __OpcUaGui_Modul_h__
#define __OpcUaGui_Modul_h__

#include <boost/shared_ptr.hpp>
#include <set>
#include <string>

namespace OpcUaStackCore
{
    class Config;
}

namespace OpcUaGui
{

	class ModulConfig
	{
	  public:
		typedef boost::shared_ptr<ModulConfig> SPtr;
		typedef std::set<ModulConfig::SPtr> Set;

		std::string modulName_;
		std::string modulLibrary_;
	};


	class Modul
	{
	  public:
		Modul(void);
		virtual ~Modul(void);

		ModulConfig::Set& modulConfigSet(void);

		bool initModuls(const std::string& modulDirectory);

	  private:
		bool readModulConfig(const std::string& modulDirectory);

		ModulConfig::Set modulConfigSet_;
	};

}

#endif
