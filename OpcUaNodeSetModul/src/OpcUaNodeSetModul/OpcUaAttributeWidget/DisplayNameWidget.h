/*
   Copyright 2017-2019 Kai Huebl (kai@huebl-sgh.de)

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

#include <QWidget>

#include "OpcUaStackCore/BuildInTypes/OpcUaLocalizedText.h"

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

		void setValue(OpcUaStackCore::OpcUaLocalizedText& displayName);
		void getValue(OpcUaStackCore::OpcUaLocalizedText& displayName);
		bool isValid(void);
		void enabled(bool enabled);

	  signals:
		void valueChanged(OpcUaLocalizedText& displayName, bool isValid);
		void update(void);

	  private slots:
		void onTextChangedLocale(const QString& text);
		void onTextChangedText(const QString& text);

	  private:
		void showValue(void);
		bool checkValue(void);
		void styleValue(void);

		OpcUaStackCore::OpcUaLocalizedText displayName_;
		bool isValid_;
		bool checkOn_;

		QLineEdit* localeWidget_;
		QLineEdit* textWidget_;
	};

}

#endif
