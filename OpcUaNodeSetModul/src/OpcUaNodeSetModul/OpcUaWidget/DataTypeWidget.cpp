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

#include "OpcUaStackServer/InformationModel/InformationModelAccess.h"
#include "OpcUaNodeSetModul/OpcUaWidget/DataTypeWidget.h"

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	DataTypeWidget::DataTypeWidget(QWidget* parent)
	: QWidget()
	, informationModel_()
	, dataType_()
	, isValid_(false)
	, checkOn_(true)
	{
		// widgets
		textWidget_ = new QLineEdit();
		textWidget_->setFixedWidth(370-5);

		buttonWidget_ = new QPushButton("...");
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

	DataTypeWidget::~DataTypeWidget(void)
	{
	}

	void
	DataTypeWidget::setValue(InformationModel::SPtr& informationModel)
	{
		informationModel_ = informationModel;
	}

	void
	DataTypeWidget::setValue(OpcUaNodeId& dataType)
	{
		dataType_ = dataType;
		checkOn_ = false;
		showValue();
		checkOn_ = true;
		isValid_ = checkValue();
		styleValue();
		emit valueChanged(dataType_, isValid_);
	}

	void
	DataTypeWidget::getValue(OpcUaNodeId& dataType)
	{
		dataType = dataType_;
	}

	bool
	DataTypeWidget::isValid(void)
	{
		return isValid_;
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	DataTypeWidget::showValue(void)
	{
		if (informationModel_.get() == NULL) {
			textWidget_->setText(QString(""));
			return;
		}

		BaseNodeClass::SPtr baseNode = informationModel_->find(dataType_);
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
	DataTypeWidget::checkValue(void)
	{
		if (informationModel_.get() == NULL) {
			return false;
		}

		BaseNodeClass::SPtr baseNode = informationModel_->find(dataType_);
		if (baseNode.get() == NULL) {
			return false;
		}

		if (textWidget_->text().isEmpty()) {
			return false;
		}

		return true;
	}

	void
	DataTypeWidget::findNodeId(const std::string& displayName, OpcUaNodeId& typeNode)
	{
		if (informationModel_.get() == NULL) {
			return;
		}

		BaseNodeClass::SPtr baseNode = informationModel_->find(typeNode);
		if (baseNode.get() == NULL) {
			return;
		}


		OpcUaLocalizedText tmpDisplayName;
		baseNode->getDisplayName(tmpDisplayName);

		std::string locale;
		std::string text;
		tmpDisplayName.get(locale, text);
		if (text == displayName) {
			dataType_ = typeNode;
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
	DataTypeWidget::styleValue(void)
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
	DataTypeWidget::onTextChanged(const QString& text)
	{
		if (!checkOn_) return;

		// find node id from text
		dataType_.set(0);
		OpcUaNodeId typeNode(24);
		findNodeId(text.toStdString(), typeNode);

		isValid_ = checkValue();
		styleValue();
		emit valueChanged(dataType_, isValid_);
	}

	void
	DataTypeWidget::onClicked(void)
	{
		emit selectDataType();
	}


}


