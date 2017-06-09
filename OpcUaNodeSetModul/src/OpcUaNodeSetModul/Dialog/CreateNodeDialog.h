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

#ifndef __BHIMatlabSimulink_CreateNodeDialog_h__
#define __BHIMatlabSimulink_CreateNodeDialog_h__

#include <QDialog>
#include <QWidget>
#include "OpcUaNodeSetModul/Model/DataModel.h"

class QComboBox;
class QStackedWidget;
class QLayout;

namespace OpcUaNodeSet
{

	class CreateNodeDialog
	: public QDialog
	{
		Q_OBJECT

	  public:
		CreateNodeDialog(DataModel* dataModel, BaseNodeClass::SPtr& baseNode);
		virtual ~CreateNodeDialog(void);

	  public slots:
	    void onCurrentIndexChangedNodeClass(int index);
	    void onClickedObjectType(void);
	    void onClickedValueType(void);

      signals:

	  private:
        void createLayout(void);
        QWidget* createEmptyWidget(void);
        QWidget* createObjectWidget(void);
        QWidget* createValueWidget(void);
        void createUniqueNodeId(const std::string& prefix);
        void show(void);

        //
        // data model
        //
        DataModel* dataModel_;
        BaseNodeClass::SPtr baseNode_;
        OpcUaNodeId nodeId_;

        //
        // widgets
        //
        QStackedWidget* stackedWidget_;
	};

}

#endif
