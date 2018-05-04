#include "DeviceTreeWidget.h"
#include "treeitemminedata.h"
#include "devicemanagerwidget.h"

DeviceTreeWidget::DeviceTreeWidget(QWidget* parent)
	:CustomTreeWidgetBase(parent)
{
}


DeviceTreeWidget::~DeviceTreeWidget(void)
{
}


void DeviceTreeWidget::dragEnterEvent(QDragEnterEvent *event)
{
	QWidget* source=qobject_cast<CustomTreeWidgetBase*>(event->source());
	if(source)
	{
		event->setDropAction(Qt::CopyAction);
	}
	event->accept();
}

void DeviceTreeWidget::dragMoveEvent(QDragMoveEvent *event)
{
	QWidget* source =qobject_cast<CustomTreeWidgetBase*>(event->source());
	if(source)
	{
		const TreeItemMineData* pMimeData=(const TreeItemMineData*)(event->mimeData());
		const QTreeWidgetItem* item=pMimeData->DragItemData();
		QTreeWidgetItem* currentItem=this->itemAt(event->pos());
		if(currentItem==item)
		{
			event->ignore();
		}
		else
		{
			setCurrentItem(currentItem);
			event->setDropAction(Qt::CopyAction);
		}
		event->accept();
	}
}

void DeviceTreeWidget::dropEvent(QDropEvent *event)
{
	QWidget* source = qobject_cast<CustomTreeWidgetBase*>(event->source());
	const TreeItemMineData* pMimeData=(const TreeItemMineData*)event->mimeData();
	if(source)
	{
		const QTreeWidgetItem* item=pMimeData->DragItemData();
		QTreeWidgetItem* pItem=item->clone();
		QTreeWidgetItem* currentItem=this->itemAt(event->pos());
		if(currentItem&&currentItem!=item)
		{
			currentItem->addChild(pItem);
		}
		else
		{
			this->addTopLevelItem(pItem);
		}
		event->setDropAction(Qt::CopyAction);
	}
	event->accept();
}