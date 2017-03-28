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
#include "OpcUaNodeSetModul/Base/LibraryConfig.h"

using namespace OpcUaStackCore;

namespace OpcUaNodeSet
{

	LibraryConfig::LibraryConfig(void)
	: standardNodeSetFile_("")
	{
	}

	LibraryConfig::~LibraryConfig(void)
	{
	}

	bool
	LibraryConfig::readLibraryConfig(Config *config)
	{
		// get standard node set file name
		if (!config->getConfigParameter("OpcUaModul.ModulConfig.StandardNodeSetFile", standardNodeSetFile_)) {
			Log(Error, "missing element in configuration")
				.parameter("Element", "OpcUaModul.ModulConfig.StandardNodeSetFile")
				.parameter("FileName", config->configFileName());
		    return false;
		}

		return true;
	}

}
