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

#include "OpcUaNodeSetModul/MainWindow/NodeSetWindow.h"

namespace OpcUaNodeSet
{

	NodeSetWindow::NodeSetWindow(QMainWindow* parentMainWindow)
	: QMainWindow()
	, modulName_("")
	, modulFile_("")
	, parentMainWindow_(parentMainWindow)
	{
	}

	NodeSetWindow::~NodeSetWindow(void)
	{
	}

	void
	NodeSetWindow::modulName(const std::string& modulName)
	{
		modulName_ = modulName;
	}

	std::string
	NodeSetWindow::modulName(void)
	{
		return modulName_;
	}

	void
	NodeSetWindow::modulFile(const std::string& modulFile)
	{
		modulFile_ = modulFile;
	}

	std::string
	NodeSetWindow::modulFile(void)
	{
		return modulFile_;
	}

}

