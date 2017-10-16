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
#include <QTableWidget>

#include "OpcUaNodeSetModul/OpcUaWidget/ArgumentsWidget.h"

namespace OpcUaNodeSet
{


	ArgumentsWidget::ArgumentsWidget(QWidget* parent)
	: QWidget()
	, checkOn_(true)
	, isValid_(true)
	{
		// widgets
		table_ = new QTableWidget(0,4);

		// layout
		QHBoxLayout* hBoxLayout = new QHBoxLayout();
		hBoxLayout->addWidget(table_);
		hBoxLayout->setMargin(0);

		setLayout(hBoxLayout);

		//
		// actions
		//
		//connect(
		//	textWidget_, SIGNAL(textChanged(const QString&)),
		//	this, SLOT(onTextChangedTextWidget(const QString&))
		//)
	}

	ArgumentsWidget::~ArgumentsWidget(void)
	{
	}

	bool
	ArgumentsWidget::isValid(void)
	{
		return isValid_;
	}

	void
	ArgumentsWidget::nodeChange(NodeInfo* nodeInfo)
	{
#if 0
		BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;
		if (baseNode->isNullArguments()) {
			textWidget_->setText(QString("0"));
		}

		checkOn_ = false;
		OpcUaByte accessLevel;
		baseNode->getArguments(accessLevel);
		textWidget_->setText(QString("%1").arg((uint32_t)accessLevel));
		isValid_ = checkValue();
		styleValue();
		checkOn_ = true;
#endif
	}

	void
	ArgumentsWidget::enabled(bool enabled)
	{
		table_->setEnabled(enabled);
	}

	void
	ArgumentsWidget::getValue(OpcUaByte& accessLevel)
	{
#if 0
		bool rc;
		accessLevel = textWidget_->text().toInt(&rc);
#endif
	}

	bool
	ArgumentsWidget::checkValue(void)
	{
		// FIXME: todo
		return true;
	}

	void
	ArgumentsWidget::styleValue(void)
	{
#if 0
		if (isValid_) {
			table_->setStyleSheet("background-color:none;");
		}
		else {
			table_->setStyleSheet("background-color:red;");
		}
#endif
	}

#if 0
	void
	ArgumentsWidget::onTextChangedTextWidget(const QString& text)
	{
		if (!checkOn_) return;

		OpcUaByte accessLevel;
		isValid_ = checkValue();
		styleValue();
		bool rc;
		accessLevel = textWidget_->text().toInt(&rc);
		emit valueChanged(accessLevel, isValid_);
	    emit update();
	}
#endif

}


