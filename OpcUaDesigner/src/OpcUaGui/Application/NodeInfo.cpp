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

#include "OpcUaGui/Application/NodeInfo.h"

namespace OpcUaGui
{

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// ModulInfo
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	NodeInfo::NodeInfo(void)
	: modulConfig_()
	, applicationData_()
	, handle_(0)
	{
	}

	NodeInfo::~NodeInfo(void)
	{
	}

	void
	NodeInfo::modulConfig(ModulConfig::SPtr& modulConfig)
	{
		modulConfig_ = modulConfig;
	}

	ModulConfig::SPtr
	NodeInfo::modulConfig(void)
	{
		return modulConfig_;
	}

	void
	NodeInfo::handle(uint32_t handle)
	{
		handle_ = handle;
	}

	uint32_t
	NodeInfo::handle(void)
	{
		return handle_;
	}

	void
	NodeInfo::applicationData(ApplicationData::SPtr& applicationData)
	{
		applicationData_ = applicationData;
	}

	ApplicationData::SPtr
	NodeInfo::applicationData(void)
	{
		return applicationData_;
	}

}
