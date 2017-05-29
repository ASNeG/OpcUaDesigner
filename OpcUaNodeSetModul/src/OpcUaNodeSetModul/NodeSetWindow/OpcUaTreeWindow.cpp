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

#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackServer/InformationModel/InformationModelAccess.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaTreeWindow.h"

#include <QString>
#include <QWidget>
#include <QHeaderView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QVariant>
#include <QMenu>

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	OpcUaTreeWindow::OpcUaTreeWindow(QWidget* parent)
	: QWidget()
	, rootItem_(NULL)
	, actItem_(NULL)
	, dataModel_(NULL)
	{
		//
		// create opc ua tree
		//
		opcUaTree_ = new QTreeWidget();
		opcUaTree_->setMinimumWidth(300);
		opcUaTree_->header()->close();
		opcUaTree_->setContextMenuPolicy(Qt::CustomContextMenu);

		//
		// create actions
		//
		connect(
			opcUaTree_, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)),
			this, SLOT(onCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*))
		);
		//
		// actions
		//
		connect(
			opcUaTree_, SIGNAL(customContextMenuRequested(const QPoint&)),
		    this, SLOT(onCustomContextMenuRequested(const QPoint&))
		);

		// show opc ua tree
		QVBoxLayout* layout_ = new QVBoxLayout();
		layout_->addWidget(opcUaTree_);
		setLayout(layout_);
	}

	OpcUaTreeWindow::~OpcUaTreeWindow(void)
	{
	}

	void
	OpcUaTreeWindow::dataModel(DataModel* dataModel)
	{
		dataModel_ = dataModel;
	}

	bool
	OpcUaTreeWindow::show(void)
	{
		// get root element and create tree
		OpcUaNodeId rootNodeId(OpcUaId_RootFolder);
		BaseNodeClass::SPtr rootNode = dataModel_->informationModel()->find(rootNodeId);
		if (rootNode.get() == nullptr) {
			QMessageBox msgBox;
			msgBox.setText("The information model can not be displayed");
			msgBox.exec();
			return false;
		}

		// show nodes
		addNode(dataModel_->informationModel(), NULL, rootNode);
		return true;
	}

	void
	OpcUaTreeWindow::addNode(
		InformationModel::SPtr& informationModel,
		QTreeWidgetItem* parentItem,
		BaseNodeClass::SPtr& baseNode
	)
	{
		InformationModelAccess informationModelAccess(informationModel);
		OpcUaNodeId typeNodeId;
		QIcon icon;
		NodeClassType nodeClass;

		// get information from base node
		informationModelAccess.getType(baseNode, typeNodeId);
		baseNode->getNodeClass(nodeClass);

		switch (nodeClass)
		{
			case NodeClassType_Object:
			{
				OpcUaNodeId folderNodeId(OpcUaId_FolderType);

				if (typeNodeId == folderNodeId) {
					icon = QIcon(":images/Folder.png");
				}
				else {
					icon = QIcon(":images/Object.png");
				}
				break;
			}
			case NodeClassType_Variable:
			{
				OpcUaNodeId propertyNodeId(OpcUaId_PropertyType);

				if (typeNodeId == propertyNodeId) {
					icon = QIcon(":images/Property.png");
				} else {
					icon = QIcon(":images/Value.png");
				}
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
		NodeInfo* nodeInfo = new NodeInfo();
		nodeInfo->baseNode_ = baseNode;
		nodeInfo->informationModel_ = informationModel;
		QVariant v;
		v.setValue(nodeInfo);

		QTreeWidgetItem* item = new QTreeWidgetItem();
		item->setText(0, displayName.text().value().c_str());
		item->setData(0, Qt::UserRole, v);
		item->setIcon(0, icon);

		if (parentItem == NULL) {
			opcUaTree_->addTopLevelItem(item);
		}
		else {
			parentItem->addChild(item);
		}

		// read childs of base node
		BaseNodeClass::Vec baseNodeClassVec;
		if (!informationModelAccess.getChildHierarchically(baseNode, baseNodeClassVec)) {
			Log(Error, "hierarchical child access error")
				.parameter("NodeId", *baseNode->getNodeId());
			return;
		}

		BaseNodeClass::Vec::iterator it;
		for (it=baseNodeClassVec.begin(); it!=baseNodeClassVec.end(); it++) {
			BaseNodeClass::SPtr childBaseNode = *it;

			addNode(informationModel, item, childBaseNode);
		}
	}

	void
	OpcUaTreeWindow::removeNode(
		QTreeWidgetItem* item
	)
	{
		if(!item) return;

		QVariant v = item->data(0, Qt::UserRole);
		NodeInfo* nodeInfo = v.value<NodeInfo*>();
		delete nodeInfo;

		delete item->parent()->takeChild(item->parent()->indexOfChild(item));
	}

	void
	OpcUaTreeWindow::onCurrentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previos)
	{
		QVariant v = current->data(0, Qt::UserRole);
		NodeInfo* nodeInfo = v.value<NodeInfo*>();
		emit nodeChanged(nodeInfo);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// context menu
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	OpcUaTreeWindow::onCustomContextMenuRequested(const QPoint& pos)
	{
	    QMenu menu;

	    // get and check tree widget item
	    actItem_ = opcUaTree_->itemAt(pos);
	    if (actItem_ == NULL) {
	        return;
	    }

	    // get node information
	    QVariant v = actItem_->data(0, Qt::UserRole);
	    NodeInfo* nodeInfo = v.value<NodeInfo*>();

	    // create menu
	    createNewMenu(menu, nodeInfo);
	    createDeleteMenu(menu, nodeInfo);

	    // show menu
	    menu.exec(opcUaTree_->viewport()->mapToGlobal(pos));
	}

    void
    OpcUaTreeWindow::createNewMenu(QMenu& menu, NodeInfo* nodeInfo)
    {
    	if (nodeInfo->baseNode_.get() == NULL) return;

		// create modul config value
		QVariant v;
		v.setValue((void*)nodeInfo);

		QAction* action = new QAction("New", this);
		action->setIcon(QIcon(":images/New.png"));
		action->setData(v);
		menu.addAction(action);
		connect(action, SIGNAL(triggered()), this, SLOT(onNewAction()));
    }

    void
    OpcUaTreeWindow::createDeleteMenu(QMenu& menu, NodeInfo* nodeInfo)
    {
    	if (nodeInfo->baseNode_.get() == NULL) return;

    	OpcUaNodeId nodeId;
    	nodeInfo->baseNode_->getNodeId(nodeId);
    	if (nodeId.namespaceIndex() == 0) return;

		// create modul config value
		QVariant v;
		v.setValue((void*)nodeInfo);

		QAction* action = new QAction("Delete", this);
		action->setIcon(QIcon(":images/Delete.png"));
		action->setData(v);
		menu.addAction(action);
		connect(action, SIGNAL(triggered()), this, SLOT(onDeleteAction()));
    }

    void
    OpcUaTreeWindow::onNewAction(void)
    {
    	// FIXME: todo
    }

    void
    OpcUaTreeWindow::onDeleteAction(void)
    {
    	// FIXME: todo
    }

}


