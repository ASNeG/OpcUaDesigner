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
#include <map>
#include <string>

#include "OpcUaGui/ModulInterface/ModulInterface.h"

namespace OpcUaStackCore
{
    class Config;
}

namespace OpcUaGui
{

	class DynamicLibrary;

	class ModulConfig
	{
	  public:
		typedef std::vector<std::string> ModulParents;
		typedef std::vector<std::string> ModulChilds;
		typedef boost::shared_ptr<ModulConfig> SPtr;
		typedef std::map<std::string,ModulConfig::SPtr> Map;

		ModulConfig(void);
		~ModulConfig(void);

		void addChild(const std::string& modulName);

		// configuration parameter
		std::string modulName_;
		std::string modulLibrary_;
		ModulParents modulParents_;

		// runtime parameter
		DynamicLibrary* dynamicLibrary_;
		ModulInterface* modulInterface_;
		ModulChilds modulChilds_;
	};


	class Modul
	{
	  public:
		typedef std::vector<std::string> ModulNames;

		Modul(void);
		virtual ~Modul(void);

		ModulConfig::Map& modulConfigMap(void);
		ModulNames& moduleNames(void);

		bool initModuls(const std::string& modulDirectory);

	  private:
		bool readModulConfig(const std::string& modulDirectory);
		bool parseModulConfig(const std::string& modulConfigFileName, ModulConfig::SPtr& modulConfig);
		bool loadModul(void);
		bool addModulChilds(void);

		ModulConfig::Map modulConfigMap_;
		ModulNames modulNames_;
	};

}

#endif
