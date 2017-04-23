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

#include "OpcUaClientModul/Library/Library.h"

#include <QMainWindow>
#include <QIcon>

using namespace OpcUaClientModul;

namespace OpcUaNodeSet
{

	Library::Library(void)
	: OpcUaGui::ModulLibraryInterface()
	, client_(new OpcUaClientProvider())
	, monitorItemWindow_()
	, modulMainWindow_()
	{
	}

	Library::~Library(void)
	{
	}

	QIcon*
	Library::libModulIcon(void)
	{
		return new QIcon(":images/OpcUaClient.png");
	}

	bool
	Library::startApplication(uint32_t& handle)
	{
		std::cout << "start application..." << std::endl;

		// open connection dialog
		ConnectionDialog* dialog = new ConnectionDialog();

		if (!dialog->isAccept())
		{
			return false;
		}

		// create connection to OPC UA server
		// set endpointUrl and sessionName
		std::string endpointUrlStr = dialog->getEndpointAddress();
		client_->endpointUrl(endpointUrlStr);
		std::string sessionNameStr = dialog->getSessionName();
		client_->sessionName(sessionNameStr);

		// connect to server
		if (!client_->connectToServer())
		{
			return false;
		}

		// create main window
		modulMainWindow_ = new ModulMainWindow(parentMainWindow(), client_);
		modulMainWindow_->modulName("ModulMainWindow");

		if (!modulMainWindow_->create())
		{
			delete modulMainWindow_;
			client_->disconnectFromServer();
			return false;
		}

		// show main window
		modulMainWindow_->resize(400, 600);
		modulMainWindow_->show();

		// create monitor item window
		monitorItemWindow_ = new MonitorItemWindow(client_);

		// show main window
		monitorItemWindow_->resize(700, 400);
		monitorItemWindow_->show();

		// set connections
		connect(
				modulMainWindow_, SIGNAL(createNewMonitorItem(NodeInfo*)),
				monitorItemWindow_, SLOT(createNewMonitorItem(NodeInfo*))
		);
		connect(
				client_, SIGNAL(signalUpdateMonitoredItem(OpcUaUInt32, OpcUaDataValue&)),
				monitorItemWindow_, SLOT(updateMonitoredItem(OpcUaUInt32, OpcUaDataValue&))
		);

		return true;
	}

	bool
	Library::openApplication(uint32_t& handle)
	{
		// FIXME: todo
		std::cout << "open application..." << std::endl;
		return false;
	}

	bool
	Library::stopApplication(uint32_t handle)
	{
		std::cout << "stop application..." << std::endl;

		client_->disconnectFromServer();

		delete modulMainWindow_;
		delete monitorItemWindow_;

		return true;
	}

	bool
	Library::getValue(uint32_t handle, Value value, QVariant& variant)
	{
		// TODO andere value vergabe
		variant.setValue(QString("OpcUaClientModul"));
		return true;
	}

}

extern "C" MYSHAREDLIB_EXPORT void  init(OpcUaGui::ModulLibraryInterface** modulLibraryInterface) {
    *modulLibraryInterface = new OpcUaNodeSet::Library();
}


