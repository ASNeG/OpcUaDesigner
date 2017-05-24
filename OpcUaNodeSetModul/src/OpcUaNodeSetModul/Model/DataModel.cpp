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

#include "OpcUaStackCore/Base/ObjectPool.h"
#include "OpcUaStackCore/Base/ConfigXml.h"
#include "OpcUaStackServer/NodeSet/NodeSetXmlParser.h"
#include "OpcUaStackServer/InformationModel/InformationModelNodeSet.h"
#include "OpcUaNodeSetModul/Model/DataModel.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{

	DataModel::DataModel(void)
	: informationModel_(constructSPtr<InformationModel>())
	{
	}

	DataModel::~DataModel(void)
	{
	}

	InformationModel::SPtr&
	DataModel::informationModel(void)
	{
		return informationModel_;
	}

	bool
	DataModel::loadStandardNodeSet(const std::string& standardNodeSetFileName)
	{
		bool rc;

		// parse node set file
		ConfigXml configXml;
		rc = configXml.parse(standardNodeSetFileName);
		if (!rc) {
			Log(Error, "parse node set file error")
			    .parameter("NodeSetFile", standardNodeSetFileName)
			    .parameter("ErrorMessage", configXml.errorMessage());
			return false;
		}

		// decode node set
	    NodeSetXmlParser nodeSetXmlParser;
	    rc = nodeSetXmlParser.decode(configXml.ptree());
		if (!rc) {
			Log(Error, "decode node set file error")
			    .parameter("NodeSetFile", standardNodeSetFileName);
			return false;
		}

		// create opc ua information model
		if (informationModel_.get() == nullptr) {
			informationModel_ = constructSPtr<InformationModel>();
		}
		rc = InformationModelNodeSet::initial(informationModel_, nodeSetXmlParser);
		if (!rc) {
			Log(Error, "create node set error")
			    .parameter("NodeSetFile", standardNodeSetFileName);
			return false;
		}

		informationModel_->checkForwardReferences();

		return true;
	}

	bool
	DataModel::writeNodeSet(const std::string& nodeSetFile)
	{
		// FIXME: todo
		return true;
	}

}

