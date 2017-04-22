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

#ifndef __OpcUaClientModul_ConnectionDialog_h__
#define __OpcUaClientModul_ConnectionDialog_h__

#include <QDialog>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>

namespace OpcUaClientModul
{

	class ConnectionDialog
	: public QDialog
	{
		Q_OBJECT

	  public:
		ConnectionDialog();
		virtual ~ConnectionDialog();

		bool isAccept(void);
		std::string getEndpointAddress(void);
		std::string getSessionName(void);

//	  public slots:
//	  	void accept(void);
//	  	void cancel(void);

	  private:
	  	bool accept_;

		QLineEdit* endpointAddress_;
		QLineEdit* sessionName_;
	};

} /* namespace OpcUaClientModul */

#endif /* __OpcUaClientModul_ConnectionDialog_h__ */
