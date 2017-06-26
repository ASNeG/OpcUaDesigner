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

#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaNodeSetModul/Dialog/CreateNodeDialog.h"
#include "OpcUaNodeSetModul/Dialog/SelectObjectTypeDialog.h"
#include "OpcUaNodeSetModul/Dialog/SelectVariableTypeDialog.h"
#include "OpcUaNodeSetModul/Dialog/SelectReferenceTypeDialog.h"

namespace OpcUaNodeSet
{


	CreateNodeDialog::CreateNodeDialog(DataModel* dataModel, BaseNodeClass::SPtr& baseNode)
	: QDialog()
	, dataModel_(dataModel)
	, baseNode_(baseNode)
	, nodeClassType_(NodeClassType_Object)
	, nodeId_()
	, displayName_()
	, browseName_()
	, isValid_(false)
	, isOk_(false)
	, nodeClassList_()
	, referenceTypeNodeId_(OpcUaId_Organizes)
	{
		createNodeClassList();
		createLayout();
	}

	CreateNodeDialog::~CreateNodeDialog(void)
	{
	}

	bool
	CreateNodeDialog::isOk(void)
	{
		return isOk_;
	}

	void
	CreateNodeDialog::getNodeClass(NodeClassType& nodeClassType)
	{
		nodeClassWidget_->getValue(nodeClassType);
	}

	void
	CreateNodeDialog::getNodeId(OpcUaNodeId& nodeId)
	{
		nodeIdWidget_->getValue(nodeId);
	}

	void
	CreateNodeDialog::getDisplayName(OpcUaLocalizedText& displayName)
	{
		displayNameWidget_->getValue(displayName);
	}

	void
	CreateNodeDialog::getBrowseName(OpcUaQualifiedName& browseName)
	{
		browseNameWidget_->getValue(browseName);
	}

	void
	CreateNodeDialog::getReferenceType(OpcUaNodeId& referenceType)
	{
		referenceTypeWidget_->getValue(referenceType);
	}

	void
	CreateNodeDialog::getObjectType(OpcUaNodeId& objectType)
	{
		objectTypeWidget_->getValue(objectType);
	}

