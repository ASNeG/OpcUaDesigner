/*
   Copyright 2016-2017 Kai Huebl (kai@huebl-sgh.de)

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
#include "OpcUaGui/Model/ApplicationData.h"

using namespace OpcUaStackCore;

namespace OpcUaGui
{

	ApplicationData::ApplicationData(void)
	: applicationName_("")
	, projectFile_("")
	{
	}

	ApplicationData::~ApplicationData(void)
	{
	}

	void
	ApplicationData::applicationName(const std::string& applicationName)
	{
		applicationName_ = applicationName;
	}

	std::string&
	ApplicationData::applicationName(void)
	{
		return applicationName_;
	}

	void
	ApplicationData::projectFile(const std::string& projectFile)
	{
		projectFile_ = projectFile;
	}

	std::string&
	ApplicationData::projectFile(void)
	{
		return projectFile_;
	}

	bool
	ApplicationData::encode(Config& config)
	{
		config.setValue("<xmlattr>.Name", applicationName_);
		config.setValue("<xmlattr>.File", projectFile_);
		return true;
	}

	bool
	ApplicationData::decode(Config& config)
	{
		// get name
		if (!config.getConfigParameter("<xmlattr>.Name", applicationName_)) {
			Log(Error, "element missing in application data")
				.parameter("Element", "Name");
			return false;
		}

		// get file
		if (!config.getConfigParameter("<xmlattr>.File", projectFile_)) {
			Log(Error, "element missing in application data")
				.parameter("Element", "File");
			return false;
		}

		return true;
	}

}


