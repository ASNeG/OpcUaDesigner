/*
 Copyright 2016-2017 Samuel Huebl (samuel@huebl-sgh.de)

 Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
 Datei nur in Übereinstimmung mit der Lizenz erlaubt.
 Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

 Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
 erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
 GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

 Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
 im Rahmen der Lizenz finden Sie in der Lizenz.

 Autor: Samuel Huebl (samuel@huebl-sgh.de)
 */

#ifndef __OpcUaClientModul_AttributeWidget_h__
#define __OpcUaClientModul_AttributeWidget_h__

#include <OpcUaClientModul/Base/BaseNode.h>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

#include "OpcUaClientModul/Base/BaseNode.h"
#include "OpcUaClientModul/Tools/OpcUaClientProvider.h"
#include "OpcUaClientModul/ModulWindow/NodeIdWidget.h"
#include "OpcUaClientModul/ModulWindow/NodeClassWidget.h"
#include "OpcUaClientModul/ModulWindow/BrowseNameWidget.h"
#include "OpcUaClientModul/ModulWindow/DescriptionWidget.h"
#include "OpcUaClientModul/ModulWindow/WriteMaskWidget.h"
#include "OpcUaClientModul/ModulWindow/UserWriteMaskWidget.h"
#include "OpcUaClientModul/ModulWindow/LineWidget.h"
#include "OpcUaClientModul/ModulWindow/ValueWidget.h"

namespace OpcUaClientModul
{

	class AttributeWidget
	: public QWidget
	{
	    Q_OBJECT

	  public:
		AttributeWidget(OpcUaClientProvider* client);
		virtual ~AttributeWidget();

	  public slots:
	  	void write(BaseNode* baseNode);
		void nodeChange(BaseNode* baseNode);

	  private:
		void readAttributesFromServer(BaseNode* baseNode);

		OpcUaClientProvider* client_;

		NodeIdWidget* nodeIdWidget_;
		NodeClassWidget* nodeClassWidget_;
		BrowseNameWidget* browseNameWidget_;
		DescriptionWidget* descriptionWidget_;
		WriteMaskWidget* writeMaskWidget_;
		UserWriteMaskWidget* userWriteMaskWidget_;
		ValueWidget* valueWidget_;
	};

} /* namespace OpcUaClientModul */

#endif /* __OpcUaClientModul_AttributeWidget_h__ */
