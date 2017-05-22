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

#ifndef __OpcUaGui_ProjectWindow_h__
#define __OpcUaGui_ProjectWindow_h__

#include <QWidget>
#include <QMetaType>
#include "OpcUaGui/Model/DataModel.h"

#include <stdint.h>

class QTreeWidget;
class QTreeWidgetItem;
class QMenu;
class QMainWindow;

namespace OpcUaGui
{

    class Modul;
    class ModulConfig;

    class NodeInfo
    {
      public:
    	NodeInfo(void);
    	~NodeInfo(void);

    	ModulConfig* modulConfig_;
    	std::string modulName_;
    	uint32_t handle_;
    	ApplicationData::SPtr applicationData_;
    };

	class ProjectWindow
	: public QWidget
	{
		Q_OBJECT

	  public:
		ProjectWindow(QWidget* parent = 0);
		virtual ~ProjectWindow(void);

		void modul(Modul* modul);
		bool dataModel(DataModel* dataModel);

      private slots:
        void onCustomContextMenuRequested(const QPoint& pos);
        void createNewMenu(QMenu& menu, ModulConfig* modulConfig);
        void createOpenMenu(QMenu& menu, ModulConfig* modulConfig);
        void createSaveMenu(QMenu& menu, NodeInfo* modulInfo);
        void createSaveAsMenu(QMenu& menu, NodeInfo* modulInfo);
        void createRenameMenu(QMenu& menu, NodeInfo* modulInfo);
        void createCloseMenu(QMenu& menu, NodeInfo* modulInfo);
        void createDeleteMenu(QMenu& menu, NodeInfo* modulInfo);
        void onItemDoubleClicked(QTreeWidgetItem* treeWidgetItem, int column);

        void projectNewAction(void);
        void projectOpenAction(void);
        void projectSaveAction(void);
        void projectSaveAsAction(void);
        void projectRenameAction(void);
        void projectCloseAction(void);
        void projectDeleteAction(void);

	  private:
        //
        // private functions
        //
        void showModel(void);

        uint32_t handle_;
		Modul* modul_;
		DataModel* dataModel_;
		QTreeWidget* projectTree_;
		QTreeWidgetItem* rootItem_;
		QTreeWidgetItem* actItem_;
	};

}

Q_DECLARE_METATYPE(OpcUaGui::NodeInfo*);

#endif
