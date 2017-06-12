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

#ifndef __OpcUaNodeSet_NodeClassWidget_h__
#define __OpcUaNodeSet_NodeClassWidget_h__

#include "OpcUaNodeSetModul/Base/NodeInfo.h"

#include <QWidget>
#include <QStringList>

class QComboBox;

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{

	class NodeClassWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		NodeClassWidget(QWidget* parent = 0);
		NodeClassWidget(QStringList& nodeClassList, QWidget* parent = 0);
		virtual ~NodeClassWidget(void);

		void setValue(QStringList& nodeClassList);
		void setValue(NodeClassType nodeClassType);
		void getValue(NodeClassType& nodeClassType);
		bool isValid(void);

	  public slots:
	    void onCurrentIndexChanged(int index);

	  signals:
		void valueChanged(NodeClassType& nodeClassType, bool isValid);

	  private:
		void createLayout(void);
		void showValue(void);
		bool checkValue(void);
		void styleValue(void);

		QComboBox* nodeClassWidget_;

		QStringList nodeClassList_;
		NodeClassType nodeClassType_;
		bool isValid_;
		bool checkOn_;
	};

}

#endif
