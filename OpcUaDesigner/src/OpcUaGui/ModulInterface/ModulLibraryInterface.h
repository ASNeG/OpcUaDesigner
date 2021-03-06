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

#ifndef __OpcUaGui_ModulLibraryInterface_h__
#define __OpcUaGui_ModulLibraryInterface_h__

#include <QObject>
#include <QtCore/QtGlobal>
#include <QMainWindow>

#include <iostream>
#include <stdint.h>

#include "OpcUaStackCore/Base/Config.h"

using namespace OpcUaStackCore;

#if defined(MYSHAREDLIB_LIBRARY)
#  define MYSHAREDLIB_EXPORT Q_DECL_EXPORT
#else
#  define MYSHAREDLIB_EXPORT Q_DECL_IMPORT
#endif

namespace OpcUaGui
{

	class MYSHAREDLIB_EXPORT ModulLibraryInterface
	: public QObject
	{
		Q_OBJECT

	  public:
		typedef enum {
			V_ModulName,
			V_ModulFile
		} Value;

		ModulLibraryInterface(void) {}
		virtual ~ModulLibraryInterface(void) {}

		void config(Config * config) { config_ = config; }
		Config* config(void) { return config_; }
		void parentMainWindow(QMainWindow* parentMainWindow) { parentMainWindow_ = parentMainWindow; }
		QMainWindow* parentMainWindow(void) { return parentMainWindow_; }

		virtual QIcon* libModulIcon(void) = 0;
		virtual std::string getFileExtension(void) = 0;
		virtual void libStartup(void) {}
		virtual void libShutdown(void) {}

		virtual bool projectNew(uint32_t handle, const std::string& projectName, const std::string& projectFile) = 0;
		virtual bool projectOpen(uint32_t handle, const std::string& projectName, const std::string& projectFile) = 0;
		virtual bool projectSave(uint32_t handle) = 0;
		virtual bool projectSaveAs(uint32_t handle, const std::string& projectFile) = 0;
		virtual bool projectRename(uint32_t handle, const std::string& projectName) = 0;
		virtual bool projectReadyToClose(uint32_t handle) = 0;
		virtual bool projectClose(uint32_t handle) = 0;

      public slots:
	    void startupLibrary(void) { libStartup(); }
	    void shutdownLibrary(void) { libShutdown(); }

      signals:
        void projectCloseSignal(uint32_t handle);
        void projectUpdateSignal(uint32_t handle);

      private:
        Config* config_ = nullptr;
        QMainWindow* parentMainWindow_ = nullptr;

	};

}

#endif
