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
#include <QString>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QVariant>

#include <iostream>

namespace OpcUaNodeSet
{

	Library::Library(void)
	: OpcUaGui::ModulLibraryInterface()
	, mainWindowMap_()
	, libraryConfig_()
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

	std::string
	Library::getFileExtension(void)
	{
		return "NodeSet.xml";
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
		std::cout << "library shutdown..." << std::endl;

		NodeSetWindow::Map::iterator it;
		for (it = mainWindowMap_.begin(); it != mainWindowMap_.end(); it++) {
			delete it->second;
		}
		mainWindowMap_.clear();
	}


	bool
	Library::projectNew(uint32_t handle, const std::string& projectName, const std::string& projectFile)
	{
		// read modul configuration
		if (!libraryConfig_.readLibraryConfig(config())) {
			return false;
		}

		// create main window
		NodeSetWindow* nodeSetWindow = new NodeSetWindow(parentMainWindow());
		nodeSetWindow->libraryConfig(&libraryConfig_);

		if (!nodeSetWindow->projectNew(handle, projectName, projectFile)) {
			delete nodeSetWindow;
			return false;
		}

		// show main window
		nodeSetWindow->resize(1200,600);
		nodeSetWindow->show();

		// insert new main window into main window map
		mainWindowMap_.insert(std::make_pair(handle, nodeSetWindow));

		return true;
	}

	bool
	Library::projectOpen(uint32_t handle, const std::string& projectName, const std::string& projectFile)
	{
		// read modul configuration
		if (!libraryConfig_.readLibraryConfig(config())) {
			return false;
		}

		// create main window
		NodeSetWindow* nodeSetWindow = new NodeSetWindow(parentMainWindow());
		nodeSetWindow->libraryConfig(&libraryConfig_);

		if (!nodeSetWindow->projectOpen(handle, projectName, projectFile)) {
			delete nodeSetWindow;
			return false;
		}

		// show main window
		nodeSetWindow->resize(1200,600);
		nodeSetWindow->show();

		// insert new main window into main window map
		mainWindowMap_.insert(std::make_pair(handle, nodeSetWindow));

		return true;
	}

	bool
	Library::projectSave(uint32_t handle)
	{
		// find main window
		NodeSetWindow::Map::iterator it;
		it = mainWindowMap_.find(handle);
		if (it == mainWindowMap_.end()) return false;
		NodeSetWindow* mainWindow = it->second;

		// save
		return mainWindow->projectSave(handle);
	}

	bool
	Library::projectSaveAs(uint32_t handle, const std::string& projectFile)
	{
		// find main window
		NodeSetWindow::Map::iterator it;
		it = mainWindowMap_.find(handle);
		if (it == mainWindowMap_.end()) return false;
		NodeSetWindow* mainWindow = it->second;

		// saveAS
		return mainWindow->projectSaveAs(handle, projectFile);
	}

	bool
	Library::projectRename(uint32_t handle, const std::string& projectName)
	{
		// find main window
		NodeSetWindow::Map::iterator it;
		it = mainWindowMap_.find(handle);
		if (it == mainWindowMap_.end()) return false;
		NodeSetWindow* mainWindow = it->second;

		// rename
		return mainWindow->projectRename(handle, projectName);
	}

	bool
	Library::projectReadyToClose(uint32_t handle)
	{
		// find main window
		NodeSetWindow::Map::iterator it;
		it = mainWindowMap_.find(handle);
		if (it == mainWindowMap_.end()) return true;
		NodeSetWindow* mainWindow = it->second;

		return mainWindow->projectReadyToClose(handle);
	}

	bool
	Library::projectClose(uint32_t handle)
	{
		NodeSetWindow::Map::iterator it;
		it = mainWindowMap_.find(handle);
		if (it == mainWindowMap_.end()) return false;
		NodeSetWindow* mainWindow = it->second;

		// remove element from main window map
		mainWindowMap_.erase(it);

		// close main window
		delete mainWindow;
		return true;
		//return mainWindow->close();
	}

}

extern "C" MYSHAREDLIB_EXPORT void  init(OpcUaGui::ModulLibraryInterface** modulLibraryInterface) {
    *modulLibraryInterface = new OpcUaNodeSet::Library();
}


