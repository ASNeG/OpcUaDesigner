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

#ifndef __BHIMatlabSimulink_SelectReferenceTypeDialog_h__
#define __BHIMatlabSimulink_SelectReferenceTypeDialog_h__

#include <QDialog>
#include <QWidget>
#include "OpcUaNodeSetModul/Model/DataModel.h"
#include "OpcUaStackServer/AddressSpaceModel/BaseNodeClass.h"
#include "OpcUaNodeSetModul/Base/NodeInfo.h"

class QTreeWidget;
class QTreeWidgetItem;

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{

	class SelectReferenceTypeDialog
	: public QDialog
	{
		Q_OBJECT

	  public:
		SelectReferenceTypeDialog(DataModel* dataModel);
		virtual ~SelectReferenceTypeDialog(void);

		OpcUaNodeId& referenceType(void);

	  public slots:
	    void onItemDoubleClicked(QTreeWidgetItem* item, int column);

      signals:

	  private:
        void showModel(void);
		void addNode(
			InformationModel::SPtr& informationModel,
			QTreeWidgetItem* parentItem,
			BaseNodeClass::SPtr& baseNode
		);

        //
        // data model
        //
        DataModel* dataModel_;
        OpcUaNodeId referenceType_;

        //
        // widgets
        //
		QTreeWidget* opcUaTree_;
		QTreeWidgetItem* rootItem_;
		QTreeWidgetItem* actItem_;
	};

}

#endif
