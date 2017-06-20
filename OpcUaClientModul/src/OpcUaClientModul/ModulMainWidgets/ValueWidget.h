/*
 Copyright 2016-2017 Samuel Huebl (samuel@huebl-sgh.de)

 Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
 Datei nur in Übereinstimmung mit der Lizenz erlaubt.
 Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

 Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
 erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
 GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

 Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
 im Rahmen der Lizenz finden Sie in der Lizenz.

 Autor: Samuel Huebl (samuel@huebl-sgh.de)
 */

#ifndef __OpcUaClientModul_ValueWidget_h__
#define __OpcUaClientModul_ValueWidget_h__

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QPushButton>

#include "OpcUaClientModul/Base/BaseNode.h"
#include "OpcUaClientModul/ModulMainWidgets/LineWidget.h"

namespace OpcUaClientModul
{

	class ValueWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		ValueWidget();
		virtual ~ValueWidget();

		void nodeChange(BaseNode* baseNode);

	  public slots:
		void writeSignal();

	  signals:
	  	void write(BaseNode* baseNode);

	  private:
		QLineEdit* valueEditWidget_;
		QLabel* sourceTimestampWidget_;
		QLabel* serverTimestampWidget_;
		QVBoxLayout* vBoxLayout_;

		BaseNode* baseNode_;
	};

} /* namespace OpcUaClientModul */

#endif /* __OpcUaClientModul_ValueWidget_h__ */
