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

#ifndef __OpcUaGui_MainWindow_h__
#define __OpcUaGui_MainWindow_h__

#include <QMainWindow>

class QAction;
class QMenu;


namespace OpcUaGui
{

	class ProjectWindow;
	class Application;
	class Modul;

	class MainWindow
	: public QMainWindow
	{
	    Q_OBJECT

	  public:
		MainWindow(void);
		virtual ~MainWindow(void);

		bool startup(int argc, char**argv);
		bool shutdown(void);

	  protected:
		void closeEvent(QCloseEvent* event);

	  private slots:
	  	//
	    // window slots
	    //
	    void projectUpdate(void);

	    //
	    // project actions
	    //
	    void newProjectAction(void);
	    void openProjectAction(void);
	    void saveProjectAction(void);
	    void saveAsProjectAction(void);

	    //
	    // application actions
	    //
	    void exitApplAction(void);
	    void aboutApplAction(void);

	  private:
		void createActions(void);
		void createMenus(void);
		void addModulMenus(void);
		void createToolBars(void);
		void createStatusBar(void);

		//
		// application
		//
		Application* application_;
		Modul* modul_;

		//
		// Menu
		//
		QMenu* projectMenu_;
		QMenu* modulMenu_;
		QMenu* helpMenu_;

		//
		// toolbar
		//
		QToolBar* projectToolBar_;

		//
		// project actions
		//
		QAction* newProjectAction_;
		QAction* openProjectAction_;
		QAction* saveProjectAction_;
		QAction* saveAsProjectAction_;

		//
		// application actions
		//
		QAction* exitApplAction_;
		QAction* aboutApplAction_;
		QAction* aboutQtApplAction_;

		//
		// project window
		//
		ProjectWindow* projectWindow_;
	};

}

#endif
