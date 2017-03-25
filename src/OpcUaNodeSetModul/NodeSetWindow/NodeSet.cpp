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

#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaStackCore/Base/ConfigXml.h"
#include "OpcUaStackServer/NodeSet/NodeSetXmlParser.h"
#include "OpcUaNodeSetModul/NodeSetWindow/NodeSet.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{

	NodeSet::NodeSet(void)
	{
	}

	NodeSet::~NodeSet(void)
	{
	}

	bool
	NodeSet::create(const std::string& fileName)
	{
		fileName_ = fileName;

		// FIXME: todo
		return false;
	}

	bool
	NodeSet::open(const std::string& fileName)
	{
		fileName_ = fileName;

		// FIXME: todo
		return false;
	}

	bool
	NodeSet::save(const std::string& fileName)
	{
		fileName_ = fileName;

		// FIXME: todo
		return false;
	}

	bool
	NodeSet::loadOpcUaNodeSet(const std::string& fileName)
	{
		bool rc;

		// parse node set file
		ConfigXml configXml;
		rc = configXml.parse(fileName);
		if (!rc) {
			Log(Error, "parse node set file error")
			    .parameter("NodeSetFile", fileName)
			    .parameter("ErrorMessage", configXml.errorMessage());
			return false;
		}

		// decode node set
	    NodeSetXmlParser nodeSetXmlParser;
	    rc = nodeSetXmlParser.decode(configXml.ptree());
		if (!rc) {
			Log(Error, "decode node set file error")
			    .parameter("NodeSetFile", fileName);
			return false;
		}

		// create opc ua information model
		informationModel_ = constructSPtr<InformationModel>();
		rc = InformationModelNodeSet::initial(informationModel_, nodeSetXmlParser);
		if (!rc) {
			Log(Error, "create node set error")
			    .parameter("NodeSetFile", fileName);
			return false;
		}

		informationModel_->checkForwardReferences();


#if 0
	    NodeSetNamespace& nodeSetNamespace = nodeSetXmlParser.nodeSetNamespace();
	    NamespaceVec& namespaceVec = nodeSetNamespace.localNamespaceVec();
	    NamespaceVec::iterator it;

	    for (it = namespaceVec.begin(); it != namespaceVec.end(); it++) {
	        uint16_t namespaceIndex = nodeSetNamespace.mapToGlobalNamespaceIndex(*it);

	        std::cout << "NamespaceUri: " << *it << std::endl;
	        std::cout << "mapToGlobalNamespaceIndex: " << namespaceIndex << std::endl;
	    }
#endif
		return false;
	}

}

