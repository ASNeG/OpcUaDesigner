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

#ifndef __OpcUaNodeSet_OpcUaBoolean_h__
#define __OpcUaNodeSet_OpcUaBoolean_h__

#include <stdint.h>
#include "OpcUaStackCore/BuildInTypes/OpcUaNumberTypes.h"

#include <QWidget>

class QCheckBox;

namespace OpcUaNodeSet
{

	class OpcUaBooleanWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		OpcUaBooleanWidget(QWidget* parent = 0);
		virtual ~OpcUaBooleanWidget(void);

		bool isValid(void);
		void enabled(bool enabled);
		void setSavedValue(OpcUaStackCore::OpcUaBoolean& savedValue);
		void setDisplayValue(OpcUaStackCore::OpcUaBoolean& displayValue);
		void getSavedValue(OpcUaStackCore::OpcUaBoolean& savedValue);
		void getDisplayValue(OpcUaStackCore::OpcUaBoolean& displayValue);
		bool acceptValue(void);
		void resetValue(void);

	signals:
      void update(void);

	private slots:
	  void onStateChanged(int state);

	private:
	  bool checkValue(void);
	  void styleValue(void);

	  OpcUaStackCore::OpcUaBoolean savedValue_;
	  OpcUaStackCore::OpcUaBoolean displayValue_;
	  QCheckBox* checkboxWidget_;
	  bool isValid_;
	  bool checkOn_;
	};

}

#endif
