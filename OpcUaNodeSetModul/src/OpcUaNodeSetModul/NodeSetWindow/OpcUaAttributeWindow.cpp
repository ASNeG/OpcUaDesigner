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

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeWindow.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeBaseTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeRefTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeParentTab.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaAttributeChildTab.h"

namespace OpcUaNodeSet
{


	OpcUaAttributeWindow::OpcUaAttributeWindow(QWidget* parent)
	: QWidget()
	{
		// create opc ua attribute tab
		opcUaAttributeTab_ = new QTabWidget();

		OpcUaAttributeBaseTab* tabBase = new  OpcUaAttributeBaseTab();
		opcUaAttributeTab_->addTab(tabBase, "Base Attributes");

		OpcUaAttributeParentTab* tabParent = new  OpcUaAttributeParentTab();
		opcUaAttributeTab_->addTab(tabParent, "Parent");

		OpcUaAttributeChildTab* tabChild = new  OpcUaAttributeChildTab();
		opcUaAttributeTab_->addTab(tabChild, "Childs");

		OpcUaAttributeRefTab* tabRef = new  OpcUaAttributeRefTab();
		opcUaAttributeTab_->addTab(tabRef, "References");

		// show opc ua attriubute tab
		QVBoxLayout* layout_ = new QVBoxLayout();
		layout_->addWidget(opcUaAttributeTab_);
		setLayout(layout_);
	}

	OpcUaAttributeWindow::~OpcUaAttributeWindow(void)
	{
	}

}


