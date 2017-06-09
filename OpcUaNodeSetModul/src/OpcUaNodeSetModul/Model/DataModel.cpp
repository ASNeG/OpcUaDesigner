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
	, nodeSetNamespace_()
	, notVisibleNamespaceSet_()
	, actNamespaceIndex_(0)
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

	NodeSetNamespace&
	DataModel::nodeSetNamespace(void)
	{
		return nodeSetNamespace_;
	}

	bool
	DataModel::namespaceVisible(const std::string& namespaceName)
	{
		VisibleNamespaceSet::iterator it;
		it = notVisibleNamespaceSet_.find(namespaceName);
		return it == notVisibleNamespaceSet_.end();
	}

	void
	DataModel::namespaceVisible(const std::string& namespaceName, bool visible)
	{
		VisibleNamespaceSet::iterator it;
		it = notVisibleNamespaceSet_.find(namespaceName);

		if (visible) {
			// remove from namespace set
			if (it == notVisibleNamespaceSet_.end()) return;
			notVisibleNamespaceSet_.erase(it);
		}
		else {
			// add to namespace set
			notVisibleNamespaceSet_.insert(namespaceName);
		}
	}

	void
	DataModel::actNamespaceIndex(uint16_t actNamespaceIndex)
	{
		actNamespaceIndex_ = actNamespaceIndex;
	}

	uint16_t
	DataModel::actNamespaceIndex(void)
	{
		return actNamespaceIndex_;
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
	DataModel::loadNodeSet(
		const std::string& nodeSetFileName
	)
	{
		bool rc;

		// parse node set file
		ConfigXml configXml;
		rc = configXml.parse(nodeSetFileName);
		if (!rc) {
			Log(Error, "parse node set file error")
			    .parameter("NodeSetFile", nodeSetFileName)
			    .parameter("ErrorMessage", configXml.errorMessage());
			return false;
		}

		// decode node set
	    NodeSetXmlParser nodeSetXmlParser;
	    rc = nodeSetXmlParser.decode(configXml.ptree());
		if (!rc) {
			Log(Error, "decode node set file error")
			    .parameter("NodeSetFile", nodeSetFileName);
			return false;
		}

		// create opc ua information model
		if (informationModel_.get() == nullptr) {
			informationModel_ = constructSPtr<InformationModel>();
		}
		rc = InformationModelNodeSet::initial(informationModel_, nodeSetXmlParser);
		if (!rc) {
			Log(Error, "create node set error")
			    .parameter("NodeSetFile", nodeSetFileName);
			return false;
		}

		informationModel_->checkForwardReferences();

		return true;
	}

	bool
	DataModel::writeNodeSet(
		const std::string& nodeSetFile,
		std::vector<std::string>& namespaceVec,
		bool empty
	)
	{
		bool success;

		// write nodes from information model into node set file
		NodeSetXmlParser nodeSetXmlParserWrite;

		if (!empty) {
			success = InformationModelNodeSet::initial(
				nodeSetXmlParserWrite,
				informationModel_,
				namespaceVec
			);
			if (!success) {
				Log(Error, "write node set file error - preprocessing")
					.parameter("NodeSetFile", nodeSetFile);
			}
		}

		ConfigXml configXmlWrite;
		success = nodeSetXmlParserWrite.encode(configXmlWrite.ptree());
		if (!success) {
			Log(Error, "write node set file error - encode")
				.parameter("NodeSetFile", nodeSetFile);
		}

		// write node set file
		success = configXmlWrite.write(nodeSetFile);
		if (!success) {
			Log(Error, "write node set file error")
				.parameter("NodeSetFile", nodeSetFile);
		}

	    //nodeSetXmlParser.nodeSetNamespace().clearGlobal();
		return true;
	}

}

