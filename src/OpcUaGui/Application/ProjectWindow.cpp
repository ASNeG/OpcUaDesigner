/*
   Copyright 2016 Kai Huebl (kai@huebl-sgh.de)

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

#include "OpcUaGui/Application/ProjectWindow.h"

#include <QWidget>
#include <QTreeWidget>

namespace OpcUaGui
{

	ProjectWindow::ProjectWindow(QWidget* parent)
	: QMainWindow(parent)
	{
		 setWindowFlags(this->windowFlags() & ~Qt::Window);

		 setCentralWidget(new QTreeWidget());
		 resize(400, 400);
		 show();
	}

	ProjectWindow::~ProjectWindow(void)
	{
	}

}


