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

#ifndef __OpcUaNodeSet_ArgumentsWidget_h__
#define __OpcUaNodeSet_ArgumentsWidget_h__

#include "OpcUaNodeSetModul/Base/NodeInfo.h"

#include <QWidget>

class QLineEdit;
class QTableWidget;
class QTableWidgetItem;

namespace OpcUaNodeSet
{

	class ArgumentsWidget
	: public QWidget
	{
		Q_OBJECT

	  public:
		ArgumentsWidget(const std::string& title, QWidget* parent = 0);
		virtual ~ArgumentsWidget(void);

		bool isValid(void);
		void nodeChange(NodeInfo* nodeInfo, BaseNodeClass::SPtr& baseNode);
		void enabled(bool enabled);
		void getValue(OpcUaByte& accessLevel);

	signals:
	  void valueChanged(OpcUaByte& accessLevel, bool isValid);
      void update(void);

	private slots:
	  //void onTextChangedTextWidget(const QString& text);

	  //
  	  // toolbar menu
      //
      void onAddRowAction(void);
      void onDelRowAction(void);

	private:
	  bool checkValue(void);
	  void styleValue(void);
	  void createTableActions(void);

	  //
	  // table action
	  //
	  QToolBar* tableToolBar_;
	  QAction* addRowAction_;
	  QAction* delRowAction_;

	  std::string title_;
	  QTableWidget* tableWidget_;
	  bool isValid_;
	  bool checkOn_;
	};

}

#endif
