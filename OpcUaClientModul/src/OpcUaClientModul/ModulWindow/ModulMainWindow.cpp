/*
   Copyright 2016-2017 Samuel Huebl (samuel@huebl-sgh.de)

   Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
   Datei nur in Übereinstimmung mit der Lizenz erlaubt.
   Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

   Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
   erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
   GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

   Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
   im Rahmen der Lizenz finden Sie in der Lizenz.

   Autor: Samuel Huebl (samuel@huebl-sgh.de)
 */

#include <OpcUaClientModul/ModulWindow/ModulMainWindow.h>

namespace OpcUaClientModul
{
	ModulMainWindow::ModulMainWindow(QMainWindow* parentMainWindow)
	: QMainWindow()
	, modulName_("")
	, parentMainWindow_(parentMainWindow)
	{
	}

	ModulMainWindow::~ModulMainWindow()
	{
	}

	bool
	ModulMainWindow::create(void)
	{
		bool rc;

		setWindowTitle(QString("OpcUaClientModul - ModulMainWindow"));

		// TODO

		return true;
	}

	bool
	ModulMainWindow::open(void)
	{
		// TODO
		return false;
	}

	void
	ModulMainWindow::modulName(const std::string& modulName)
	{
		modulName_ = modulName;
	}

	std::string
	ModulMainWindow::modulName(void)
	{
		return modulName_;
	}
}
