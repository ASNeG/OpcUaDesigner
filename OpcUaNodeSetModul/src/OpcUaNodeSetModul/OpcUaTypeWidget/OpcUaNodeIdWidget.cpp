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
	, savedValue_(0,0)
	, displayValue_(0,0)
	, rootNodeId_(OpcUaId_BaseDataType)
	, isValid_(false)
	, checkOn_(true)
	{
		// widgets
		buttonWidget_ = new QPushButton();
		buttonWidget_->setIcon(QIcon(":/images/Tree.png"));
		buttonWidget_->setFixedWidth(30);

		textWidget_ = new QLineEdit();
		textWidget_->setFixedWidth(365);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(buttonWidget_);
		hBoxLayout->addWidget(textWidget_);
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
	OpcUaNodeIdWidget::setSavedValue(OpcUaNodeId& savedValue)
	{
		savedValue_ = savedValue;

		checkOn_ = false;
		setDisplayValue(savedValue);
		checkOn_ = true;
	}

	void
	OpcUaNodeIdWidget::setDisplayValue(OpcUaNodeId& displayValue)
	{
		displayValue_ = displayValue;

		// get display name from nodeid
		OpcUaLocalizedText displayName;
		if (!getDisplayNameFromNodeId(displayValue, displayName)) {
			isValid_ = false;
			displayName.set("", displayValue.toString());
		}
		else {
			isValid_ = true;
		}

		std::string locale;
		std::string text;
		displayName.get(locale, text);
		textWidget_->setText(QString(text.c_str()));

		styleValue();
	}

	void
	OpcUaNodeIdWidget::getSavedValue(OpcUaNodeId& savedValue)
	{
		savedValue = savedValue_;
	}

	void
	OpcUaNodeIdWidget::getDisplayValue(OpcUaNodeId& displayValue)
	{
		displayValue = displayValue_;
	}

	bool
	OpcUaNodeIdWidget::isValid(void)
	{
		return isValid_;
	}

	bool
	OpcUaNodeIdWidget::acceptValue(void)
	{
		if (savedValue_ != displayValue_) {
			savedValue_ = displayValue_;
			return true;
		}
		return false;
	}


	void
	OpcUaNodeIdWidget::resetValue(void)
	{
		setDisplayValue(savedValue_);
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
			displayValue_ = nodeId;
		}

		styleValue();
		if (savedValue_ != displayValue_) {
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
				rootNodeId = childNodeId;
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

		BaseNodeClass::SPtr baseNode = informationModel_->find(nodeId);
		if (baseNode.get() == NULL) {
			return false;
		}

		return baseNode->getDisplayName(displayName);
	}

}


