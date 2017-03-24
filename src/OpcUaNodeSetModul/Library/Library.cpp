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
	, handle_(1)
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
		std::cout << "library shutdown..." << std::endl;

		NodeSetWindow::Map::iterator it;
		for (it = mainWindowMap_.begin(); it != mainWindowMap_.end(); it++) {
			delete it->second;
		}
		mainWindowMap_.clear();
	}

	bool
	Library::startApplication(uint32_t& handle)
	{
		// FIXME: todo
		std::cout << "start application..." << std::endl;

		// get node set file name
		QString fileName = QFileDialog::getSaveFileName(
			NULL, tr("Erstelle neue NodeSet Datei"), QDir::homePath(), tr("Dokumente (*.xml)")
		);
		if (fileName.isNull()) {
			return false;
		}

		// use file name as project name
		QStringList parts1 = fileName.split("/");
		QString name = parts1.at(parts1.size()-1);
		name.replace(".xml", "");

		std::cout << name.toStdString() << std::endl;

		// create main window
		NodeSetWindow* nodeSetWindow = new NodeSetWindow(parentMainWindow());
		nodeSetWindow->modulFile(fileName.toStdString());
		nodeSetWindow->modulName(name.toStdString());
		nodeSetWindow->start();

		// show main window
		nodeSetWindow->resize(400,600);
		nodeSetWindow->show();

		// insert new main window into main window map
		handle = handle_;
		handle_++;
		mainWindowMap_.insert(std::make_pair(handle, nodeSetWindow));

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
		NodeSetWindow::Map::iterator it;
		it = mainWindowMap_.find(handle);
		if (it == mainWindowMap_.end()) return false;
		NodeSetWindow* mainWindow = it->second;

		if (name == ModulLibraryInterface::V_ModulName) {
			value.setValue(QString(mainWindow->modulName().c_str()));
			return true;
		}
		else if (name == ModulLibraryInterface::V_ModulFile) {
			value.setValue(QString(mainWindow->modulFile().c_str()));
			return true;
		}
		return false;
	}

}

extern "C" MYSHAREDLIB_EXPORT void  init(OpcUaGui::ModulLibraryInterface** modulLibraryInterface) {
    *modulLibraryInterface = new OpcUaNodeSet::Library();
    std::cout << "xxx..." << std::endl;
}


