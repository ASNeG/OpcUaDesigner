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

#ifndef __BHIMatlabSimulink_ArrayDimensionDialog_h__
#define __BHIMatlabSimulink_ArrayDimensionDialog_h__

#include <stdint.h>
#include <QDialog>
#include <QWidget>

#include "OpcUaStackCore/BuildInTypes/BuildInTypes.h"

class QListWidget;
class QListWidgetItem;
class QAction;

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{

	class ArrayDimensionDialog
	: public QDialog
	{
		Q_OBJECT

	  public:
		ArrayDimensionDialog(void);
		virtual ~ArrayDimensionDialog(void);

		bool ok(void);
		void setArrayDimensions(OpcUaUInt32Array::SPtr& arrayDimensions);
		void getArrayDimensions(OpcUaUInt32Array::SPtr& arrayDimensions);

	  public slots:
	    //
	  	// toolbar slots
	    //
	    void onAddAction(void);
	    void onDelAction(void);
	    void onUpAction(void);
	    void onDownAction(void);

	    //
	    // dialog slots
	    //
	    void onCancelAction(void);
	    void onOkAction(void);
	    void onItemActivatedAction(QListWidgetItem* item);
	    void onCurrentTextChanged(const QString& text);

      //signals:

	  private:
		void createToolBarActions(void);
		void enableButtons(void);
		uint32_t findItem(const std::string& itemName);

		bool ok_;

		std::string actValue_;
		uint32_t actRow_;
        QListWidget* propertyList_;

        //
        // toolbar actions
        //
        QAction* addAction_;
        QAction* delAction_;
        QAction* upAction_;
        QAction* downAction_;

	};

}

#endif
