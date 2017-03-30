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

namespace OpcUaNodeSet
{


	OpcUaAttributeWindow::OpcUaAttributeWindow(QWidget* parent)
	: QWidget()
	{
		// create opc ua attribute tab
		opcUaAttributeTab_ = new QTabWidget();
		opcUaAttributeTab_->setMinimumWidth(600);

		tabBase_ = new  OpcUaAttributeBaseTab();
		opcUaAttributeTab_->addTab(tabBase_, "Attributes");

		tabParent_ = new  OpcUaAttributeParentTab();
		opcUaAttributeTab_->addTab(tabParent_, "Parent");

		tabChild_ = new  OpcUaAttributeChildTab();
		opcUaAttributeTab_->addTab(tabChild_, "Childs");

		tabRef_ = new  OpcUaAttributeRefTab();
		opcUaAttributeTab_->addTab(tabRef_, "References");

		// show opc ua attriubute tab
		QVBoxLayout* layout_ = new QVBoxLayout();
		layout_->addWidget(opcUaAttributeTab_);
		setLayout(layout_);
	}

	OpcUaAttributeWindow::~OpcUaAttributeWindow(void)
	{
		delete tabBase_;
		delete tabParent_;
		delete tabChild_;
		delete tabRef_;
	}

	void
	OpcUaAttributeWindow::onNodeChanged(BaseNodeClass* nodeClass)
	{
		std::cout << "onCurrentItemChanged OpcUaAttributeWindow..." << std::endl;
		nodeClass_ = nodeClass;
		onVisibleChanged(0);
	}

	void
	OpcUaAttributeWindow::onVisibleChanged(int index)
	{
		if (nodeClass_ == NULL) return;

		if (tabBase_->isVisible()) {
			std::cout << "tabBase_ is activated..." << std::endl;
		}
		else if (tabParent_->isVisible()) {
			std::cout << "tabParent_ is activated..." << std::endl;
		}
		else if (tabChild_->isVisible()) {
			std::cout << "tabChild_ is activated..." << std::endl;
		}
		else if (tabRef_->isVisible()) {
			std::cout << "tabRef_ is activated..." << std::endl;
		}
	}

}


