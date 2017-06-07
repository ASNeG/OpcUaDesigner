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

#ifndef __BHIMatlabSimulink_ImportDialog_h__
#define __BHIMatlabSimulink_ImportDialog_h__

#include <QDialog>
#include <QWidget>
#include "OpcUaNodeSetModul/Model/DataModel.h"

class QPushButton;
class QListWidget;

namespace OpcUaNodeSet
{

	class ImportDialog
	: public QDialog
	{
		Q_OBJECT

	  public:
		ImportDialog(DataModel* dataModel);
		virtual ~ImportDialog(void);

	  public slots:
	    //
	  	// context menu
	    //
	    void onCustomContextMenuRequested(const QPoint& pos);
	    void onRenameAction(void);

	    //
	    // dialog slots
	    //
	    void onRightAction(void);
	    void onLeftAction(void);
	    void onExitAction(void);
	    void onTakeOverAction(void);
	    void onImportAction(void);

      signals:

	  private:
        //
      	// data model
        //
        DataModel* dataModel_;

        //
        // widgets
        //
        QPushButton* importButton_;
        QListWidget* in_;
        QListWidget* out_;

	};

}

#endif
