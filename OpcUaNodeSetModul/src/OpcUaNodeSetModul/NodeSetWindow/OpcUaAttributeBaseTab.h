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

#ifndef __OpcUaNodeSet_OpcUaAttributeBaseTab_h__
#define __OpcUaNodeSet_OpcUaAttributeBaseTab_h__

#include <QWidget>

#include "OpcUaNodeSetModul/Base/NodeInfo.h"
#include "OpcUaNodeSetModul/OpcUaWidget/NodeIdWidget.h"
#include "OpcUaNodeSetModul/OpcUaWidget/NodeClassWidget.h"
#include "OpcUaNodeSetModul/OpcUaWidget/BrowseNameWidget.h"
#include "OpcUaNodeSetModul/OpcUaWidget/DisplayNameWidget.h"
#include "OpcUaNodeSetModul/OpcUaWidget/DescriptionWidget.h"

class QLineEdit;

namespace OpcUaNodeSet
{

	class OpcUaAttributeBaseTab
	: public QWidget
	{
		Q_OBJECT

	  public:
		OpcUaAttributeBaseTab(QWidget* parent = 0);
		virtual ~OpcUaAttributeBaseTab(void);

		void nodeChange(NodeInfo* nodeInfo);

	  private:
		void setWriteMask(NodeInfo* nodeInfo);
		void setUserWriteMask(NodeInfo* nodeInfo);

		NodeIdWidget* nodeIdWidget_;
		NodeClassWidget* nodeClassWidget_;
		BrowseNameWidget* browseNameWidget_;
		DisplayNameWidget* displayNameWidget_;
		DescriptionWidget* descriptionWidget_;
		QLineEdit* writeMaskLineEdit_;
		QLineEdit* userWriteMaskLineEdit_;
	};

}

#endif
