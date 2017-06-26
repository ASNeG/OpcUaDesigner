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
#include "OpcUaStackServer/AddressSpaceModel/DataTypeNodeClass.h"
#include "OpcUaStackServer/AddressSpaceModel/ObjectTypeNodeClass.h"
#include "OpcUaStackServer/AddressSpaceModel/VariableTypeNodeClass.h"
#include "OpcUaStackServer/AddressSpaceModel/ReferenceTypeNodeClass.h"
#include "OpcUaStackServer/InformationModel/InformationModelManager.h"
#include "OpcUaStackServer/InformationModel/InformationModelAccess.h"
#include "OpcUaNodeSetModul/NodeSetWindow/OpcUaTreeWindow.h"
#include "OpcUaNodeSetModul/Dialog/NamespaceManagerDialog.h"
#include "OpcUaNodeSetModul/Dialog/ImportDialog.h"
#include "OpcUaNodeSetModul/Dialog/ExportDialog.h"
#include "OpcUaNodeSetModul/Dialog/CreateNodeDialog.h"

#include <QString>
#include <QWidget>
#include <QHeaderView>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QVariant>
#include <QMenu>
#include <QToolBar>

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	OpcUaTreeWindow::OpcUaTreeWindow(QWidget* parent)
	: QWidget()
	, rootItem_(NULL)
	, actItem_(NULL)
	, dataModel_(NULL)
	, newActionBlackList_()
	{
		QVBoxLayout* layout_ = new QVBoxLayout();

		//
		// create new black list
		//
		newActionBlackList_.insert(OpcUaNodeId(OpcUaId_RootFolder));
		newActionBlackList_.insert(OpcUaNodeId(OpcUaId_TypesFolder));
		newActionBlackList_.insert(OpcUaNodeId(OpcUaId_ViewsFolder));
		newActionBlackList_.insert(OpcUaNodeId(OpcUaId_Server));
		newActionBlackList_.insert(OpcUaNodeId(OpcUaId_ObjectTypesFolder));
		newActionBlackList_.insert(OpcUaNodeId(OpcUaId_VariableTypesFolder));
		newActionBlackList_.insert(OpcUaNodeId(OpcUaId_DataTypesFolder));
		newActionBlackList_.insert(OpcUaNodeId(OpcUaId_ReferenceTypesFolder));
		newActionBlackList_.insert(OpcUaNodeId(OpcUaId_EventTypesFolder));
		newActionBlackList_.insert(OpcUaNodeId(OpcUaId_XmlSchema_TypeSystem));
		newActionBlackList_.insert(OpcUaNodeId(OpcUaId_OPCBinarySchema_TypeSystem));

		//
		// create toolbar menu
		//
		createToolBarActions();
		tableToolBar_ = new QToolBar();
		tableToolBar_->addAction(manageNamespaceAction_);
		tableToolBar_->addAction(importAction_);
		tableToolBar_->addAction(exportAction_);
		layout_->addWidget(tableToolBar_);

		//
		// create opc ua tree
		//
		opcUaTree_ = new QTreeWidget();
		opcUaTree_->setMinimumWidth(300);
		opcUaTree_->header()->close();
		opcUaTree_->setContextMenuPolicy(Qt::CustomContextMenu);
		layout_->addWidget(opcUaTree_);

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
			rootItem_ = item;
		}
		else {
			parentItem->addChild(item);
		}

		// read childs of base node
		OpcUaNodeId nodeId;
		baseNode->getNodeId(nodeId);
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
		if(item == NULL) return;

		// delete children of node item
		while (item->childCount() > 0) {
			removeNode(item->child(0));
		}

		// delete node info
		QVariant v = item->data(0, Qt::UserRole);
		NodeInfo* nodeInfo = v.value<NodeInfo*>();
		delete nodeInfo;

		// delete node
		if (item == rootItem_) {
			delete opcUaTree_->takeTopLevelItem(opcUaTree_->indexOfTopLevelItem(item));
		}
		else {
			//opcUaTree_->removeItemWidget(item, 0);
			delete item->parent()->takeChild(item->parent()->indexOfChild(item));
		}
	}

	void
	OpcUaTreeWindow::onCurrentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previos)
	{
		if (current == NULL) return;

		QVariant v = current->data(0, Qt::UserRole);
		NodeInfo* nodeInfo = v.value<NodeInfo*>();
		emit nodeChanged(nodeInfo);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// toolbar menu
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	OpcUaTreeWindow::createToolBarActions(void)
	{
		manageNamespaceAction_ = new QAction("Manage namespace", this);
		manageNamespaceAction_->setIcon(QIcon(":images/Eye.png"));
		connect(manageNamespaceAction_, SIGNAL(triggered()), this, SLOT(onManageNamespaceAction()));

		importAction_ = new QAction("Import nodeset", this);
		importAction_->setIcon(QIcon(":images/Import.png"));
		connect(importAction_, SIGNAL(triggered()), this, SLOT(onImportAction()));

		exportAction_ = new QAction("Export nodeset", this);
		exportAction_->setIcon(QIcon(":images/Export.png"));
		connect(exportAction_, SIGNAL(triggered()), this, SLOT(onExportAction()));
	}

	void
	OpcUaTreeWindow::onManageNamespaceAction(void)
	{
		NamespaceManagerDialog namespaceManagerDialog(dataModel_);
		namespaceManagerDialog.exec();
	}

    void
    OpcUaTreeWindow::onImportAction(void)
	{
		ImportDialog importDialog(dataModel_);
		importDialog.exec();

		removeNode(rootItem_);
		show();
	}

    void
    OpcUaTreeWindow::onExportAction(void)
	{
		ExportDialog exportDialog(dataModel_);
		exportDialog.exec();
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
    	if (nodeInfo->nodeSetNamespace_.globalNamespaceVec().size() <= 1) return;

    	// check new action black list
    	OpcUaNodeId parentNodeId;
    	nodeInfo->baseNode_->getNodeId(parentNodeId);
	    std::set<OpcUaNodeId>::iterator it;
	    it = newActionBlackList_.find(parentNodeId);
	    if (it != newActionBlackList_.end()) return;

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
    OpcUaTreeWindow::onNewAction(void)
    {
	    // get node information
	    QVariant v1 = actItem_->data(0, Qt::UserRole);
	    NodeInfo* nodeInfo = v1.value<NodeInfo*>();
	    BaseNodeClass::SPtr baseNode = nodeInfo->baseNode_;

	    // get parent node id
	    OpcUaNodeId parentNodeId;
	    baseNode->getNodeId(parentNodeId);

	    InformationModelAccess ima(nodeInfo->informationModel_);
	    OpcUaNodeId dataType;
	    baseNode->getDataType(dataType);

#if 0
	    // handle BaseDataType
	    if (ima.isDataType(baseNode)) {
	        createNewDataType(nodeInfo);
	    	return;
	    }

	    // handle BaseObjectType
	    if (ima.isObjectType(baseNode)) {
	        createNewObjectType(nodeInfo);
	    	return;
	    }

	    // handle BaseVariableType
	    if (ima.isVariableType(baseNode)) {
	        createNewVariableType(nodeInfo);
	    	return;
	    }

	    // handle References
	    if (ima.isReferences(baseNode)) {
	        createNewReferences(nodeInfo);
	    	return;
	    }

	    // handle BaseEventType
	    if (ima.isBaseEventType(baseNode)) {
	    	createNewObjectType(nodeInfo);
	    	return;
	    }
#endif

	    CreateNodeDialog createNodeDialog(dataModel_, baseNode);
	    createNodeDialog.exec();
	    if (!createNodeDialog.isOk()) {
	    	return;
	    }

	    // get information from dialog class
	    NodeClassType nodeClassType;
	    OpcUaNodeId nodeId;
	    OpcUaLocalizedText displayName;
	    OpcUaQualifiedName browseName;
	    OpcUaNodeId referenceType;
	    OpcUaNodeId objectType;
	    OpcUaNodeId variableType;

	    createNodeDialog.getNodeClass(nodeClassType);
	    createNodeDialog.getNodeId(nodeId);
	    createNodeDialog.getDisplayName(displayName);
	    createNodeDialog.getBrowseName(browseName);
	    createNodeDialog.getReferenceType(referenceType);
	    createNodeDialog.getObjectType(objectType);
	    createNodeDialog.getVariableType(variableType);

	    // create new node
	    InformationModelManager imm(dataModel_->informationModel());
    	AddNodeRule addNodeRule;
    	addNodeRule.displayPath(nodeId);

    	switch (nodeClassType)
    	{
    		case NodeClassType_Object:
    		{
    		  	bool success = imm.addObjectNode(
    			    addNodeRule,
    			    parentNodeId,
    			    nodeId,
    			    displayName,
    			    browseName,
    			    referenceType,
    			    objectType
    			);
    			if (!success) {
    				QMessageBox msgBox;
    				msgBox.setText("create object instance error");
    				msgBox.exec();
    				return;
    			}
    			break;
    		}
    		case NodeClassType_Variable:
    		{
    	    	bool success = imm.addVariableNode(
    	    		addNodeRule,
    	    		parentNodeId,
    	    		nodeId,
    	    		displayName,
    	    		browseName,
    	    		referenceType,
    	    		variableType
    	    	);
    	    	if (!success) {
    				QMessageBox msgBox;
    				msgBox.setText("create variable instance error");
    				msgBox.exec();
    				return;
    	    	}
    			break;
    		}
    		case NodeClassType_ObjectType:
    		{
    			bool success = imm.addObjectTypeNode(
    				parentNodeId,
    				nodeId,
    				displayName,
    				browseName
    			);
       	    	if (!success) {
        			QMessageBox msgBox;
        			msgBox.setText("create object type error");
        			msgBox.exec();
        			return;
        	    }
    			break;
    		}
    		default:
    		{
    			std::string nodeClassTypeStr = NodeClass::toString(nodeClassType);
    			QMessageBox msgBox;
    			msgBox.setText(QString("create new node error, because node class %1 error").arg(nodeClassTypeStr.c_str()));
    			msgBox.exec();
    			return;
    		}
    	}

	    // added new node to tree view
	    BaseNodeClass::SPtr newBaseNode = dataModel_->informationModel()->find(nodeId);
	    addNode(
	    	dataModel_->informationModel(),
	    	actItem_,
	    	newBaseNode
	    );
	    actItem_->setExpanded(true);
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
    OpcUaTreeWindow::onDeleteAction(void)
    {
    	// FIXME: todo
    }

    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    //
    // private function
    //
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------
    std::string
    OpcUaTreeWindow::displayName(const std::string& prefix)
    {
       	uint32_t idx = 0;
        std::stringstream ss;
        do
        {
        	ss.str("");
        	ss << prefix << idx;

        	BaseNodeClass::SPtr baseNode;
        	baseNode = dataModel_->informationModel()->find(OpcUaNodeId(ss.str(),1));
        	if (baseNode.get() == NULL) {
        		return ss.str();
        	}

        	idx++;
        } while (true);
    }

    void
    OpcUaTreeWindow::createNewDataType(NodeInfo* parentNodeInfo)
    {
    	//
    	// find new data type name
    	//
    	std::string dataTypeName = displayName("DataType");
    	OpcUaNodeId nodeId(dataTypeName, 1);
    	OpcUaQualifiedName browseName(dataTypeName, 1);
    	OpcUaLocalizedText displayName("en", dataTypeName);
    	OpcUaLocalizedText description("en", "");

    	//
    	// create object type node
    	//
       	DataTypeNodeClass::SPtr dataTypeNodeClass = constructSPtr<DataTypeNodeClass>();
       	dataTypeNodeClass->setNodeId(nodeId);
       	dataTypeNodeClass->setBrowseName(browseName);
       	dataTypeNodeClass->setDisplayName(displayName);
       	dataTypeNodeClass->setDescription(description);
    	dataTypeNodeClass->setWriteMask(0);
    	dataTypeNodeClass->setUserWriteMask(0);

    	bool isAbstract = true;
        dataTypeNodeClass->setIsAbstract(isAbstract);

        //
        // insert data type node into information model
        //
        OpcUaNodeId parentNodeId;
        parentNodeInfo->baseNode_->getNodeId(parentNodeId);
        dataTypeNodeClass->referenceItemMap().add(ReferenceType_HasSubtype, false, parentNodeId);
        parentNodeInfo->baseNode_->referenceItemMap().add(ReferenceType_HasSubtype, true, nodeId);
        dataModel_->informationModel()->insert(dataTypeNodeClass);

        //
        // added new item
        //
		NodeInfo* nodeInfo = new NodeInfo();
		nodeInfo->baseNode_ = dataTypeNodeClass;
		nodeInfo->informationModel_ = dataModel_->informationModel();
		QVariant v;
		v.setValue(nodeInfo);

		QTreeWidgetItem* item = new QTreeWidgetItem();
		item->setText(0, displayName.text().value().c_str());
		item->setData(0, Qt::UserRole, v);
		item->setIcon(0, QIcon(":images/DataType.png"));
		actItem_->addChild(item);

		//
		// activate new item
		//
		opcUaTree_->setCurrentItem(item);
		actItem_ = item;
    }

    void
    OpcUaTreeWindow::createNewVariableType(NodeInfo* parentNodeInfo)
    {
       	//
        // find new data type name
        //
        std::string variableTypeName = displayName("VariableType");
        OpcUaNodeId nodeId(variableTypeName, 1);
        OpcUaQualifiedName browseName(variableTypeName, 1);
        OpcUaLocalizedText displayName("en", variableTypeName);
        OpcUaLocalizedText description("en", "");

        //
        // create variable type node
        //
        VariableTypeNodeClass::SPtr variableTypeNodeClass = constructSPtr<VariableTypeNodeClass>();
        variableTypeNodeClass->setNodeId(nodeId);
        variableTypeNodeClass->setBrowseName(browseName);
        variableTypeNodeClass->setDisplayName(displayName);
        variableTypeNodeClass->setDescription(description);
        variableTypeNodeClass->setWriteMask(0);
        variableTypeNodeClass->setUserWriteMask(0);

        bool isAbstract = true;
        variableTypeNodeClass->setIsAbstract(isAbstract);
        OpcUaNodeId dataType(OpcUaId_Double);
        variableTypeNodeClass->setDataType(dataType);
        //variableTypeNodeClass->setValueRank();

        //
        // insert data type node into information model
        //
        OpcUaNodeId parentNodeId;
        parentNodeInfo->baseNode_->getNodeId(parentNodeId);
        variableTypeNodeClass->referenceItemMap().add(ReferenceType_HasSubtype, false, parentNodeId);
        parentNodeInfo->baseNode_->referenceItemMap().add(ReferenceType_HasSubtype, true, nodeId);
        dataModel_->informationModel()->insert(variableTypeNodeClass);

        //
        // added new item
        //
    	NodeInfo* nodeInfo = new NodeInfo();
    	nodeInfo->baseNode_ = variableTypeNodeClass;
    	nodeInfo->informationModel_ = dataModel_->informationModel();
    	QVariant v;
    	v.setValue(nodeInfo);

    	QTreeWidgetItem* item = new QTreeWidgetItem();
    	item->setText(0, displayName.text().value().c_str());
    	item->setData(0, Qt::UserRole, v);
    	item->setIcon(0, QIcon(":images/ValueType.png"));
    	actItem_->addChild(item);

    	//
    	// activate new item
    	//
    	opcUaTree_->setCurrentItem(item);
    	actItem_ = item;
    }

    void
    OpcUaTreeWindow::createNewReferences(NodeInfo* parentNodeInfo)
    {
       	//
        // find new data type name
        //
        std::string referencesName = displayName("References");
        OpcUaNodeId nodeId(referencesName, 1);
        OpcUaQualifiedName browseName(referencesName, 1);
        OpcUaLocalizedText displayName("en", referencesName);
        OpcUaLocalizedText description("en", "");

        //
        // create reference node
        //
        ReferenceTypeNodeClass::SPtr referenceTypeNodeClass = constructSPtr<ReferenceTypeNodeClass>();
        referenceTypeNodeClass->setNodeId(nodeId);
        referenceTypeNodeClass->setBrowseName(browseName);
        referenceTypeNodeClass->setDisplayName(displayName);
        referenceTypeNodeClass->setDescription(description);
        referenceTypeNodeClass->setWriteMask(0);
        referenceTypeNodeClass->setUserWriteMask(0);

        bool isAbstract = true;
        referenceTypeNodeClass->setIsAbstract(isAbstract);
        bool symmetric = true;
        referenceTypeNodeClass->setSymmetric(symmetric);

        //
        // insert data type node into information model
        //
        OpcUaNodeId parentNodeId;
        parentNodeInfo->baseNode_->getNodeId(parentNodeId);
        referenceTypeNodeClass->referenceItemMap().add(ReferenceType_HasSubtype, false, parentNodeId);
        parentNodeInfo->baseNode_->referenceItemMap().add(ReferenceType_HasSubtype, true, nodeId);
        dataModel_->informationModel()->insert(referenceTypeNodeClass);

        //
        // added new item
        //
    	NodeInfo* nodeInfo = new NodeInfo();
    	nodeInfo->baseNode_ = referenceTypeNodeClass;
    	nodeInfo->informationModel_ = dataModel_->informationModel();
    	QVariant v;
    	v.setValue(nodeInfo);

    	QTreeWidgetItem* item = new QTreeWidgetItem();
    	item->setText(0, displayName.text().value().c_str());
    	item->setData(0, Qt::UserRole, v);
    	item->setIcon(0, QIcon(":images/ReferenceType.png"));
    	actItem_->addChild(item);

    	//
    	// activate new item
    	//
    	opcUaTree_->setCurrentItem(item);
    	actItem_ = item;
    }

}