	void
	CreateNodeDialog::getVariableType(OpcUaNodeId& variableType)
	{
		variableTypeWidget_->getValue(variableType);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	CreateNodeDialog::createNodeClassList(void)
	{
		//
		// get parent information
		//
		OpcUaNodeId parentNodeId;
		NodeClassType parentNodeClassType;
		baseNode_->getNodeId(parentNodeId);
		baseNode_->getNodeClass(parentNodeClassType);

		//
		// check whether object type is allowed
		//
		if (parentNodeClassType == NodeClassType_ObjectType) {
			nodeClassList_ << "ObjectType";
			nodeClassType_ = NodeClassType_ObjectType;
			referenceTypeNodeId_ = OpcUaId_HasSubtype;

			if (parentNodeId.namespaceIndex() != 0) {
				nodeClassList_ << "Object" << "Variable" << "Method";
			}
			return;
		}

		//
		// check wether variable type is allowed
		//
		if (parentNodeClassType == NodeClassType_VariableType) {
			nodeClassList_ << "VariableType";
			nodeClassType_ = NodeClassType_VariableType;
			referenceTypeNodeId_ = OpcUaId_HasSubtype;

			if (parentNodeId.namespaceIndex() != 0) {
				nodeClassList_ << "Object" << "Variable" << "Method";
			}
			return;
		}

		//
		// check wether data type is allowed
		//
		if (parentNodeClassType == NodeClassType_DataType) {
			nodeClassList_ << "DataType";
			nodeClassType_ = NodeClassType_DataType;
			referenceTypeNodeId_ = OpcUaId_HasSubtype;

			if (parentNodeId.namespaceIndex() != 0) {
				nodeClassList_ << "Object" << "Variable" << "Method";
			}
			return;
		}

		//
		// check wether reference type is allowed
		//
		if (parentNodeClassType == NodeClassType_ReferenceType) {
			nodeClassList_ << "ReferenceType";
			nodeClassType_ = NodeClassType_ReferenceType;
			referenceTypeNodeId_ = OpcUaId_HasSubtype;
			return;
		}

		nodeClassType_ = NodeClassType_Object;
		nodeClassList_ << "Object" << "Variable" << "Method";
		referenceTypeNodeId_ = OpcUaId_Organizes;
	}

	void
	CreateNodeDialog::createLayout(void)
	{
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

		nodeClassWidget_ = new NodeClassWidget(nodeClassList_);
		baseInfoLayout->addWidget(nodeClassWidget_, 0, 1);

		// node id
		QLabel* nodeIdLabel = new QLabel("NodeId");
		baseInfoLayout->addWidget(nodeIdLabel, 1, 0);

		nodeIdWidget_ = new NodeIdWidget();
		nodeIdWidget_->setValue(dataModel_->informationModel());
		nodeIdWidget_->setValue(dataModel_->nodeSetNamespace());

		QHBoxLayout* hBoxLayoutInfo = new QHBoxLayout();
		hBoxLayoutInfo->addWidget(nodeIdWidget_);
		hBoxLayoutInfo->addStretch();

		baseInfoLayout->addLayout(hBoxLayoutInfo, 1, 1);

		// display name
		QLabel* displayNameLabel = new QLabel("DisplayName");
		baseInfoLayout->addWidget(displayNameLabel, 2, 0);

		displayNameWidget_ = new DisplayNameWidget();
		baseInfoLayout->addWidget(displayNameWidget_, 2, 1);

		// browse name
		QLabel* browseNameLabel = new QLabel("BrowseName");
		baseInfoLayout->addWidget(browseNameLabel, 3, 0);

		browseNameWidget_ = new BrowseNameWidget();
		baseInfoLayout->addWidget(browseNameWidget_, 3, 1);
		browseNameWidget_->setValue(dataModel_->nodeSetNamespace());

		// reference type
		QLabel* referenceTypeLabel = new QLabel("Parent Ref");
		baseInfoLayout->addWidget(referenceTypeLabel, 4, 0);

		referenceTypeWidget_ = new ReferenceTypeWidget();
		referenceTypeWidget_->setValue(dataModel_->informationModel());
		referenceTypeWidget_->setValue(referenceTypeNodeId_);
		baseInfoLayout->addWidget(referenceTypeWidget_, 4, 1);
		browseNameWidget_->setValue(dataModel_->nodeSetNamespace());

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
		okButton_ = new QPushButton("Ok");
		okButton_->setEnabled(false);
		actionButtonLayout->addWidget(okButton_);
		vBoxLayout->addLayout(actionButtonLayout);

		//
		// actions
		//
		connect(
			nodeClassWidget_, SIGNAL(valueChanged(NodeClassType&, bool)),
			this, SLOT(onValueChangedClass(NodeClassType&, bool))
		);
		connect(
			nodeIdWidget_, SIGNAL(valueChanged(OpcUaNodeId&, bool)),
			this, SLOT(onValueChangedNodeId(OpcUaNodeId&, bool))
		);
		connect(
			displayNameWidget_, SIGNAL(valueChanged(OpcUaLocalizedText&, bool)),
			this, SLOT(onValueChangedDisplayName(OpcUaLocalizedText&, bool))
		);
		connect(
			browseNameWidget_, SIGNAL(valueChanged(OpcUaQualifiedName&, bool)),
			this, SLOT(onValueChangedBrowseName(OpcUaQualifiedName&, bool))
		);
		connect(
			referenceTypeWidget_, SIGNAL(selectReferenceType()),
			this, SLOT(onClickedReferenceType())
		);

		connect(
			okButton_, SIGNAL(clicked()),
			this, SLOT(onClickedOk())
		);
		connect(
			cancelButton, SIGNAL(clicked()),
			this, SLOT(onClickedCancel())
		);

		nodeClassWidget_->setValue(nodeClassType_);
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
 			variableTypeWidget_, SIGNAL(selectVariableType()),
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

	bool
	CreateNodeDialog::checkValue(void)
	{
		if (!nodeIdWidget_->isValid()) return false;
		if (!displayNameWidget_->isValid()) return false;
		if (!browseNameWidget_->isValid()) return false;
		if (!referenceTypeWidget_->isValid()) return false;

		NodeClassType nodeClassType;
		nodeClassWidget_->getValue(nodeClassType);
		if (nodeClassType == NodeClassType_Object) {
			if (!objectTypeWidget_->isValid()) return false;
		}
		else if (nodeClassType == NodeClassType_Variable){
			if (!variableTypeWidget_->isValid()) return false;
		}
		return true;
	}

	void
	CreateNodeDialog::controlButton(void)
	{
		if (isValid_) {
			okButton_->setEnabled(true);
		}
		else {
			okButton_->setEnabled(false);
		}
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// dialog slots
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	CreateNodeDialog::onValueChangedClass(NodeClassType& nodeClassType, bool isValid)
	{
		if (!isValid) return;

		switch (nodeClassType)
		{
			case NodeClassType_Object:
			{
				createAttributes("Object");
				stackedWidget_->setCurrentIndex(1);
				referenceTypeNodeId_.set(OpcUaId_Organizes);
				break;
			}
			case NodeClassType_Variable:
			{
				createAttributes("Variable");
				stackedWidget_->setCurrentIndex(2);
				referenceTypeNodeId_.set(OpcUaId_Organizes);
				break;
			}
			case NodeClassType_Method:
			{
				createAttributes("Method");
				stackedWidget_->setCurrentIndex(0);
				referenceTypeNodeId_.set(OpcUaId_Organizes);
				break;
			}
			case NodeClassType_ObjectType:
			{
				createAttributes("ObjectType");
				stackedWidget_->setCurrentIndex(0);
				referenceTypeNodeId_.set(OpcUaId_HasSubtype);
				break;
			}
			case NodeClassType_VariableType:
			{
				createAttributes("VariableType");
				stackedWidget_->setCurrentIndex(0);
				referenceTypeNodeId_.set(OpcUaId_HasSubtype);
				break;
			}
			case NodeClassType_ReferenceType:
			{
				createAttributes("ReferenceType");
				stackedWidget_->setCurrentIndex(0);
				referenceTypeNodeId_.set(OpcUaId_HasSubtype);
				break;
			}
			case NodeClassType_DataType:
			{
				createAttributes("DataType");
				stackedWidget_->setCurrentIndex(0);
				referenceTypeNodeId_.set(OpcUaId_HasSubtype);
				break;
			}
			default:
			{
				createAttributes("Variable");
				stackedWidget_->setCurrentIndex(2);
				referenceTypeNodeId_.set(OpcUaId_Organizes);
				break;
			}
		}

		nodeIdWidget_->setValue(nodeId_);
		displayNameWidget_->setValue(displayName_);
		browseNameWidget_->setValue(browseName_);
		referenceTypeWidget_->setValue(referenceTypeNodeId_);

		isValid_ = checkValue();
		controlButton();
	}

	void
	CreateNodeDialog::onClickedObjectType(void)
	{
		createAttributes("Object");

		SelectObjectTypeDialog dialog(dataModel_);
		dialog.exec();

		objectTypeWidget_->setValue(dialog.objectType());

		isValid_ = checkValue();
		controlButton();
	}

	void
	CreateNodeDialog::onClickedVariableType(void)
	{
		createAttributes("Variable");

		SelectVariableTypeDialog dialog(dataModel_);
		dialog.exec();

		variableTypeWidget_->setValue(dialog.variableType());

		isValid_ = checkValue();
		controlButton();
	}

	void
	CreateNodeDialog::onClickedReferenceType(void)
	{
		SelectReferenceTypeDialog dialog(dataModel_);
		dialog.exec();

		referenceTypeWidget_->setValue(dialog.referenceType());

		isValid_ = checkValue();
	}

    void
    CreateNodeDialog::onValueChangedNodeId(OpcUaNodeId& nodeId, bool isValid)
    {
    	isValid_ = checkValue();
    	controlButton();
    }

    void
    CreateNodeDialog::onValueChangedDisplayName(OpcUaLocalizedText& displayName, bool isValid)
    {
    	isValid_ = checkValue();
    	controlButton();
    }

    void
    CreateNodeDialog::onValueChangedBrowseName(OpcUaQualifiedName& browseName, bool isValid)
    {
    	isValid_ = checkValue();
    	controlButton();
    }

    void
    CreateNodeDialog::onClickedOk(void)
    {
    	isOk_ = true;
    	close();
    }

    void
    CreateNodeDialog::onClickedCancel(void)
    {
    	isValid_ = false;
    	close();
    }

}


