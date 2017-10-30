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

#ifndef __OpcUaNodeSet_ValueRankWidget_h__
#define __OpcUaNodeSet_ValueRankWidget_h__

#include "OpcUaNodeSetModul/Base/NodeInfo.h"

#include <QWidget>

class QLineEdit;
class QComboBox;

namespace OpcUaNodeSet
{

	class ValueRankWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		ValueRankWidget(QWidget* parent = 0);
		virtual ~ValueRankWidget(void);

		void enabled(bool enabled);
		bool isValid(void);
		void nodeChange(NodeInfo* nodeInfo);
		void setSavedValue(OpcUaInt32& savedValue);
		void setDisplayValue(OpcUaInt32& displayValue);
		void getSavedValue(OpcUaInt32& savedValue);
		void getDisplayValue(OpcUaInt32& displayValue);
		bool acceptValue(void);
		void resetValue(void);

	signals:
      void update(void);

	private slots:
	  void onTextChangedTextWidget(const QString& text);
	  void onCurrentIndexChangedComboboxWidget(int index);

	private:
	  bool checkValue(void);
	  void styleValue(void);

	  QComboBox* comboBoxWidget_;
	  QLineEdit* textWidget_;
	  bool isValid_;
	  bool checkOn_;

	  OpcUaInt32 savedValue_;
	  OpcUaInt32 displayValue_;
	};

}

#endif
