/*
   Copyright 2016-2019 Kai Huebl (kai@huebl-sgh.de)

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

#ifndef __OpcUaNodeSetModul_Library_h__
#define __OpcUaNodeSetModul_Library_h__

#include <QObject>
#include <QMainWindow>
#include <QIcon>

#include "OpcUaGui/ModulInterface/ModulLibraryInterface.h"
#include "OpcUaClientModul/Base/OpcUaClient.h"
#include "OpcUaClientModul/Dialog/ConnectionDialog.h"
#include "OpcUaClientModul/ModulMainWindow/ModulMainWindow.h"
#include "OpcUaClientModul/ModulMonitorWindow/MonitorItemWindow.h"

namespace OpcUaClientModul
{

	class MYSHAREDLIB_EXPORT Library
	: public OpcUaGui::ModulLibraryInterface
	{
	  Q_OBJECT

	  public:
		Library(void);
		virtual ~Library(void);

		//- ModulInterface ----------------------------------------------------
		virtual QIcon* libModulIcon(void);
		virtual std::string getFileExtension(void);
		virtual void libStartup(void);
		virtual void libShutdown(void);

		virtual bool projectNew(uint32_t handle, const std::string& projectName, const std::string& projectFile);
		virtual bool projectOpen(uint32_t handle, const std::string& projectName, const std::string& projectFile);
		virtual bool projectSave(uint32_t handle);
		virtual bool projectSaveAs(uint32_t handle, const std::string& projectFile);
		virtual bool projectRename(uint32_t handle, const std::string& projectName);
		virtual bool projectReadyToClose(uint32_t handle);
		virtual bool projectClose(uint32_t handle);
		//- ModulInterface ----------------------------------------------------

	  private:
		OpcUaClient* client_;

		ModulMainWindow* modulMainWindow_;
		MonitorItemWindow* monitorItemWindow_;
	};

	class MYSHAREDLIB_EXPORT xxxx
	: public QObject
	{
		Q_OBJECT

	  public:
		xxxx(void) {}
		virtual ~xxxx(void) {}

      public slots:
        void startupLibrary(void) {}
        void shutdownLibrary(void) {}

      signals:

	};

}

#endif
