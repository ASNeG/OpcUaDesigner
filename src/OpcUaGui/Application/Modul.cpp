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
#include <iostream>

#include "OpcUaStackCore/Base/Log.h"
#include "OpcUaGui/Application/Modul.h"

using namespace OpcUaStackCore;

namespace OpcUaGui
{

	Modul::Modul(void)
	: modulConfigSet_()
	{
	}

	Modul::~Modul(void)
	{
	}

	ModulConfig::Set&
	Modul::modulConfigSet(void)
	{
		return modulConfigSet_;
	}

	bool
	Modul::initModuls(const std::string& modulDirectory)
	{
		// read all files in directory
		try {
		    boost::filesystem::directory_iterator endIt;
		    for (boost::filesystem::directory_iterator it(modulDirectory); it != endIt; it++) {
			    std::cout << "FILE=" << *it << std::endl;
		    }
		}
		catch (...)
		{
			Log(Error, "modul configuration directory error")
				.parameter("ModulDirectory", modulDirectory);
			return false;
		}

		return true;
	}

}

