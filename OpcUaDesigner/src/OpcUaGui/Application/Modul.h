/*
   Copyright 2016-2017 Kai Huebl (kai@huebl-sgh.de)

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

#include <QObject>
#include <QApplication>
#include <QMainWindow>

#include "OpcUaGui/ModulInterface/ModulLibraryInterface.h"

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
		std::string modulName_;			// name of the modul
		std::string modulLibrary_;		// name of the modul library
		ModulParents modulParents_;		// list of modul parents

		// runtime parameter
		DynamicLibrary* dynamicLibrary_;
		ModulLibraryInterface* modulLibraryInterface_;
		ModulChilds modulChilds_;

		OpcUaStackCore::Config* config_;
	};


	class Modul
    : public QObject
	{

		Q_OBJECT

	  public:
		typedef std::vector<std::string> ModulNames;

		Modul(void);
		virtual ~Modul(void);

		void modulDirectory(const std::string& modulDirectory);

		void mainWindow(QMainWindow* mainWindow);
		QMainWindow* mainWindow(void);
		ModulConfig::Map& modulConfigMap(void);
		ModulNames& moduleNames(void);
		ModulConfig::SPtr getModulConfig(const std::string& modulName);

		bool startup(void);
		bool shutdown(void);

	  signals:
	    void startupSignal(void);
	    void shutdownSignal(void);

	  private:
		bool initModuls(void);
		bool readModulConfig(const std::string& modulDirectory);
		bool parseModulConfig(const std::string& modulConfigFileName, ModulConfig::SPtr& modulConfig);
		bool loadModul(void);
		void addRootModul(void);
		bool addModulChilds(void);

		ModulConfig::Map modulConfigMap_;
		ModulNames modulNames_;
		std::string modulDirectory_;
		QMainWindow* mainWindow_;
	};

}

#endif
