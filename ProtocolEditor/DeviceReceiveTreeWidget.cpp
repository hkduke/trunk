#include "DeviceReceiveTreeWidget.h"
#include "treeitemminedata.h"
#include "DeviceNoReceiveTreeWidget.h"


DeviceReceiveTreeWidget::DeviceReceiveTreeWidget(QWidget* parent)
	:CustomTreeWidgetBase(parent)
{
}


DeviceReceiveTreeWidget::~DeviceReceiveTreeWidget(void)
{
}

void DeviceReceiveTreeWidget::dragEnterEvent(QDragEnterEvent* event)
{
	if(event->mouseButtons() == Qt::LeftButton)
	{
		QWidget* source=qobject_cast<DeviceNoReceiveTreeWidget*>(event->source());
		if(source)
		{
			event->setDropAction(Qt::CopyAction);
		}
		event->accept();
	}
}

void DeviceReceiveTreeWidget::dragMoveEvent(QDragMoveEvent* event)
{
	QWidget* source =qobject_cast<DeviceNoReceiveTreeWidget*>(event->source());
	
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

void DeviceReceiveTreeWidget::dropEvent(QDropEvent* event)
{
	QWidget* source = qobject_cast<DeviceNoReceiveTreeWidget*>(event->source());
	const TreeItemMineData* pMimeData=(const TreeItemMineData*)event->mimeData();

	if(source&&topLevelItem(0))
	{
		const QTreeWidgetItem* item=pMimeData->DragItemData();
		QTreeWidgetItem* pItem=item->clone();
		QTreeWidgetItem* currentItem=this->itemAt(event->pos());
		this->topLevelItem(0)->addChild(pItem);	
		pItem->setExpanded(true);
		QString msgName=item->text(0);
		xlDataManager::MessageStruct tempMessageStruct=m_dataManager->messageList[msgName];
		int numberCount=tempMessageStruct.propList.size();
		for(int i=0;i<numberCount;++i)
		{
			QTreeWidgetItem* secondItem=new QTreeWidgetItem(pItem);
			xlDataManager::PropStruct tempPropStruct=tempMessageStruct.propList.at(i);
			QString propStr=QString("%1  %2  %3  %4").arg(tempPropStruct.propName.c_str())
				.arg(tempPropStruct.propStyle.c_str()).arg(QString::number(tempPropStruct.propSize))
				.arg(tempPropStruct.propHint.c_str());
			secondItem->setText(0,propStr);
		}
		QString protName=topLevelItem(0)->text(0);
		m_dataManager->protList[protName].messages.append(msgName.toStdString());
		m_dataManager->protListChangeds();
		event->setDropAction(Qt::CopyAction);
	}
	event->accept();
}

void DeviceReceiveTreeWidget::setDataManager(xlDataManager* dataManager)
{
	m_dataManager=dataManager;
}
