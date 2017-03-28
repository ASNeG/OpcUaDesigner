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

#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaTreeWindow.h"
#include "OpcUaNodeSetModul/NodeSetWindow/NodeSet.h"

#include <QWidget>
#include <QHeaderView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QMessageBox>

namespace OpcUaNodeSet
{


	OpcUaTreeWindow::OpcUaTreeWindow(QWidget* parent)
	: QWidget()
	, rootItem_(NULL)
	, actItem_(NULL)
	, fileName_("")
	, nodeSet_()
	{
		// create opc ua tree
		opcUaTree_ = new QTreeWidget();
		opcUaTree_->header()->close();
		opcUaTree_->setContextMenuPolicy(Qt::CustomContextMenu);

		// show opc ua tree
		QVBoxLayout* layout_ = new QVBoxLayout();
		layout_->addWidget(opcUaTree_);
		setLayout(layout_);
	}

	OpcUaTreeWindow::~OpcUaTreeWindow(void)
	{
	}

	void
	OpcUaTreeWindow::standardNodeSetFileName(const std::string& standardNodeSetFileName)
	{
		standardNodeSetFileName_ = standardNodeSetFileName;
	}

	bool
	OpcUaTreeWindow::create(const std::string& fileName)
	{
		bool rc;

		fileName_ = fileName;

		// create standard opc ua node set
		nodeSet_.standardNodeSetFileName(standardNodeSetFileName_);
		rc = nodeSet_.create(fileName);
		if (!rc) {
			QMessageBox msgBox;
			msgBox.setText("The nodeset can not be created");
			msgBox.exec();
			return false;
		}

		// get opc ua information model
		InformationModel::SPtr informationModel = nodeSet_.informationModel();

		// get root element and create tree
		OpcUaNodeId rootNodeId(84);
		BaseNodeClass::SPtr baseNode = informationModel->find(rootNodeId);
		if (baseNode.get() == nullptr) {
			QMessageBox msgBox;
			msgBox.setText("The information model can not be displayed");
			msgBox.exec();
			return false;
		}
		addNode(informationModel, baseNode);

		return true;
	}

	bool
	OpcUaTreeWindow::open(const std::string& fileName)
	{
		fileName_ = fileName;

		// FIXME: todo
		return true;
	}

	void
	OpcUaTreeWindow::addNode(InformationModel::SPtr& informationModel, BaseNodeClass::SPtr& baseNode)
	{
		QIcon icon;
		NodeClassType nodeClass;
		baseNode->getNodeClass(nodeClass);
		switch (nodeClass)
		{
			case NodeClassType_Object:
			{
				icon = QIcon(":images/Folder.png");
				icon = QIcon(":images/Object.png");
				break;
			}
			case NodeClassType_Variable:
			{
				icon = QIcon(":images/Property.png");
				icon = QIcon(":images/Value.png");
				break;
			}
			case NodeClassType_Method:
			{
				icon = QIcon(":images/Function.png");
				break;
			}
			case NodeClassType_ObjectType:
			{
				icon = QIcon(":images/ObjectType.png");
				break;
			}
			case NodeClassType_VariableType:
			{
				icon = QIcon(":images/ValueType.png");
				break;
			}
			case NodeClassType_ReferenceType:
			{
				icon = QIcon(":images/ReferenceType.png");
				break;
			}
			case NodeClassType_DataType:
			{
				icon = QIcon(":images/DataType.png");
				break;
			}
			case NodeClassType_View:
			{
				icon = QIcon(":images/Folder.png");
				break;
			}
			default:
			{
				Log(Error, "invalid node class found")
					.parameter("NodeId", "xx")
					.parameter("NodeClass", (uint32_t)nodeClass);
				// FIXME: todo

				break;
			}
		}

		OpcUaLocalizedText displayName;
		baseNode->getDisplayName(displayName);

		// create tree item
		if (rootItem_ == NULL) {
			rootItem_ = new QTreeWidgetItem(opcUaTree_);
			rootItem_->setText(0, displayName.text().value().c_str());
			//rootItem_->setData(0, Qt::UserRole, v);
			rootItem_->setIcon(0, icon);
		}
	}

}


