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

#ifndef __OpcUaNodeSetModul_MainWindow_h__
#define __OpcUaNodeSetModul_MainWindow_h__

#include <QMainWindow>

#include <map>
#include <stdint.h>

namespace OpcUaNodeSet
{

	class NodeSetWindow
    : public QMainWindow
	{

	  Q_OBJECT

	  public:
		typedef std::map<uint32_t, NodeSetWindow*> Map;

		NodeSetWindow(QMainWindow* parentMainWindow);
		virtual ~NodeSetWindow(void);

		void modulName(const std::string& modulName);
		std::string modulName(void);
		void modulFile(const std::string& modulFile);
		std::string modulFile(void);

	  private:
		QMainWindow* parentMainWindow_;
		std::string modulName_;
		std::string modulFile_;
	};

}

#endif
