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

#ifndef __OpcUaNodeSet_OpcUaNodeIdWidget_h__
#define __OpcUaNodeSet_OpcUaNodeIdWidget_h__

#include <QWidget>

#include "OpcUaStackServer/InformationModel/InformationModel.h"

#include "OpcUaNodeSetModul/Base/NodeInfo.h"

class QLineEdit;
class QPushButton;

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{

	class OpcUaNodeIdWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		OpcUaNodeIdWidget(QWidget* parent = 0);
		virtual ~OpcUaNodeIdWidget(void);

		void enabled(bool enabled);
		void informationModel(InformationModel::SPtr& informationModel);
		void setValue(OpcUaNodeId& nodeId);
		void getValue(OpcUaNodeId& nodeId);
		bool isValid(void);
		void acceptValue(void);
		void resetValue(void);

	  signals:
		void update(void);
		void selectDataType(void);

	  private slots:
		void onTextChanged(const QString& text);
		void onClicked(void);

	  private:
		void showValue(void);
		bool checkValue(void);
		void styleValue(void);
		void findNodeId(const std::string& displayName, OpcUaNodeId& typeNode);

		InformationModel::SPtr informationModel_;
		OpcUaNodeId nodeId_;
		OpcUaNodeId rootNodeId_;
		bool isValid_;
		bool checkOn_;

		QLineEdit* textWidget_;
		QPushButton* buttonWidget_;
	};

}

#endif
