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

#ifndef __OpcUaNodeSet_NodeIdWidget_h__
#define __OpcUaNodeSet_NodeIdWidget_h__

#include "OpcUaStackServer/InformationModel/InformationModel.h"
#include "OpcUaStackServer/NodeSet/NodeSetNamespace.h"

#include <QWidget>

class QLineEdit;
class QComboBox;

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{

	class NodeIdWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		NodeIdWidget(QWidget* parent = 0);
		virtual ~NodeIdWidget(void);

		void setValue(InformationModel::SPtr& informationModel);
		void setValue(NodeSetNamespace& nodeSetNamespace);
		void setValue(OpcUaNodeId& nodeId);
		void getValue(OpcUaNodeId& nodeId);
		bool isValid(void);

	  signals:
	    void valueChanged(OpcUaNodeId& nodeId, bool isValid);

	  private slots:


	  private:
		void show(void);

		OpcUaNodeId nodeId_;
		InformationModel::SPtr informationModel_;
		NodeSetNamespace* nodeSetNamespace_;
		bool isValid_;

		QComboBox* typeWidget_;
		QLineEdit* nodeIdWidget_;
		QComboBox* namespaceWidget_;
	};

}

#endif
