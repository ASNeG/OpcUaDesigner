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

#ifndef __BHIMatlabSimulink_NamespaceManagerDialog_h__
#define __BHIMatlabSimulink_NamespaceManagerDialog_h__

#include <QDialog>
#include <QWidget>
#include <QToolBar>
#include <QAction>
#include "OpcUaNodeSetModul/Model/DataModel.h"

class QTableWidget;
class QTableWidgetItem;

namespace OpcUaNodeSet
{

	class NamespaceManagerDialog
	: public QDialog
	{
		Q_OBJECT

	  public:
		NamespaceManagerDialog(DataModel* dataModel);
		virtual ~NamespaceManagerDialog(void);

	  public slots:
	  	void onAddRowAction(void);
	  	void onDeleteRowAction(void);
	    void onCellChanged(int row, int column);
	    void onCurrentItemChanged(QTableWidgetItem* newItem, QTableWidgetItem* oldItem);

      signals:

	  private:
      	//
        // private functions
        //
      	void createTableActions(void);
        void writeHeader(void);
        void writeData(void);
        void addRow(uint32_t row);
        void deleteRow(uint32_t row);

		//
		// table action
		//
		QAction* addRowAction_;
		QAction* deleteRowAction_;

     	//
      	// widgets
      	//
		QToolBar* tableToolBar_;

		uint16_t maxNamespaceIndex_;
		std::vector<std::string> namespaceVec_;
        DataModel* dataModel_;

        QTableWidget* namespaceTable_;

	};

}

#endif
