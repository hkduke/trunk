#include "DeviceNoReceiveTreeWidget.h"
#include "treeitemminedata.h"
#include <qapplication>


DeviceNoReceiveTreeWidget::DeviceNoReceiveTreeWidget(QWidget* parent)
	:CustomTreeWidgetBase(parent)
{
}


DeviceNoReceiveTreeWidget::~DeviceNoReceiveTreeWidget(void)
{
}


void DeviceNoReceiveTreeWidget::mouseMoveEvent(QMouseEvent *event)
{
	
	if(event->buttons() == Qt::RightButton)
		return;
	if(event->buttons()==Qt::LeftButton)
	{
		int dragDistance=(event->pos()-m_startDragPoint).manhattanLength();
		if(dragDistance>QApplication::startDragDistance())
		{
			performDrag();
		}
	}
	QTreeWidget::mouseMoveEvent(event);
}

void DeviceNoReceiveTreeWidget::dragEnterEvent(QDragEnterEvent* event)
{
	
	//QWidget* source=qobject_cast<CustomTreeWidgetBase*>(event->source());
	//if(source)
	//{
	//	event->setDropAction(Qt::CopyAction);
	//}
	//event->accept();
}

void DeviceNoReceiveTreeWidget::dragMoveEvent(QDragMoveEvent* event)
{
	//QWidget* source =qobject_cast<CustomTreeWidgetBase*>(event->source());
	//if(source)
	//{
	//	const TreeItemMineData* pMimeData=(const TreeItemMineData*)(event->mimeData());
	//	const QTreeWidgetItem* item=pMimeData->DragItemData();
	//	QTreeWidgetItem* currentItem=this->itemAt(event->pos());
	//	if(currentItem==item)
	//	{
	//		event->ignore();
	//	}
	//	else
	//	{
	//		setCurrentItem(currentItem);
	//		event->setDropAction(Qt::CopyAction);
	//	}
	//	event->accept();
	//}
	
}

void DeviceNoReceiveTreeWidget::dropEvent(QDropEvent* event)
{
	//QWidget* source = qobject_cast<CustomTreeWidgetBase*>(event->source());
	//const TreeItemMineData* pMimeData=(const TreeItemMineData*)event->mimeData();
	//if(source)
	//{
	//	const QTreeWidgetItem* item=pMimeData->DragItemData();
	//	QTreeWidgetItem* pItem=item->clone();
	//	QTreeWidgetItem* currentItem=this->itemAt(event->pos());
	//	if(currentItem&&currentItem!=item)
	//	{
	//		currentItem->addChild(pItem);
	//	}
	//	else
	//	{
	//		this->addTopLevelItem(pItem);
	//	}
	//	event->setDropAction(Qt::CopyAction);
	//}
	//event->accept();
}