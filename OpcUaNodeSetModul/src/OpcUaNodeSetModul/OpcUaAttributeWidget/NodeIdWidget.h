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

#ifndef __OpcUaNodeSet_NodeIdWidget_h__
#define __OpcUaNodeSet_NodeIdWidget_h__

#include "OpcUaStackServer/InformationModel/InformationModel.h"
#include "OpcUaStackServer/NodeSet/NodeSetNamespace.h"

#include <QWidget>

class QLineEdit;
class QComboBox;

namespace OpcUaNodeSet
{

	class NodeIdWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		NodeIdWidget(QWidget* parent = 0);
		virtual ~NodeIdWidget(void);

		void setValue(OpcUaStackServer::InformationModel::SPtr& informationModel);
		void setValue(OpcUaStackServer::NodeSetNamespace& nodeSetNamespace);
		void setValue(OpcUaNodeId& nodeId);
		void getValue(OpcUaNodeId& nodeId);
		bool isValid(void);
		void enabled(bool enabled);

	  signals:
	    void valueChanged(OpcUaNodeId& nodeId, bool isValid);
	    void update(void);

	  private slots:
	    void onCurrentIndexChangedTypeWidget(int index);
	    void onCurrentIndexChangedNamespaceWidget(int index);
	    void onTextChanged(const QString& text);

	  private:
		void showValue(void);
		bool checkValue(void);
		void styleValue(void);

		OpcUaStackCore::OpcUaNodeId nodeId_;
		OpcUaStackServer::InformationModel::SPtr informationModel_;
		OpcUaStackServer::NodeSetNamespace* nodeSetNamespace_;
		bool isValid_;
		bool checkOn_;

		QComboBox* typeWidget_;
		QLineEdit* nodeIdWidget_;
		QComboBox* namespaceWidget_;
	};

}

#endif
