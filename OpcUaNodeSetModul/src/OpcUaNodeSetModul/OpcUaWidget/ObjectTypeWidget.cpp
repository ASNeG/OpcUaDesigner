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

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QPushButton>

#include "OpcUaNodeSetModul/OpcUaWidget/ObjectTypeWidget.h"

namespace OpcUaNodeSet
{


	ObjectTypeWidget::ObjectTypeWidget(QWidget* parent)
	: QWidget(parent)
	{
		createLayout();
	}

	ObjectTypeWidget::~ObjectTypeWidget(void)
	{
	}

	void
	ObjectTypeWidget::createLayout(void)
	{
		QVBoxLayout* layout = new QVBoxLayout();
		layout->setMargin(0);

		//
		// object type tree
		//
		objectTypeTree_ = new QTreeWidget();
		layout->addWidget(objectTypeTree_);

		//
		// dialog action button
		//
		QHBoxLayout* actionButtonLayout = new QHBoxLayout();
		QPushButton* cancelButton = new QPushButton("Cancel");
		actionButtonLayout->addWidget(cancelButton);
		QPushButton* okButton = new QPushButton("Ok");
		okButton->setEnabled(false);
		actionButtonLayout->addWidget(okButton);
		layout->addLayout(actionButtonLayout);


		layout->addStretch();
		setLayout(layout);
	}

}


