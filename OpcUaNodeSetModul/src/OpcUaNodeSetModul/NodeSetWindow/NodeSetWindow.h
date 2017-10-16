/*
   Copyright 2017 Kai Huebl (kai@huebl-sgh.de)

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

#ifndef __OpcUaNodeSetModul_NodeSetWindow_h__
#define __OpcUaNodeSetModul_NodeSetWindow_h__

#include <QMainWindow>
#include <QCloseEvent>

#include <map>
#include <stdint.h>

#include "OpcUaStackCore/Core/Core.h"
#include "OpcUaNodeSetModul/Base/LibraryConfig.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaTreeWindow.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeWindow.h"
#include "OpcUaNodeSetModul/Model/DataModel.h"

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{

	class NodeSetWindow
    : public QMainWindow
	{

	  Q_OBJECT

	  public:
		typedef std::map<uint32_t, NodeSetWindow*> Map;

		NodeSetWindow(QMainWindow* parentMainWindow);
		virtual ~NodeSetWindow(void);

		void closeEvent(QCloseEvent* event);

		bool projectNew(uint32_t handle, const std::string& projectName, const std::string& projectFile);
	    bool projectOpen(uint32_t handle, const std::string& projectName, const std::string& projectFile);
		bool projectSave(uint32_t handle);
		bool projectSaveAs(uint32_t handle, const std::string& projectFile);
		bool projectRename(uint32_t handle, const std::string& projectName);
		bool projectReadyToClose(uint32_t handle);
		bool projectClose(uint32_t handle);

		void libraryConfig(LibraryConfig* libraryConfig);

	  public slots:
		void onUpdateTab(void);

	  private:
		bool createWindow(void);

		Core core_;
		DataModel dataModel_;

		LibraryConfig* libraryConfig_;
		QMainWindow* parentMainWindow_;
		std::string projectName_;
		std::string projectFile_;

		OpcUaTreeWindow* opcUaTreeWindow_;
		OpcUaAttributeWindow* opcUaAttributeWindow_;
	};

}

#endif
