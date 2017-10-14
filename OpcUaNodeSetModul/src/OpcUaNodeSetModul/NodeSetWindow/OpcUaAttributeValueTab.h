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

#ifndef __OpcUaNodeSet_OpcUaAttributeValueTab_h__
#define __OpcUaNodeSet_OpcUaAttributeValueTab_h__

#include <QWidget>

#include "OpcUaNodeSetModul/Base/NodeInfo.h"

class QLineEdit;

namespace OpcUaNodeSet
{

	class OpcUaAttributeValueTab
	: public QWidget
	{
		Q_OBJECT

	  public:
		OpcUaAttributeValueTab(QWidget* parent = 0);
		virtual ~OpcUaAttributeValueTab(void);

		void nodeChange(NodeInfo* nodeInfo);

	  private:
		void setAccessLevel(NodeInfo* nodeInfo);
		void setArrayDimensions(NodeInfo* nodeInfo);
		void setDataType(NodeInfo* nodeInfo);
		void setHistorizing(NodeInfo* nodeInfo);
		void setMinimumSamplingInterval(NodeInfo* nodeInfo);
		void setValue(NodeInfo* nodeInfo);
		void setValueRank(NodeInfo* nodeInfo);

		QLineEdit* accessLevelLineEdit_;
		QLineEdit* arrayDimensionsLineEdit_;
		QLineEdit* dataTypeLineEdit_;
		QLineEdit* historizingLineEdit_;
		QLineEdit* minimumSamplingIntervalLineEdit_;
		QLineEdit* valueLineEdit_;
		QLineEdit* valueRankLineEdit_;
	};

}

#endif
