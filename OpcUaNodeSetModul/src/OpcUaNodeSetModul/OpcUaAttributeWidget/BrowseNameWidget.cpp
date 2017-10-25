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
#include <QLineEdit>
#include <QComboBox>
#include <QStringList>
#include <QString>

#include "OpcUaNodeSetModul/OpcUaAttributeWidget/BrowseNameWidget.h"

namespace OpcUaNodeSet
{


	BrowseNameWidget::BrowseNameWidget(QWidget* parent)
	: QWidget()
	, nodeSetNamespace_(NULL)
	, browseName_()
	, isValid_(false)
	, checkOn_(true)
	{
		// widgets
		browseNameWidget_ = new QLineEdit();
		browseNameWidget_->setFixedWidth(400);

		namespaceWidget_ = new QComboBox();
		namespaceWidget_->setFixedWidth(400);

		// layout
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->addWidget(browseNameWidget_);
		vBoxLayout->addWidget(namespaceWidget_);
		vBoxLayout->addStretch();
		vBoxLayout->setMargin(0);
		setLayout(vBoxLayout);

		//
		// actions
		//
		connect(
			namespaceWidget_, SIGNAL(currentIndexChanged(int)),
			this, SLOT(onCurrentIndexChangedNamespaceWidget(int))
		);
		connect(
			browseNameWidget_, SIGNAL(textChanged(const QString&)),
			this, SLOT(onTextChanged(const QString&))
		);
	}

	BrowseNameWidget::~BrowseNameWidget(void)
	{
	}

	void
	BrowseNameWidget::setValue(NodeSetNamespace& nodeSetNamespace)
	{
		nodeSetNamespace_ = &nodeSetNamespace;
	}

	void
	BrowseNameWidget::setValue(OpcUaQualifiedName& browseName)
	{
		browseName_ = browseName;
		checkOn_ = false;
		showValue();
		checkOn_ = true;
		isValid_ = checkValue();
		styleValue();
		//emit valueChanged(browseName_, isValid_);
	}

	void
	BrowseNameWidget::getValue(OpcUaQualifiedName& browseName)
	{
		browseName = browseName_;
	}

	bool
	BrowseNameWidget::isValid(void)
	{
		return isValid_;
	}

	void
	BrowseNameWidget::enabled(bool enabled)
	{
		browseNameWidget_->setEnabled(enabled);
		namespaceWidget_->setEnabled(enabled);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// slots
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	BrowseNameWidget::onCurrentIndexChangedNamespaceWidget(int index)
	{
		if (!checkOn_) return;
		isValid_ = checkValue();
		styleValue();

		// set value
		if (isValid_) {
			browseName_.set(browseNameWidget_->text().toStdString(), namespaceWidget_->currentIndex());
		}
		emit valueChanged(browseName_, isValid_);
		emit update();
	}

	void
	BrowseNameWidget::onTextChanged(const QString& text)
	{
		if (!checkOn_) return;
		isValid_ = checkValue();
		styleValue();

		// set value
		if (isValid_) {
			browseName_.set(browseNameWidget_->text().toStdString(), namespaceWidget_->currentIndex());
		}
		emit valueChanged(browseName_, isValid_);
		emit update();
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	BrowseNameWidget::showValue(void)
	{
		std::string text;
		OpcUaUInt16 namespaceIndex;
		browseName_.get(text, namespaceIndex);
		browseNameWidget_->setText(QString(text.c_str()));

		// set namespace
		if (nodeSetNamespace_ != NULL) {
			namespaceWidget_->clear();
			for (uint32_t idx = 0; idx < nodeSetNamespace_->globalNamespaceVec().size(); idx++) {
				namespaceWidget_->addItem(nodeSetNamespace_->globalNamespaceVec()[idx].c_str());
			}
			namespaceWidget_->setCurrentIndex(browseName_.namespaceIndex());
		}
	}

	bool
	BrowseNameWidget::checkValue(void)
	{
		// check namespace
		if (namespaceWidget_->currentIndex() < 0) return false;
		if (browseNameWidget_->text().length() == 0) return false;
		return true;
	}

	void
	BrowseNameWidget::styleValue(void)
	{
		if (isValid_) {
			browseNameWidget_->setStyleSheet("background-color:none;");
		}
		else {
			browseNameWidget_->setStyleSheet("background-color:red;");
		}
	}

}


