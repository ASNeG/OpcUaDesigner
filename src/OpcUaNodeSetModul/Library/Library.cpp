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

#include "OpcUaNodeSetModul/Library/Library.h"

#include <QMainWindow>
#include <QIcon>
#include <iostream>

namespace OpcUaNodeSet
{

	Library::Library(void)
	: OpcUaGui::ModulLibraryInterface()
	{
	}

	Library::~Library(void)
	{
	}

	QIcon*
	Library::libModulIcon(void)
	{
		return new QIcon(":images/OpcUaNodeSet.png");
	}

	void
	Library::libStartup(void)
	{
		// FIXME: todo
		std::cout << "library startup..." << std::endl;
	}

	void
	Library::libShutdown(void)
	{
		// FIXME: todo
		std::cout << "library shutdown..." << std::endl;
	}

	bool
	Library::startApplication(uint32_t& handle)
	{
		// FIXME: todo
		std::cout << "start application..." << std::endl;
		return true;
	}

	bool
	Library::stopApplication(uint32_t handle)
	{
		// FIXME: todo
		std::cout << "stop application..." << std::endl;
		return true;
	}

	bool
	Library::getValue(uint32_t handle, Value name, QVariant& value)
	{
		if (name == ModulLibraryInterface::V_ModulName) {
			value.setValue(QString("MyOpcUaNodeSet"));
			return true;
		}
		else if (name == ModulLibraryInterface::V_ModulFile) {
			value.setValue(QString("MyOpcUaNodeSet.xml"));
			return true;
		}
		return false;
	}

}

extern "C" MYSHAREDLIB_EXPORT void  init(OpcUaGui::ModulLibraryInterface** modulLibraryInterface) {
    *modulLibraryInterface = new OpcUaNodeSet::Library();
    std::cout << "xxx..." << std::endl;
}


