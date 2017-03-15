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

#ifndef __OpcUaGui_ModulLibraryInterface_h__
#define __OpcUaGui_ModulLibraryInterface_h__

#include <QObject>
#include <QtCore/QtGlobal>
#include <QApplication>

#if defined(MYSHAREDLIB_LIBRARY)
#  define MYSHAREDLIB_EXPORT Q_DECL_EXPORT
#else
#  define MYSHAREDLIB_EXPORT Q_DECL_IMPORT
#endif

namespace OpcUaGui
{

	class MYSHAREDLIB_EXPORT ModulLibraryInterface
	: public QObject
	{
		Q_OBJECT

	  public:
		ModulLibraryInterface(void)
		: application_(0)
		{}
		virtual ~ModulLibraryInterface(void) {}

		void application(QApplication* application) { application_ = application; }
		QApplication* application(void) { return application_; }

		virtual QIcon* modulIcon(void) = 0;

      public slots:
        void startupLibrary(void) {}
        void shutdownLibrary(void) {}

      signals:

      private:
        QApplication* application_;

	};

}

#endif
