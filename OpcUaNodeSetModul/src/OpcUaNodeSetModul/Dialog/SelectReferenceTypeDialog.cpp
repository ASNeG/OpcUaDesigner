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


#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QHeaderView>

#include "OpcUaStackCore/BuildInTypes/OpcUaIdentifier.h"
#include "OpcUaStackServer/InformationModel/InformationModelAccess.h"
#include "OpcUaNodeSetModul/Dialog/SelectReferenceTypeDialog.h"

using namespace OpcUaStackCore;
using namespace OpcUaStackServer;

namespace OpcUaNodeSet
{


	SelectReferenceTypeDialog::SelectReferenceTypeDialog(DataModel* dataModel)
	: QDialog()
	, dataModel_(dataModel)
	, referenceType_(31)
	{
		this->setWindowTitle(QString("Select Reference Type Dialog"));
		QVBoxLayout* vBoxLayout = new QVBoxLayout();

		//
		// create opc ua tree
		//
		opcUaTree_ = new QTreeWidget();
		opcUaTree_->setMinimumWidth(300);
		opcUaTree_->setMinimumHeight(500);
		opcUaTree_->header()->close();
		opcUaTree_->setContextMenuPolicy(Qt::CustomContextMenu);
		vBoxLayout->addWidget(opcUaTree_);

		setLayout(vBoxLayout);

		//
		// actions
		//
		connect(
			opcUaTree_, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),
			this, SLOT(onItemDoubleClicked(QTreeWidgetItem*, int))
		);

		//
		// show model
		//
		showModel();
	}

	SelectReferenceTypeDialog::~SelectReferenceTypeDialog(void)
	{
	}

	OpcUaNodeId&
	SelectReferenceTypeDialog::referenceType(void)
	{
		return referenceType_;
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// dialog slots
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	SelectReferenceTypeDialog::onItemDoubleClicked(QTreeWidgetItem* item, int column)
	{
		if(item == NULL) return;

		// get node info
		QVariant v = item->data(0, Qt::UserRole);
		NodeInfo* nodeInfo = v.value<NodeInfo*>();

		nodeInfo->baseNode_->getNodeId(referenceType_);
		close();
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	//
	// private functions
	//
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	void
	SelectReferenceTypeDialog::showModel(void)
	{
		OpcUaNodeId referenceType(31);
		BaseNodeClass::SPtr baseNode = dataModel_->informationModel()->find(referenceType);
		addNode(dataModel_->informationModel(), NULL, baseNode);

		if (rootItem_ == NULL) return;
		opcUaTree_->expandItem(rootItem_);
	}

	void
	SelectReferenceTypeDialog::addNode(
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

		if (nodeClass != NodeClassType_ReferenceType) return;

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
			case NodeClassType_DataType:
			{
				icon = QIcon(":images/DataType.png");
				break;
			}
			case NodeClassType_ReferenceType:
			{
				icon = QIcon(":images/ReferenceType.png");
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

}

