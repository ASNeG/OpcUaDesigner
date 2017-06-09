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
#include "OpcUaNodeSetModul/OpcUaWidget/NodeClassWidget.h"
#include "OpcUaNodeSetModul/OpcUaWidget/NodeIdWidget.h"
#include "OpcUaNodeSetModul/OpcUaWidget/BrowseNameWidget.h"

namespace OpcUaNodeSet
{


	CreateNodeDialog::CreateNodeDialog(DataModel* dataModel)
	: QDialog()
	, dataModel_(dataModel)
	{
		createLayout();
	}

	CreateNodeDialog::~CreateNodeDialog(void)
	{
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

		QStringList nodeClassList;
		nodeClassList << "Object" << "Variable";
		NodeClassWidget* nodeClassWidget = new NodeClassWidget(nodeClassList);
		baseInfoLayout->addWidget(nodeClassWidget, 0, 1);

		// node id
		QLabel* nodeIdLabel = new QLabel("NodeId");
		baseInfoLayout->addWidget(nodeIdLabel, 1, 0);

		NodeIdWidget* nodeIdWidget = new NodeIdWidget();

		QHBoxLayout* hBoxLayoutInfo = new QHBoxLayout();
		hBoxLayoutInfo->addWidget(nodeIdWidget);
		hBoxLayoutInfo->addStretch();

		baseInfoLayout->addLayout(hBoxLayoutInfo, 1, 1);

		// browse name
		QLabel* browseNameLabel = new QLabel("BrowseName");
		baseInfoLayout->addWidget(browseNameLabel, 2, 0);

		BrowseNameWidget* browseNameWidget = new BrowseNameWidget();

		hBoxLayoutInfo = new QHBoxLayout();
		hBoxLayoutInfo->addWidget(browseNameWidget);
		hBoxLayoutInfo->addStretch();

		baseInfoLayout->addLayout(hBoxLayoutInfo, 2, 1);

		//
		//
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

       	//
       	// object type
       	//
        QLabel* objectTypeLabel = new QLabel("Object Type   ");
        gridLayout->addWidget(objectTypeLabel, 0, 0);

        QHBoxLayout* objectTypeLayout = new QHBoxLayout();
        gridLayout->addLayout(objectTypeLayout, 0, 1);

        QLineEdit* objectTypeLineEdit = new QLineEdit();
        objectTypeLayout->addWidget(objectTypeLineEdit);

        QPushButton* objectTypePushButton = new QPushButton("...");
        objectTypePushButton->setFixedWidth(30);
        objectTypeLayout->addWidget(objectTypePushButton);

        widget->setLayout(gridLayout);
    	return widget;
    }

	QWidget*
    CreateNodeDialog::createValueWidget(void)
    {
    	QWidget* widget = new QWidget();
    	return widget;
    }

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// dialog slots
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------

}


