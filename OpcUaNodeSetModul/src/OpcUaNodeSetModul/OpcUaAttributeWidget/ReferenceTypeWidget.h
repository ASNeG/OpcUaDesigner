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

#ifndef __OpcUaNodeSet_ReferenceTypeWidget_h__
#define __OpcUaNodeSet_ReferenceTypeWidget_h__

#include <QWidget>

#include "OpcUaStackServer/InformationModel/InformationModel.h"

class QLineEdit;
class QPushButton;

namespace OpcUaNodeSet
{

	class ReferenceTypeWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		ReferenceTypeWidget(QWidget* parent = 0);
		virtual ~ReferenceTypeWidget(void);

		void setValue(OpcUaStackServer::InformationModel::SPtr& informationModel);
		void setValue(OpcUaStackCore::OpcUaNodeId& referenceType);
		void getValue(OpcUaStackCore::OpcUaNodeId& referenceType);
		bool isValid(void);

	  signals:
		void valueChanged(OpcUaStackCore::OpcUaNodeId& referenceType, bool isValid);
		void selectReferenceType(void);

	  private slots:
		void onTextChanged(const QString& text);
		void onClicked(void);

	  private:
		void showValue(void);
		bool checkValue(void);
		void styleValue(void);
		void findNodeId(const std::string& displayName, OpcUaStackCore::OpcUaNodeId& typeNode);

		OpcUaStackServer::InformationModel::SPtr informationModel_;
		OpcUaStackCore::OpcUaNodeId referenceType_;
		bool isValid_;
		bool checkOn_;

		QLineEdit* textWidget_;
		QPushButton* buttonWidget_;
	};

}

#endif
