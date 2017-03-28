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

#ifndef __OpcUaNodeSetModul_NodeSet_h__
#define __OpcUaNodeSetModul_NodeSet_h__

#include "OpcUaStackServer/InformationModel/InformationModel.h"

#include <iostream>

using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{

	class NodeSet
	{
	  public:
		NodeSet(void);
		virtual ~NodeSet(void);
		void start(void);

		InformationModel::SPtr informationModel(void);

		bool create(const std::string& fileName);
		bool open(const std::string& fileName);
		bool save(const std::string& fileName);

	  private:
		std::string fileName_;
		InformationModel::SPtr informationModel_;

		bool loadOpcUaNodeSet(const std::string& fileName);
	};

}

#endif
