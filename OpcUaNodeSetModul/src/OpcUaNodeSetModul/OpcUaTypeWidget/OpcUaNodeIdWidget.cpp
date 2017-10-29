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

#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackServer/InformationModel/InformationModelAccess.h"
#include "OpcUaNodeSetModul/OpcUaTypeWidget/OpcUaNodeIdWidget.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	OpcUaNodeIdWidget::OpcUaNodeIdWidget(QWidget* parent)
	: QWidget()
	, informationModel_()
	, nodeId_()
	, newNodeId_(0,0)
	, rootNodeId_(OpcUaId_BaseDataType)
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
	OpcUaNodeIdWidget::rootNodeId(const OpcUaNodeId& rootNodeId)
	{
		rootNodeId_ = rootNodeId;
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
		if (nodeId_ == newNodeId_) return;

		nodeId_ = nodeId;
		newNodeId_ = nodeId;

		// get display name from nodeid
		OpcUaLocalizedText displayName;
		if (!getDisplayNameFromNodeId(nodeId, displayName)) {
			isValid_ = false;
			displayName.set("", nodeId.toString());
		}
		else {
			isValid_ = true;
		}

		checkOn_ = false;
		std::string locale;
		std::string text;
		displayName.get(locale, text);
		textWidget_->setText(QString(text.c_str()));
		checkOn_ = true;

		styleValue();
	}

	void
	OpcUaNodeIdWidget::getOldValue(OpcUaNodeId& nodeId)
	{
		nodeId = nodeId_;
	}

	void
	OpcUaNodeIdWidget::getNewValue(OpcUaNodeId& nodeId)
	{
		nodeId = newNodeId_;
	}

	bool
	OpcUaNodeIdWidget::isValid(void)
	{
		return isValid_;
	}

	bool
	OpcUaNodeIdWidget::acceptValue(void)
	{
		if (nodeId_ == newNodeId_) return false;
		nodeId_ = newNodeId_;
		return false;
	}


	void
	OpcUaNodeIdWidget::resetValue(void)
	{
		setValue(nodeId_);
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
		OpcUaNodeId nodeId = rootNodeId_;
		if (!getNodeIdFromDisplayName(text.toStdString(), nodeId)) {
			isValid_ = false;
		}
		else {
			isValid_ = true;
			newNodeId_ = nodeId;
		}

		styleValue();
		if (nodeId_ != newNodeId_) {
			emit update();
		}
	}

	void
	OpcUaNodeIdWidget::onClicked(void)
	{
		emit selectDataType();
	}


	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
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

	bool
	OpcUaNodeIdWidget::getNodeIdFromDisplayName(const std::string& displayName, OpcUaNodeId& rootNodeId)
	{
		if (informationModel_.get() == NULL) {
			return false;
		}

		BaseNodeClass::SPtr baseNode = informationModel_->find(rootNodeId);
		if (baseNode.get() == NULL) {
			return false;
		}

		OpcUaLocalizedText tmpDisplayName;
		baseNode->getDisplayName(tmpDisplayName);

		std::string locale;
		std::string text;
		tmpDisplayName.get(locale, text);
		if (text == displayName) {
			nodeId_ = rootNodeId;
			return true;
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
			if (getNodeIdFromDisplayName(displayName, childNodeId)) {
				return true;
			}
		}

		return false;
	}

	bool
	OpcUaNodeIdWidget::getDisplayNameFromNodeId(OpcUaNodeId& nodeId, OpcUaLocalizedText& displayName)
	{
		if (informationModel_.get() == NULL) {
			return false;
		}

		BaseNodeClass::SPtr baseNode = informationModel_->find(nodeId_);
		if (baseNode.get() == NULL) {
			return false;
		}

		return baseNode->getDisplayName(displayName);
	}

}


