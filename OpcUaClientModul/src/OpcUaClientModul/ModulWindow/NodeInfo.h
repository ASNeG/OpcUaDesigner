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

#ifndef __OpcUaClientModul_NodeInfo_h__
#define __OpcUaClientModul_NodeInfo_h__

#include <QMetaType>

#include "OpcUaStackCore/ServiceSet/ReferenceDescription.h"

using namespace OpcUaStackCore;

namespace OpcUaClientModul
{

	class NodeInfo
	{
	  public:
		NodeInfo();
		virtual ~NodeInfo();

		ReferenceDescription::SPtr reference_; // TODO ReferenceDescription nicht mit abspeichern
		OpcUaLocalizedText::SPtr description_;
		OpcUaUInt32 writeMask_;
		OpcUaUInt32 userWriteMask_;
		OpcUaDataValue::SPtr dataValue_;
	};

} /* namespace OpcUaClientModul */

Q_DECLARE_METATYPE(OpcUaClientModul::NodeInfo*);

#endif /* __OpcUaClientModul_NodeInfo_h__ */
