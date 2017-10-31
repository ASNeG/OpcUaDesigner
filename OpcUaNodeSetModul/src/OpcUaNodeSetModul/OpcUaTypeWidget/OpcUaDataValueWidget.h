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

#ifndef __OpcUaNodeSet_OpcUaDataValueWidget_h__
#define __OpcUaNodeSet_OpcUaDataValueWidget_h__

#include <QWidget>

#include "OpcUaStackCore/BuildInTypes/OpcUaDataValue.h"

class QCheckBox;
class QDateTimeEdit;

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{

	class OpcUaStatusCodeWidget;

	class OpcUaDataValueWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		OpcUaDataValueWidget(QWidget* parent = 0);
		virtual ~OpcUaDataValueWidget(void);

		void enabled(bool enabled);
		bool isValid(void);
		void setSavedValue(OpcUaDataValue& savedValue);
		void setDisplayValue(OpcUaDataValue& displayValue);
		void getSavedValue(OpcUaDataValue& savedValue);
		void getDisplayValue(OpcUaDataValue& displayValue);
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

		OpcUaDataValue savedValue_;
		OpcUaDataValue displayValue_;
		bool isValid_;
		bool checkOn_;

		OpcUaStatusCodeWidget* statusCodeWidget_;

		QCheckBox* sourceTimeExistWidget_;
		QDateTimeEdit* sourceTimeValueWidget_;

		QCheckBox* serverTimeExistWidget_;
		QDateTimeEdit* serverTimeValueWidget_;

		QCheckBox* valueExistWidget_;
	};

}

#endif
