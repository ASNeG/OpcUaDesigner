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

#ifndef __OpcUaNodeSetModul_Library_h__
#define __OpcUaNodeSetModul_Library_h__

#include <QObject>

#include "OpcUaGui/ModulInterface/ModulLibraryInterface.h"

namespace OpcUaNodeSet
{

	class MYSHAREDLIB_EXPORT Library
	: public OpcUaGui::ModulLibraryInterface
	{
	  Q_OBJECT

	  public:
		Library(void);
		virtual ~Library(void);

		//- ModulInterface ----------------------------------------------------
		virtual QIcon* libModulIcon(void);
		//- ModulInterface ----------------------------------------------------

	  private:
	};


	class MYSHAREDLIB_EXPORT xxxx
	: public QObject
	{
		Q_OBJECT

	  public:
		xxxx(void) {}
		virtual ~xxxx(void) {}

      public slots:
        void startupLibrary(void) {}
        void shutdownLibrary(void) {}

      signals:

	};

}

#endif
