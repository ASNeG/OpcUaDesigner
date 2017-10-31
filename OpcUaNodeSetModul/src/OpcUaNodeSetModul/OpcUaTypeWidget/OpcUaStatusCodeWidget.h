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

#ifndef __OpcUaNodeSet_OpcUaStatusCodeWidget_h__
#define __OpcUaNodeSet_OpcUaStatusCodeWidget_h__

#include <QWidget>
#include <QStringList>
#include <QString>

#include "OpcUaStackCore/BuildInTypes/OpcUaStatusCode.h"

class QLineEdit;
class QComboBox;

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{

	class OpcUaStatusCodeWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		OpcUaStatusCodeWidget(QWidget* parent = 0);
		virtual ~OpcUaStatusCodeWidget(void);

		void enabled(bool enabled);
		bool isValid(void);
		void setSavedValue(OpcUaStatusCode& savedValue);
		void setDisplayValue(OpcUaStatusCode& displayValue);
		void getSavedValue(OpcUaStatusCode& savedValue);
		void getDisplayValue(OpcUaStatusCode& displayValue);
		bool acceptValue(void);
		void resetValue(void);

	  signals:
		void update(void);
		void selectDataType(void);

	  private slots:
		void onCurrentIndexChanged(const QString& text);

	  private:
		bool checkValue(void);
		void styleValue(void);

		OpcUaStatusCode savedValue_;
		OpcUaStatusCode displayValue_;
		bool isValid_;
		bool checkOn_;

		QStringList statusCodeList_;
		QComboBox* comboBoxWidget_;
	};

}

#endif
