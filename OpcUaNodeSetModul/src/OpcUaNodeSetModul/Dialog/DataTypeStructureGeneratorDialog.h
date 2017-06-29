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

#ifndef __BHIMatlabSimulink_DataTypeStructureGeneratorDialog_h__
#define __BHIMatlabSimulink_DataTypeStructureGeneratorDialog_h__

#include <QDialog>
#include <QWidget>
#include "OpcUaNodeSetModul/Model/DataModel.h"

class QListWidget;
class QPushButton;

namespace OpcUaNodeSet
{

	class DataTypeStructureGeneratorDialog
	: public QDialog
	{
		Q_OBJECT

	  public:
		DataTypeStructureGeneratorDialog(DataModel* dataModel);
		virtual ~DataTypeStructureGeneratorDialog(void);

	  public slots:
	    //
	    // dialog slots
	    //
	    void onRightAction(void);
	    void onLeftAction(void);
	    void onExitAction(void);
	    void onDataTypeStructureGeneratorAction(void);

      signals:

	  private:
    	void fillList(void);
    	void enableDataTypeStructureGeneratorButton(void);

        DataModel* dataModel_;

        //
         // widgets
         //
         QPushButton* saveButton_;
         QListWidget* in_;
         QListWidget* out_;

	};

}

#endif
