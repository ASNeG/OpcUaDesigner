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

#ifndef __OpcUaGui_ProjectWindow_h__
#define __OpcUaGui_ProjectWindow_h__

#include <QWidget>
#include <QMetaType>

class QTreeWidget;
class QTreeWidgetItem;

namespace OpcUaGui
{

    class Modul;

    class ModulInfo
    {
      public:
    	std::string modulName_;
    };

	class ProjectWindow
	: public QWidget
	{
		Q_OBJECT

	  public:
		ProjectWindow(QWidget* parent = 0);
		virtual ~ProjectWindow(void);

		void modul(Modul* modul);

      private slots:
        void onCustomContextMenuRequested(const QPoint& pos);

	  private:
		Modul* modul_;
		QTreeWidget* projectTree_;
		QTreeWidgetItem* rootItem_;
	};

}

Q_DECLARE_METATYPE(OpcUaGui::ModulInfo*);

#endif
