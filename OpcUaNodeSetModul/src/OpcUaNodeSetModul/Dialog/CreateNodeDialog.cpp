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


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QLineEdit>
#include <QFrame>

#include "OpcUaNodeSetModul/Dialog/CreateNodeDialog.h"
#include "OpcUaNodeSetModul/Dialog/SelectObjectTypeDialog.h"
#include "OpcUaNodeSetModul/Dialog/SelectVariableTypeDialog.h"
#include "OpcUaNodeSetModul/OpcUaWidget/NodeClassWidget.h"
#include "OpcUaNodeSetModul/OpcUaWidget/NodeIdWidget.h"
#include "OpcUaNodeSetModul/OpcUaWidget/BrowseNameWidget.h"
#include "OpcUaNodeSetModul/OpcUaWidget/DisplayNameWidget.h"

namespace OpcUaNodeSet
{


	CreateNodeDialog::CreateNodeDialog(DataModel* dataModel, BaseNodeClass::SPtr& baseNode)
	: QDialog()
	, dataModel_(dataModel)
	, baseNode_(baseNode)
	, nodeId_()
	, displayName_()
	, browseName_()
	{
		createLayout();
	}

	CreateNodeDialog::~CreateNodeDialog(void)
	{
	}

	void
	CreateNodeDialog::createLayout(void)
	{
		createAttributes("Object");

		this->setWindowTitle(QString("Create Node Dialog"));
		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		//
		// base information section
		//
		QGridLayout* baseInfoLayout = new QGridLayout();
		vBoxLayout->addLayout(baseInfoLayout);

		// node class
		QLabel* nodeClassLabel = new QLabel("NodeClass");
		baseInfoLayout->addWidget(nodeClassLabel, 0, 0);

		QStringList nodeClassList;
		nodeClassList << "Object" << "Variable";
		NodeClassWidget* nodeClassWidget = new NodeClassWidget(nodeClassList);
		baseInfoLayout->addWidget(nodeClassWidget, 0, 1);

		// node id
		QLabel* nodeIdLabel = new QLabel("NodeId");
		baseInfoLayout->addWidget(nodeIdLabel, 1, 0);

		NodeIdWidget* nodeIdWidget = new NodeIdWidget();
		nodeIdWidget->setValue(dataModel_->informationModel());
		nodeIdWidget->setValue(dataModel_->nodeSetNamespace());
		nodeIdWidget->setValue(nodeId_);

		QHBoxLayout* hBoxLayoutInfo = new QHBoxLayout();
		hBoxLayoutInfo->addWidget(nodeIdWidget);
		hBoxLayoutInfo->addStretch();

		baseInfoLayout->addLayout(hBoxLayoutInfo, 1, 1);

		// display name
		QLabel* displayNameLabel = new QLabel("DisplayName");
		baseInfoLayout->addWidget(displayNameLabel, 2, 0);

		DisplayNameWidget* displayNameWidget = new DisplayNameWidget();
		baseInfoLayout->addWidget(displayNameWidget, 2, 1);
		displayNameWidget->setValue(displayName_);

		// browse name
		QLabel* browseNameLabel = new QLabel("BrowseName");
		baseInfoLayout->addWidget(browseNameLabel, 3, 0);

		BrowseNameWidget* browseNameWidget = new BrowseNameWidget();
		baseInfoLayout->addWidget(browseNameWidget, 3, 1);
		browseNameWidget->setValue(dataModel_->nodeSetNamespace());
		browseNameWidget->setValue(browseName_);

		//
		// diving line
		//
	    QFrame* line = new QFrame();
	    line->setFrameShape(QFrame::HLine);
	    line->setFrameShadow(QFrame::Sunken);
	    vBoxLayout->addWidget(line);

		//
		// type specific data
		//
		stackedWidget_ = new QStackedWidget();
		stackedWidget_->addWidget(createEmptyWidget());
		stackedWidget_->addWidget(createObjectWidget());
		stackedWidget_->addWidget(createValueWidget());
		stackedWidget_->setCurrentIndex(1);
		vBoxLayout->addWidget(stackedWidget_);

		//
		// dialog action button
		//
		QHBoxLayout* actionButtonLayout = new QHBoxLayout();
		QPushButton* cancelButton = new QPushButton("Cancel");
		actionButtonLayout->addWidget(cancelButton);
		QPushButton* okButton = new QPushButton("Ok");
		okButton->setEnabled(false);
		actionButtonLayout->addWidget(okButton);
		vBoxLayout->addLayout(actionButtonLayout);

		//
		// actions
		//
		connect(
			nodeClassWidget, SIGNAL(currentIndexChanged(int)),
			this, SLOT(onCurrentIndexChangedNodeClass(int))
		);

		show();
		setLayout(vBoxLayout);
	}

