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

#include "OpcUaClientModul/Dialog/ConnectionDialog.h"

namespace OpcUaClientModul
{

	ConnectionDialog::ConnectionDialog()
	: QDialog()
	, accept_(false)
	{
		QVBoxLayout* vBoxLayout = new QVBoxLayout();
		vBoxLayout->setMargin(0);

		QLabel* endpointAddressLabel = new QLabel("Endpoint Address");

		endpointAddress_ = new QLineEdit();
		endpointAddress_->setFixedWidth(350);
		endpointAddress_->setText("opc.tcp://127.0.0.1:8889");

		vBoxLayout->addWidget(endpointAddressLabel);
		vBoxLayout->addWidget(endpointAddress_);

		QLabel* sessionNameLabel = new QLabel("Session Name");

		sessionName_ = new QLineEdit();
		sessionName_->setFixedWidth(350);
		sessionName_->setText("urn:127.0.0.1:ASNeG.de:DesignerClient");

		vBoxLayout->addWidget(sessionNameLabel);
		vBoxLayout->addWidget(sessionName_);

		vBoxLayout->addStretch();

		QFormLayout form(this);
		form.addRow(vBoxLayout);

		QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
		form.addRow(&buttonBox);
		connect(&buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
		connect(&buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

		if (exec() == QDialog::Accepted) accept_ = true;
	}

	ConnectionDialog::~ConnectionDialog()
	{
	}

	bool
	ConnectionDialog::isAccept(void)
	{
		return accept_;
	}

	std::string
	ConnectionDialog::getEndpointAddress(void)
	{
		if (endpointAddress_ == NULL)
		{
			return "";
		}
		return endpointAddress_->text().toStdString();
	}

	std::string
	ConnectionDialog::getSessionName(void)
	{
		if (sessionName_ == NULL)
		{
			return "";
		}
		return sessionName_->text().toStdString();
	}

} /* namespace OpcUaClientModul */
