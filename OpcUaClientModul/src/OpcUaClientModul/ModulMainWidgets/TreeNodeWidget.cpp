/*
 Copyright 2016-2017 Samuel Huebl (samuel@huebl-sgh.de)

 Lizenziert gemäß Apache Licence Version 2.0 (die „Lizenz“); Nutzung dieser
 Datei nur in Übereinstimmung mit der Lizenz erlaubt.
 Eine Kopie der Lizenz erhalten Sie auf http://www.apache.org/licenses/LICENSE-2.0.

 Sofern nicht gemäß geltendem Recht vorgeschrieben oder schriftlich vereinbart,
 erfolgt die Bereitstellung der im Rahmen der Lizenz verbreiteten Software OHNE
 GEWÄHR ODER VORBEHALTE – ganz gleich, ob ausdrücklich oder stillschweigend.

 Informationen über die jeweiligen Bedingungen für Genehmigungen und Einschränkungen
 im Rahmen der Lizenz finden Sie in der Lizenz.

 Autor: Samuel Huebl (samuel@huebl-sgh.de)
 */

#include "OpcUaClientModul/ModulMainWidgets/TreeNodeWidget.h"

namespace OpcUaClientModul
{

	TreeNodeWidget::TreeNodeWidget(OpcUaClientProvider* client)
	: QWidget()
	, client_(client)
	{
		// create opc ua tree
		opcUaTree_ = new QTreeWidget();
		opcUaTree_->setMinimumWidth(300);
		opcUaTree_->header()->close();
		opcUaTree_->setContextMenuPolicy(Qt::CustomContextMenu);

		connect(
			opcUaTree_, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),
			this, SLOT(myItemDoubleClicked(QTreeWidgetItem*, int))
		);
		connect(
			opcUaTree_, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
			this, SLOT(myItemClicked(QTreeWidgetItem*, int))
		);

