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
#include <QComboBox>
#include <QStringList>
#include <QString>

#include "OpcUaNodeSetModul/OpcUaWidget/NodeIdWidget.h"

namespace OpcUaNodeSet
{


	NodeIdWidget::NodeIdWidget(QWidget* parent)
	: QWidget()
	, nodeId_()
	, informationModel_()
	, nodeSetNamespace_(nullptr)
	, isValid_(false)
	, checkOn_(true)
	{
		// widgets
		QStringList typeList;
		typeList << "Numeric" << "String" << "Guid" << "Unknown";
		typeWidget_ = new QComboBox();
		typeWidget_->addItems(typeList);
		typeWidget_->setFixedWidth(120);

		nodeIdWidget_ = new QLineEdit();
		nodeIdWidget_->setFixedWidth(280-5);

		namespaceWidget_ = new QComboBox();
		namespaceWidget_->setFixedWidth(400);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->setSpacing(5);
		hBoxLayout->addWidget(typeWidget_);
		hBoxLayout->addWidget(nodeIdWidget_);
		hBoxLayout->addStretch();
		hBoxLayout->setMargin(0);

		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->addLayout(hBoxLayout);
		vBoxLayout->addWidget(namespaceWidget_);
		vBoxLayout->setMargin(0);

		//
		// actions
		//
		connect(
			typeWidget_, SIGNAL(currentIndexChanged(int)),
			this, SLOT(onCurrentIndexChangedTypeWidget(int))
		);
		connect(
			namespaceWidget_, SIGNAL(currentIndexChanged(int)),
			this, SLOT(onCurrentIndexChangedNamespaceWidget(int))
		);
		connect(
			nodeIdWidget_, SIGNAL(textChanged(const QString&)),
			this, SLOT(onTextChanged(const QString&))
		);

		setLayout(vBoxLayout);
	}

	NodeIdWidget::~NodeIdWidget(void)
	{
	}

	void
	NodeIdWidget::setValue(InformationModel::SPtr& informationModel)
	{
		informationModel_ = informationModel;
	}

	void
	NodeIdWidget::setValue(NodeSetNamespace& nodeSetNamespace)
	{
		nodeSetNamespace_ = &nodeSetNamespace;
	}

	void
	NodeIdWidget::setValue(OpcUaNodeId& nodeId)
	{
		nodeId_ = nodeId;
		checkOn_ = false;
		showValue();
		checkOn_ = true;
		isValid_ = checkValue();
		styleValue();
		emit valueChanged(nodeId_, isValid_);
	}

	void
	NodeIdWidget::getValue(OpcUaNodeId& nodeId)
	{
		nodeId = nodeId_;
	}

	void
	NodeIdWidget::showValue(void)
	{
		std::cout << "Nam..." << nodeId_.toString() << std::endl;
		switch (nodeId_.nodeIdType())
		{
			case OpcUaBuildInType_OpcUaUInt32:
			{
				OpcUaUInt16 namespaceIndex;
				OpcUaUInt32 value;
				nodeId_.get(value, namespaceIndex);
				typeWidget_->setCurrentIndex(0);
				nodeIdWidget_->setText(QString("%1").arg(value));
				break;
			}
			case OpcUaBuildInType_OpcUaString:
			{
				OpcUaUInt16 namespaceIndex;
				std::string value;
				nodeId_.get(value, namespaceIndex);
				typeWidget_->setCurrentIndex(1);
				nodeIdWidget_->setText(value.c_str());
				break;
			}
			case OpcUaBuildInType_OpcUaGuid:
			{
				OpcUaUInt16 namespaceIndex;
				std::string value;
				nodeId_.get(value, namespaceIndex);
				typeWidget_->setCurrentIndex(2);
				nodeIdWidget_->setText(QString(value.c_str()));
				break;
			}
			default:
			{
				typeWidget_->setCurrentIndex(3);
				nodeIdWidget_->setText(QString("???"));
				break;
			}
		}

		// set namespace
		if (nodeSetNamespace_ != NULL) {
			namespaceWidget_->clear();
			for (uint32_t idx = 0; idx < nodeSetNamespace_->globalNamespaceVec().size(); idx++) {
				namespaceWidget_->addItem(nodeSetNamespace_->globalNamespaceVec()[idx].c_str());
			}
			namespaceWidget_->setCurrentIndex(nodeId_.namespaceIndex());
		}
	}

	bool
	NodeIdWidget::checkValue(void)
	{
		// create node id
		OpcUaNodeId nodeId;

		// check namespace
		std::cout << "idx= " << namespaceWidget_->currentIndex() << std::endl;
		if (namespaceWidget_->currentIndex() < 0) return false;
		if (nodeIdWidget_->text().length() == 0) return false;

		// check type
		switch (typeWidget_->currentIndex())
		{
			case 0: // numeric
			{
				QRegExp rx("\\d+");
				if (!rx.exactMatch(nodeIdWidget_->text())) {
					return false;
				}

				uint32_t id = nodeIdWidget_->text().toInt();
				nodeId.set(id, (uint16_t)namespaceWidget_->currentIndex());

				break;
			}
			case 1: // string
			{
				std::string id = nodeIdWidget_->text().toStdString();
				nodeId.set(id, (uint16_t)namespaceWidget_->currentIndex());

				break;
			}
			case 2: // guid
			{
				QRegExp rx("[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}");
				if (!rx.exactMatch(nodeIdWidget_->text())) {
					return false;
				}

				std::string id = nodeIdWidget_->text().toStdString();
				nodeId.set(id, (uint16_t)namespaceWidget_->currentIndex());

				break;
			}
			default:
			{
				return false;
			}
		}

		// check if value exist
		if (informationModel_.get() == NULL) {
			nodeId_ = nodeId;
			return true;
		}

		BaseNodeClass::SPtr baseNode = informationModel_->find(nodeId);
		if (baseNode.get() != NULL) return false;

		nodeId_ = nodeId;
		return true;
	}

	void
	NodeIdWidget::styleValue(void)
	{
		if (isValid_) {
			nodeIdWidget_->setStyleSheet("background-color:none;");
		}
		else {
			nodeIdWidget_->setStyleSheet("background-color:red;");
		}
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// slots
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	NodeIdWidget::onCurrentIndexChangedTypeWidget(int index)
	{
		if (!checkOn_) return;
		isValid_ = checkValue();
		styleValue();
		emit valueChanged(nodeId_, isValid_);
	}

	void
	NodeIdWidget::onCurrentIndexChangedNamespaceWidget(int index)
	{
		if (!checkOn_) return;
		isValid_ = checkValue();
		styleValue();
		emit valueChanged(nodeId_, isValid_);
	}

	void
	NodeIdWidget::onTextChanged(const QString& text)
	{
		if (!checkOn_) return;
		isValid_ = checkValue();
		styleValue();
		emit valueChanged(nodeId_, isValid_);
	}

}


