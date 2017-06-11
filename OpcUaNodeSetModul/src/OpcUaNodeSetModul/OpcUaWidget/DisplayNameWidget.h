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

#ifndef __OpcUaNodeSet_DisplayNameWidget_h__
#define __OpcUaNodeSet_DisplayNameWidget_h__

#include "OpcUaNodeSetModul/Base/NodeInfo.h"

#include <QWidget>

class QLineEdit;

namespace OpcUaNodeSet
{

	class DisplayNameWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		DisplayNameWidget(QWidget* parent = 0);
		virtual ~DisplayNameWidget(void);

		void setValue(OpcUaLocalizedText& displayName);
		void getValue(OpcUaLocalizedText& displayName);
		bool isValid(void);
		void nodeChange(NodeInfo* nodeInfo);

	  signals:
		void valueChanged(OpcUaLocalizedText& displayName, bool isValid);

	  private slots:
		void onTextChangedLocale(const QString& text);
		void onTextChangedText(const QString& text);

	  private:
		void showValue(void);
		bool checkValue(void);
		void styleValue(void);

		OpcUaLocalizedText displayName_;
		bool isValid_;
		bool checkOn_;

		QLineEdit* localeWidget_;
		QLineEdit* textWidget_;
	};

}

#endif
