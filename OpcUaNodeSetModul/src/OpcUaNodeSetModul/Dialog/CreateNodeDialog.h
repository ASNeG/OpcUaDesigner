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
#include "OpcUaNodeSetModul/OpcUaWidget/NodeClassWidget.h"
#include "OpcUaNodeSetModul/OpcUaWidget/NodeIdWidget.h"
#include "OpcUaNodeSetModul/OpcUaWidget/BrowseNameWidget.h"
#include "OpcUaNodeSetModul/OpcUaWidget/DisplayNameWidget.h"
#include "OpcUaNodeSetModul/OpcUaWidget/ObjectTypeWidget.h"
#include "OpcUaNodeSetModul/OpcUaWidget/VariableTypeWidget.h"
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
	    void onValueChangedClass(NodeClassType& nodeClassType, bool isValid);
	    void onClickedObjectType(void);
	    void onClickedVariableType(void);
	    void onValueChangedNodeId(OpcUaNodeId& nodeId, bool isValid);
	    void onValueChangedDisplayName(OpcUaLocalizedText& displayName, bool isValid);
	    void onValueChangedBrowseName(OpcUaQualifiedName& browseName, bool isValid);

      signals:

	  private:
        void createLayout(void);
        QWidget* createEmptyWidget(void);
        QWidget* createObjectWidget(void);
        QWidget* createValueWidget(void);
        void createAttributes(const std::string& prefix);

        bool checkValue(void);

        //
        // data model
        //
        bool isValid_;
        DataModel* dataModel_;
        BaseNodeClass::SPtr baseNode_;

        NodeClassType nodeClassType_;
        OpcUaNodeId nodeId_;
        OpcUaLocalizedText displayName_;
        OpcUaQualifiedName browseName_;

        //
        // widgets
        //
        NodeClassWidget* nodeClassWidget_;
        NodeIdWidget* nodeIdWidget_;
        DisplayNameWidget* displayNameWidget_;
        BrowseNameWidget* browseNameWidget_;

        QStackedWidget* stackedWidget_;
        ObjectTypeWidget* objectTypeWidget_;
        VariableTypeWidget* variableTypeWidget_;
	};

}

#endif
