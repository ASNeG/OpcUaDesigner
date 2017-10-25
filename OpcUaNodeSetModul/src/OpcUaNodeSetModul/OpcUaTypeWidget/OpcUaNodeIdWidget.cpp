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
#include <QLineEdit>
#include <QPushButton>
#include <QIcon>

#include "OpcUaStackServer/InformationModel/InformationModelAccess.h"
#include "OpcUaNodeSetModul/OpcUaTypeWidget/OpcUaNodeIdWidget.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	OpcUaNodeIdWidget::OpcUaNodeIdWidget(QWidget* parent)
	: QWidget()
	, informationModel_()
	, nodeId_()
	, rootNodeId_(24)
	, isValid_(false)
	, checkOn_(true)
	{
		// widgets
		textWidget_ = new QLineEdit();
		textWidget_->setFixedWidth(365);

		buttonWidget_ = new QPushButton();
		buttonWidget_->setIcon(QIcon(":/images/Tree.png"));
		buttonWidget_->setFixedWidth(30);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(textWidget_);
		hBoxLayout->addWidget(buttonWidget_);
		hBoxLayout->setMargin(0);

		//
		// actions
		//
		connect(
			textWidget_, SIGNAL(textChanged(const QString&)),
			this, SLOT(onTextChanged(const QString&))
		);
		connect(
			buttonWidget_, SIGNAL(clicked()),
			this, SLOT(onClicked())
		);

		setLayout(hBoxLayout);
	}

	OpcUaNodeIdWidget::~OpcUaNodeIdWidget(void)
	{
	}

	void
	OpcUaNodeIdWidget::enabled(bool enabled)
	{
		textWidget_->setEnabled(enabled);
		buttonWidget_->setEnabled(enabled);
	}

	void
	OpcUaNodeIdWidget::informationModel(InformationModel::SPtr& informationModel)
	{
		informationModel_ = informationModel;
	}

	void
	OpcUaNodeIdWidget::setValue(OpcUaNodeId& nodeId)
	{
		nodeId_ = nodeId;

		checkOn_ = false;
		showValue();
		checkOn_ = true;
		isValid_ = checkValue();
		styleValue();
	}

	void
	OpcUaNodeIdWidget::getValue(OpcUaNodeId& nodeId)
	{
		nodeId = nodeId_;
	}

	bool
	OpcUaNodeIdWidget::isValid(void)
	{
		return isValid_;
	}

	void
	OpcUaNodeIdWidget::acceptValue(void)
	{
		getValue(nodeId_);
	}


	void
	OpcUaNodeIdWidget::resetValue(void)
	{
		setValue(nodeId_);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	OpcUaNodeIdWidget::showValue(void)
	{
		if (informationModel_.get() == NULL) {
			textWidget_->setText(QString(""));
			return;
		}

		BaseNodeClass::SPtr baseNode = informationModel_->find(nodeId_);
		if (baseNode.get() == NULL) {
			textWidget_->setText(QString(""));
			return;
		}

		OpcUaLocalizedText displayName;
		baseNode->getDisplayName(displayName);

		std::string locale;
		std::string text;
		displayName.get(locale, text);
		textWidget_->setText(QString(text.c_str()));
	}

	bool
	OpcUaNodeIdWidget::checkValue(void)
	{
		if (informationModel_.get() == NULL) {
			return false;
		}

		BaseNodeClass::SPtr baseNode = informationModel_->find(nodeId_);
		if (baseNode.get() == NULL) {
			return false;
		}

		if (textWidget_->text().isEmpty()) {
			return false;
		}

		return true;
	}

	void
	OpcUaNodeIdWidget::findNodeId(const std::string& displayName, OpcUaNodeId& rootNodeId)
	{
		if (informationModel_.get() == NULL) {
			return;
		}

		BaseNodeClass::SPtr baseNode = informationModel_->find(rootNodeId);
		if (baseNode.get() == NULL) {
			return;
		}


		OpcUaLocalizedText tmpDisplayName;
		baseNode->getDisplayName(tmpDisplayName);

		std::string locale;
		std::string text;
		tmpDisplayName.get(locale, text);
		if (text == displayName) {
			nodeId_ = rootNodeId;
			return;
		}

		// search children elements
		BaseNodeClass::Vec::iterator it;
		BaseNodeClass::Vec childBaseNodeClassVec;
		InformationModelAccess ima(informationModel_);
		ima.getChildHierarchically(baseNode, childBaseNodeClassVec);
		for (it = childBaseNodeClassVec.begin(); it != childBaseNodeClassVec.end(); it++) {
			BaseNodeClass::SPtr child = *it;

			OpcUaNodeId childNodeId;
			child->getNodeId(childNodeId);
			findNodeId(displayName, childNodeId);
		}
	}

	void
	OpcUaNodeIdWidget::styleValue(void)
	{
		if (isValid_) {
			textWidget_->setStyleSheet("background-color:none;");
		}
		else {
			textWidget_->setStyleSheet("background-color:red;");
		}
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// added slots
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	OpcUaNodeIdWidget::onTextChanged(const QString& text)
	{
		if (!checkOn_) return;

		// find node id from text
		nodeId_.set(0);
		findNodeId(text.toStdString(), rootNodeId_);

		isValid_ = checkValue();
		styleValue();
		emit update();
	}

	void
	OpcUaNodeIdWidget::onClicked(void)
	{
		emit selectDataType();
	}


}