	QWidget*
    CreateNodeDialog::createEmptyWidget(void)
    {
    	QWidget* widget = new QWidget();
    	return widget;
    }

	QWidget*
    CreateNodeDialog::createObjectWidget(void)
    {
    	QWidget* widget = new QWidget();
       	QGridLayout* gridLayout = new QGridLayout();
       	gridLayout->setMargin(0);
       	widget->setLayout(gridLayout);

       	//
       	// object type
       	//
        QLabel* objectTypeLabel = new QLabel("Object Type   ");
        gridLayout->addWidget(objectTypeLabel, 0, 0);

        QHBoxLayout* objectTypeLayout = new QHBoxLayout();
        gridLayout->addLayout(objectTypeLayout, 0, 1);

        OpcUaNodeId objectTypeNodeId(58);
        objectTypeWidget_ = new ObjectTypeWidget();
        objectTypeWidget_->setValue(dataModel_->informationModel());
        objectTypeWidget_->setValue(objectTypeNodeId);
        objectTypeLayout->addWidget(objectTypeWidget_);

        //
        // action
        //
		connect(
			objectTypeWidget_, SIGNAL(selectObjectType()),
			this, SLOT(onClickedObjectType())
		);

    	return widget;
    }

	QWidget*
    CreateNodeDialog::createValueWidget(void)
    {
    	QWidget* widget = new QWidget();
       	QGridLayout* gridLayout = new QGridLayout();
       	gridLayout->setMargin(0);
        widget->setLayout(gridLayout);

       	//
       	// object type
       	//
        QLabel* valueTypeLabel = new QLabel("Value Type    ");
        gridLayout->addWidget(valueTypeLabel, 0, 0);

        QHBoxLayout* variableTypeLayout = new QHBoxLayout();
        gridLayout->addLayout(variableTypeLayout, 0, 1);

        OpcUaNodeId variableTypeNodeId(62);
        variableTypeWidget_ = new VariableTypeWidget();
        variableTypeWidget_->setValue(dataModel_->informationModel());
        variableTypeWidget_->setValue(variableTypeNodeId);
        variableTypeLayout->addWidget(variableTypeWidget_);

        //
        // action
        //
 		connect(
 				variableTypeWidget_, SIGNAL(selectObjectType()),
 			this, SLOT(onClickedVariableType())
 		);

    	return widget;
    }

	void
	CreateNodeDialog::createAttributes(const std::string& prefix)
	{
		if (dataModel_->actNamespaceIndex() == 0) {
			dataModel_->actNamespaceIndex(1);
		}

		uint32_t idx = 1;
		while (true)
		{
			std::stringstream ss;
			ss << prefix << idx;

			nodeId_.set(ss.str(), dataModel_->actNamespaceIndex());

			BaseNodeClass::SPtr baseNode = dataModel_->informationModel()->find(nodeId_);
			if (baseNode.get() == NULL) break;

			idx++;
		}

		displayName_.set("", prefix);

		browseName_.set(prefix, dataModel_->actNamespaceIndex());
	}

	void
	CreateNodeDialog::show(void)
	{
		;
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// dialog slots
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	CreateNodeDialog::onCurrentIndexChangedNodeClass(int index)
	{
		stackedWidget_->setCurrentIndex(index+1);
	}

	void
	CreateNodeDialog::onClickedObjectType(void)
	{
		createAttributes("Object");

		SelectObjectTypeDialog dialog(dataModel_);
		dialog.exec();

		objectTypeWidget_->setValue(dialog.objectType());
		show();
	}

	void
	CreateNodeDialog::onClickedVariableType(void)
	{
		createAttributes("Variable");

		SelectVariableTypeDialog dialog(dataModel_);
		dialog.exec();

		variableTypeWidget_->setValue(dialog.variableType());
		show();
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------

}


