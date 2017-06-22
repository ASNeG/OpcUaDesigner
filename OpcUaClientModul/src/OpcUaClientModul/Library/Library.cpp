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

	std::string
	Library::getFileExtension(void)
	{
		return "OpcUaClientModul.xml";
	}

	void
	Library::libStartup(void)
	{
		std::cout << "opcua client modul library startup..." << std::endl;
	}

	void
	Library::libShutdown(void)
	{
		std::cout << "opcua client modul library shutdown..." << std::endl;
	}

	bool
	Library::projectNew(uint32_t handle, const std::string& projectName, const std::string& projectFile)
	{
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

		// show monitor item window
		monitorItemWindow_->resize(700, 400);
		monitorItemWindow_->show();

		// set connections
		connect(
				modulMainWindow_, SIGNAL(signalCreateNewMonitorItem(BaseNode*)),
				monitorItemWindow_, SLOT(slotCreateNewMonitorItem(BaseNode*))
		);
		connect(
				client_, SIGNAL(signalUpdateMonitoredItem(OpcUaUInt32, OpcUaDataValue&)),
				monitorItemWindow_, SLOT(slotUpdateMonitoredItem(OpcUaUInt32, OpcUaDataValue&))
		);

		return true;
	}

	bool
	Library::projectOpen(uint32_t handle, const std::string& projectName, const std::string& projectFile)
	{
		// TODO
		return false;
	}

	bool
	Library::projectSave(uint32_t handle)
	{
		// TODO
		return false;
	}

	bool
	Library::projectSaveAs(uint32_t handle, const std::string& projectFile)
	{
		// TODO
		return false;
	}

	bool
	Library::projectRename(uint32_t handle, const std::string& projectName)
	{
		// TODO
		return false;
	}

	bool
	Library::projectReadyToClose(uint32_t handle)
	{
		// TODO
		return true;
	}

	bool
	Library::projectClose(uint32_t handle)
	{
		client_->disconnectFromServer();

		delete modulMainWindow_;
		delete monitorItemWindow_;

		return true;
	}

}

extern "C" MYSHAREDLIB_EXPORT void  init(OpcUaGui::ModulLibraryInterface** modulLibraryInterface) {
    *modulLibraryInterface = new OpcUaNodeSet::Library();
}


