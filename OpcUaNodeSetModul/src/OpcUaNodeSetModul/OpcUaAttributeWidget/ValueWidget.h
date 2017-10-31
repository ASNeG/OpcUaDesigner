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

#ifndef __OpcUaNodeSet_ValueWidget_h__
#define __OpcUaNodeSet_ValueWidget_h__

#include "OpcUaNodeSetModul/Base/NodeInfo.h"
#include "OpcUaNodeSetModul/OpcUaTypeWidget/OpcUaDataValueWidget.h"

#include <QWidget>

class QLineEdit;

namespace OpcUaNodeSet
{

	class ValueWidget
	: public OpcUaDataValueWidget
	{
		Q_OBJECT

	  public:
		ValueWidget(QWidget* parent = 0);
		virtual ~ValueWidget(void);

		void nodeChange(NodeInfo* nodeInfo);
	};

}

#endif
