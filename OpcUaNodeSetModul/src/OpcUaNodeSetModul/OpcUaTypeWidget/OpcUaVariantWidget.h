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

#ifndef __OpcUaNodeSet_OpcUaVariantWidget_h__
#define __OpcUaNodeSet_OpcUaVariantWidget_h__

#include <QWidget>

#include "OpcUaStackCore/BuildInTypes/OpcUaVariant.h"

class QLineEdit;

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{

	class OpcUaVariantWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		OpcUaVariantWidget(QWidget* parent = 0);
		virtual ~OpcUaVariantWidget(void);

		void enabled(bool enabled);
		bool isValid(void);
		void setSavedValue(OpcUaVariant& savedValue);
		void setDisplayValue(OpcUaVariant& displayValue);
		void getSavedValue(OpcUaVariant& savedValue);
		void getDisplayValue(OpcUaVariant& displayValue);
		bool acceptValue(void);
		void resetValue(void);

	  signals:
		void update(void);
		void selectDataType(void);

	  private slots:
		void onTextChanged(const QString& text);
		void onClicked(void);

	  private:
		bool checkValue(void);
		void styleValue(void);

		OpcUaVariant savedValue_;
		OpcUaVariant displayValue_;
		bool isValid_;
		bool checkOn_;

		QLineEdit* textWidget_;
	};

}

#endif
