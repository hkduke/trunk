#include "customtreewidgetbase.h"
#include <QApplication>
#include "treeitemminedata.h"
#include<qdebug>
#include <QDrag>
CustomTreeWidgetBase::CustomTreeWidgetBase(QWidget*parent) : QTreeWidget(parent)
{
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->setAcceptDrops(true);
	this->setDragEnabled(true);
	this->setStyleSheet("QTreeWidget::item:selected{background-color:rgb(150,0,0)}");
}

CustomTreeWidgetBase::~CustomTreeWidgetBase()
{

}

void CustomTreeWidgetBase::mousePressEvent(QMouseEvent* event)
{
	m_startDragPoint=event->pos();
	QTreeWidget::mousePressEvent(event);
}

void CustomTreeWidgetBase::mouseReleaseEvent(QMouseEvent* event)
{
	QTreeWidget::mouseReleaseEvent(event);
}

void CustomTreeWidgetBase::mouseMoveEvent(QMouseEvent* event)
{
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

void CustomTreeWidgetBase::dragEnterEvent(QDragEnterEvent* event)
{

	QWidget* source=qobject_cast<CustomTreeWidgetBase*>(event->source());
	if(source)
	{
		event->setDropAction(Qt::CopyAction);
	}
	event->accept();
	
}

void CustomTreeWidgetBase::dragMoveEvent(QDragMoveEvent* event)
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

void CustomTreeWidgetBase::dropEvent(QDropEvent* event)
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

void CustomTreeWidgetBase::performDrag()
{
	QTreeWidgetItem* item=currentItem();
	if(item)
	{
		TreeItemMineData* mimeData=new TreeItemMineData;
		mimeData->setDragData("ItemMimeData",item);
		QDrag* drag=new QDrag(this);
		drag->setMimeData(mimeData);
		drag->setPixmap(this->style()->standardPixmap(QStyle::SP_ArrowLeft));
		drag->exec(Qt::CopyAction);
	}
}
