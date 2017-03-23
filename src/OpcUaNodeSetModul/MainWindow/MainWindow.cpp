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

#include "OpcUaNodeSetModul/MainWindow/MainWindow.h"

namespace OpcUaNodeSet
{

	MainWindow::MainWindow(QApplication* parent)
	: modulName_("")
	, modulFile_("")
	{
	}

	MainWindow::~MainWindow(void)
	{
	}

	void
	MainWindow::modulName(const std::string& modulName)
	{
		modulName_ = modulName;
	}

	std::string
	MainWindow::modulName(void)
	{
		return modulName_;
	}

	void
	MainWindow::modulFile(const std::string& modulFile)
	{
		modulFile_ = modulFile;
	}

	std::string
	MainWindow::modulFile(void)
	{
		return modulFile_;
	}

}

