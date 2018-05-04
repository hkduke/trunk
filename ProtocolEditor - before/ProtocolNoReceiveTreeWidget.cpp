#include "ProtocolNoReceiveTreeWidget.h"
#include "treeitemminedata.h"
#include <QApplication>
#include<QDrag>
ProtocolNoReceiveTreeWidget::ProtocolNoReceiveTreeWidget(QWidget* parent)
	:CustomTreeWidgetBase(parent)
{
	
}


ProtocolNoReceiveTreeWidget::~ProtocolNoReceiveTreeWidget(void)
{
}

void ProtocolNoReceiveTreeWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(currentIndex().row()==-1)
		return;
	if(this->currentItem()->data(0,Qt::UserRole)!="protocolName")
	{
		return;
	}
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

void ProtocolNoReceiveTreeWidget::dragEnterEvent(QDragEnterEvent* event)
{
	/*QWidget* source=qobject_cast<CustomTreeWidgetBase*>(event->source());
	if(source)
	{
		event->setDropAction(Qt::CopyAction);
	}
	event->accept();*/
}

void ProtocolNoReceiveTreeWidget::dragMoveEvent(QDragMoveEvent* event)
{
	/*QWidget* source =qobject_cast<CustomTreeWidgetBase*>(event->source());
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
	}*/
	
}

void ProtocolNoReceiveTreeWidget::dropEvent(QDropEvent* event)
{
	/*QWidget* source = qobject_cast<CustomTreeWidgetBase*>(event->source());
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
	event->accept();*/
}



void ProtocolNoReceiveTreeWidget::performDrag()
{
	QTreeWidgetItem* item=currentItem();
	
	if(item)
	{
		emit ItemMoving();
		TreeItemMineData* mimeData=new TreeItemMineData;
		mimeData->setDragData("ItemMimeData",item);
		QDrag* drag=new QDrag(this);
		drag->setMimeData(mimeData);
		drag->setPixmap(this->style()->standardPixmap(QStyle::SP_ArrowLeft));
		drag->exec(Qt::CopyAction);

		
	}
}

