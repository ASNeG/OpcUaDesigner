/*
   Copyright 2016 Kai Huebl (kai@huebl-sgh.de)

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

#include <boost/filesystem.hpp>

#include "OpcUaGui/Application/Application.h"

#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaStackCore/Base/Config.h"
#include "OpcUaStackCore/Base/ConfigXml.h"
#include "OpcUaStackCore/Core/FileLogger.h"
#include "OpcUaStackCore/Utility/Environment.h"

using namespace OpcUaStackCore;

namespace OpcUaGui
{

	Application::Application(void)
	: errorString_("no error detected")
	, fileLogger_(new FileLogger())
	, libraryConfigPath_("")
	{
	}

	Application::~Application(void)
	{
		delete fileLogger_;
	}

	std::string
	Application::errorString(void) const
	{
		return errorString_;
	}

	Config*
	Application::config(void)
	{
		return config_;
	}

	std::string
	Application::libraryConfigPath(void) const
	{
		return libraryConfigPath_;
	}

	bool
	Application::parseConfig(const std::string& configFile)
	{
		// create CONFDIR directory
		auto configFileName = boost::filesystem::absolute(configFile).string();
		auto configFilePath = boost::filesystem::path(configFileName).parent_path().string();
		Environment::confDir(configFilePath);
		config_->alias("@CONF_DIR@", Environment::confDir());

		// parse configuration file
		config_ = Config::instance();
		ConfigXml configXml;
		if (!configXml.parse(configFile, true)) {
			errorString_ = configXml.errorMessage();
			return false;
		}

		// read application configuration
		boost::optional<Config> applConfig = config_->getChild("OpcUaDesigner.Application");
		if (!applConfig) {
			errorString_ = "parameter OpcUaDesigner.Application do not exist in configuration file";
		    return false;
		}
		if (!applConfig->getConfigParameter("ModulDirectory", libraryConfigPath_)) {
			errorString_ = "parameter OpcUaDesigner.Application.ModulDirectory do not exist in configuration file";
		    return false;
		}

		return true;
	}

	bool
	Application::initLogging(void)
	{
		boost::optional<Config> logConfig = config_->getChild("OpcUaDesigner.Logging.FileLogger");
		if (!logConfig) {
			fileLogger_->logFileName("OpcUaDesigner.log");
			OpcUaStackCore::Log::logIf(fileLogger_);
		    return true;
		}

		// read log file name
		std::string logFileName;
		logConfig->getConfigParameter("LogFileName", logFileName, "");
		if (logFileName == "") logFileName = "OpcUaServer.log";
		fileLogger_->logFileName(logFileName);

		// read max log file number
		uint32_t maxLogFileNumber;
		logConfig->getConfigParameter("MaxLogFileNumber", maxLogFileNumber, "20");
		fileLogger_->maxLogFileNumber(maxLogFileNumber);

		// read max log file size
		uint32_t maxLogFileSize;
		logConfig->getConfigParameter("MaxLogFileSize", maxLogFileSize, "5000000");
		fileLogger_->maxLogFileSize(maxLogFileSize);

		// read log level
		LogLevel logLevel;
		std::string logLevelString;
		logConfig->getConfigParameter("LogLevel", logLevelString, "Trace");
		if (logLevelString == "Error") logLevel = Error;
		else if (logLevelString == "Warning") logLevel = Warning;
		else if (logLevelString == "Info") logLevel = Info;
		else if (logLevelString == "Debug") logLevel = Debug;
		else logLevel = Trace;
		fileLogger_->logLevel(logLevel);

		// init logging
		OpcUaStackCore::Log::logIf(fileLogger_);

		return true;
	}

}