		// show opc ua tree
		QVBoxLayout* layout_ = new QVBoxLayout();
		layout_->addWidget(opcUaTree_);
		setLayout(layout_);
	}

	TreeNodeWidget::~TreeNodeWidget()
	{
	}

	bool
	TreeNodeWidget::create(void)
	{
		std::cout << "create tree node widget" << std::endl;

		OpcUaLocalizedText displayName;
		displayName.set("", "RootFolder");

		OpcUaQualifiedName qualifiedName;
		qualifiedName.set("RootFolder", (OpcUaInt16) 0);

		BaseNode* baseNode = new BaseNode();
		baseNode->nodeId().set((OpcUaInt32) 84, (OpcUaUInt16) 0);
		baseNode->displayName(displayName);
		baseNode->typeDefinition()->set(OpcUaId_FolderType);
		baseNode->browseName(qualifiedName);

		QVariant v;
		v.setValue(baseNode);

		QIcon icon = createQIcon(NodeClassType_Object, baseNode->typeDefinition());

		QTreeWidgetItem* item = new QTreeWidgetItem();
		item->setText(0, displayName.text().value().c_str());
		item->setData(0, Qt::UserRole, v);
		item->setIcon(0, icon);

		opcUaTree_->addTopLevelItem(item);
		opcUaTree_->setContextMenuPolicy(Qt::CustomContextMenu);

		connect(
				opcUaTree_, SIGNAL(customContextMenuRequested(const QPoint&)),
				this, SLOT(prepareMenu(const QPoint&))
		);

		std::cout << "create tree node widget finished" << std::endl;

		return true;
	}

	void
	TreeNodeWidget::myItemDoubleClicked(QTreeWidgetItem* parentItem, int row)
	{
		if (parentItem->childCount() == 0)	// FIXME muss über OPC Variable geprüft werden...
		{
			browseNextElements(parentItem);
		}
	}

	void
	TreeNodeWidget::browseNextElements(QTreeWidgetItem* parentItem)
	{
		std::cout << "browse next elements" << std::endl;

		QVariant v = parentItem->data(0, Qt::UserRole);
		BaseNode* baseNode = v.value<BaseNode*>();

		OpcUaNodeId::SPtr nodeId = baseNode->nodeIdSPtr();

		OpcUaStatusCode sc;
		ReferenceDescriptionArray::SPtr references;
		sc = client_->syncBrowse(nodeId, references);

		if (sc == Success)
		{
			std::cout << "add nodes for parent node " << nodeId->toString() << std::endl;
			addNode(parentItem, references);
		}

		std::cout << "browse next elements finished" << std::endl;
	}

	void
	TreeNodeWidget::addNode(QTreeWidgetItem* parentItem, ReferenceDescriptionArray::SPtr& references)
	{
		std::cout << "add new nodes" << std::endl;

		for (uint32_t idx=0; idx<references->size(); idx++)
		{
			ReferenceDescription::SPtr refDescription;
			references->get(idx, refDescription);

			OpcUaLocalizedText displayName = refDescription->displayName();

			BaseNode* baseNode = new BaseNode(refDescription);
			QVariant v;
			v.setValue(baseNode);

			QIcon icon = createQIcon(refDescription->nodeClass(), refDescription->typeDefinition());

			QTreeWidgetItem* item = new QTreeWidgetItem();
			item->setText(0, displayName.text().value().c_str());
			item->setData(0, Qt::UserRole, v);
			item->setIcon(0, icon);

			parentItem->addChild(item);

			std::cout << "addChild " << displayName.text().value() << std::endl;
		}

		std::cout << "add new nodes finished" << std::endl;
	}

	QIcon
	TreeNodeWidget::createQIcon(NodeClassType nodeClass, OpcUaExpandedNodeId::SPtr typeExpNodeId)
	{
		QIcon icon;

		OpcUaNodeId typeNodeId;
		typeNodeId.nodeIdValue(typeExpNodeId->nodeIdValue());
		typeNodeId.namespaceIndex(typeExpNodeId->namespaceIndex());

		switch (nodeClass)
		{
			case NodeClassType_Object:
			{
				OpcUaNodeId folderNodeId(OpcUaId_FolderType);

				if (typeNodeId == folderNodeId)
				{
					icon = QIcon(":images/Folder.png");
				} else
				{
					icon = QIcon(":images/Object.png");
				}
				break;
			}
			case NodeClassType_Variable:
			{
				OpcUaNodeId propertyNodeId(OpcUaId_PropertyType);

				if (typeNodeId == propertyNodeId)
				{
					icon = QIcon(":images/Property.png");
				} else
				{
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
				Log(Error, "invalid node class found").parameter("NodeId", "xx").parameter(
						"NodeClass", (uint32_t) nodeClass);
				break;
			}
		}

		return icon;
	}

	void
	TreeNodeWidget::myItemClicked(QTreeWidgetItem* item, int row)
	{
		QVariant v = item->data(0, Qt::UserRole);
		BaseNode* baseNode = v.value<BaseNode*>();
		emit nodeChanged(baseNode);
	}

	void
	TreeNodeWidget::prepareMenu(const QPoint& pos)
	{
		QTreeWidgetItem* item = opcUaTree_->itemAt(pos);

		QVariant v = item->data(0, Qt::UserRole);
		BaseNode* baseNode = v.value<BaseNode*>();

		QMenu menu(this);
		TreeMenuHandler* menuHandler = new TreeMenuHandler(pos);

		QAction* attributeAction = new QAction(QIcon(":images/DataType.png"), tr("Attribute"), this);
		connect(attributeAction, SIGNAL(triggered()), menuHandler, SLOT(handleMenuActionAttribute()));
		connect(menuHandler, SIGNAL(signalMenuActionAttribute(QPoint&)), this, SLOT(menuActionAttribute(QPoint&)));
		menu.addAction(attributeAction);

		if (item->childCount() == 0) // FIXME: doppelter code
		{
			QAction* browseAction = new QAction(QIcon(":images/OpcUaClient.png"), tr("Browse"), this);
			connect(browseAction, SIGNAL(triggered()), menuHandler, SLOT(handleMenuActionBrowse()));
			connect(menuHandler, SIGNAL(signalMenuActionBrowse(QPoint&)), this, SLOT(menuActionBrowse(QPoint&)));
			menu.addAction(browseAction);
		}

		if (baseNode->nodeClass() == NodeClassType_Variable)
		{
			QAction* monitorAction = new QAction(QIcon(":images/Value.png"), tr("Monitor"), this);
			connect(monitorAction, SIGNAL(triggered()), menuHandler, SLOT(handleMenuActionMonitor()));
			connect(menuHandler, SIGNAL(signalMenuActionMonitor(QPoint&)), this, SLOT(menuActionMonitor(QPoint&)));
			menu.addAction(monitorAction);
		}

		menu.exec(opcUaTree_->mapToGlobal(pos));
	}

	void
	TreeNodeWidget::menuActionMonitor(QPoint& pos)
	{
		QTreeWidgetItem* item = opcUaTree_->itemAt(pos);
		QVariant v = item->data(0, Qt::UserRole);
		BaseNode* baseNode = v.value<BaseNode*>();
		emit signalCreateNewMonitorItem(baseNode);
	}

	void
	TreeNodeWidget::menuActionBrowse(QPoint& pos)
	{
		QTreeWidgetItem* item = opcUaTree_->itemAt(pos);
		browseNextElements(item);
	}

	void
	TreeNodeWidget::menuActionAttribute(QPoint& pos)
	{
		QTreeWidgetItem* item = opcUaTree_->itemAt(pos);
		QVariant v = item->data(0, Qt::UserRole);
		BaseNode* baseNode = v.value<BaseNode*>();
		emit nodeChanged(baseNode);
	}

} /* namespace OpcUaClientModul */
