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

#ifndef __OpcUaClientModul_ConnectionInfoWidget_h__
#define __OpcUaClientModul_ConnectionInfoWidget_h__

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "OpcUaClientModul/Base/BaseNode.h"

namespace OpcUaClientModul
{
	class ConnectionInfoWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		ConnectionInfoWidget();
		virtual ~ConnectionInfoWidget();

		void nodeChange(BaseNode* baseNode);

	  private:
		QLabel* connectionInfo_;
		QLabel* connectionStatus_;
	};
}

#endif /* __OpcUaClientModul_ConnectionInfoWidget_h__ */
