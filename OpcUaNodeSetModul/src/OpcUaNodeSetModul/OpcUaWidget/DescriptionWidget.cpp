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

#include "OpcUaNodeSetModul/OpcUaWidget/DescriptionWidget.h"

namespace OpcUaNodeSet
{


	DescriptionWidget::DescriptionWidget(QWidget* parent)
	: QWidget()
	, checkOn_(true)
	{
		// widgets
		localeWidget_ = new QLineEdit();
		localeWidget_->setFixedWidth(50);

		textWidget_ = new QLineEdit();
		textWidget_->setFixedWidth(350-5);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(localeWidget_);
		hBoxLayout->addWidget(textWidget_);
		hBoxLayout->setMargin(0);

		//
		// actions
		//
		connect(
			localeWidget_, SIGNAL(textChanged(const QString&)),
			this, SLOT(onTextChangedLocaleWidget(const QString&))
		);
		connect(
			textWidget_, SIGNAL(textChanged(const QString&)),
			this, SLOT(onTextChangedTextWidget(const QString&))
		);

		setLayout(hBoxLayout);
	}

	DescriptionWidget::~DescriptionWidget(void)
	{
	}

	bool
	DescriptionWidget::isValid(void)
	{
		return true;
	}

	void
	DescriptionWidget::nodeChange(NodeInfo* nodeInfo)
	{
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullDescription()) {
			localeWidget_->setText(QString(""));
			textWidget_->setText(QString(""));
		}

		checkOn_ = false;
		OpcUaLocalizedText description;
		baseNode->getDescription(description);
		localeWidget_->setText(QString(description.locale().value().c_str()));
		textWidget_->setText(QString(description.text().value().c_str()));
		checkOn_ = true;
	}

	void
	DescriptionWidget::enabled(bool enabled)
	{
		localeWidget_->setEnabled(enabled);
		textWidget_->setEnabled(enabled);
	}

	void
	DescriptionWidget::onTextChangedLocaleWidget(const QString& text)
	{
		if (!checkOn_) return;

		OpcUaLocalizedText description;
		description.set(localeWidget_->text().toStdString(), textWidget_->text().toStdString());
		emit valueChanged(description, true);
	    emit update();
	}

	void
	DescriptionWidget::onTextChangedTextWidget(const QString& text)
	{
		if (!checkOn_) return;

		OpcUaLocalizedText description;
		description.set(localeWidget_->text().toStdString(), textWidget_->text().toStdString());
		emit valueChanged(description, true);
	    emit update();
	}

}


