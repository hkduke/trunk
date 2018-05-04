#include "ProtocolReceiveTreeWidget.h"
#include "treeitemminedata.h"
#include "ProtocolNoReceiveTreeWidget.h"
#include <QDebug>
#include <QMessageBox>
ProtocolReceiveTreeWidget::ProtocolReceiveTreeWidget(QWidget* parent)
	:CustomTreeWidgetBase(parent)
{
}


ProtocolReceiveTreeWidget::~ProtocolReceiveTreeWidget(void)
{
}

void ProtocolReceiveTreeWidget::dragEnterEvent(QDragEnterEvent* event)
{
	if(event->mouseButtons() == Qt::LeftButton)
	{
		QWidget* source=qobject_cast<ProtocolNoReceiveTreeWidget*>(event->source());
	
		if(source)
		{
		
			event->setDropAction(Qt::CopyAction);
		}
		event->accept();
	}
}

void ProtocolReceiveTreeWidget::dragMoveEvent(QDragMoveEvent* event)
{
	QWidget* source =qobject_cast<ProtocolNoReceiveTreeWidget*>(event->source());
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

void ProtocolReceiveTreeWidget::dropEvent(QDropEvent* event)
{
	QWidget* source = qobject_cast<ProtocolNoReceiveTreeWidget*>(event->source());
	const TreeItemMineData* pMimeData=(const TreeItemMineData*)event->mimeData();
	if (currentIndex().row() == -1)
	{
		return;
	}
	if(source && currentItem()->data(0,Qt::UserRole).toString()=="port")
	{
		if(this->topLevelItem(0))
		{
			const QTreeWidgetItem* item=pMimeData->DragItemData();
			qDebug() << this->topLevelItem(0)->text(0) << currentItem()->text(0) << item->text(0);
			if(m_devManager->IsExitProt(this->topLevelItem(0)->text(0),currentItem()->text(0),item->text(0)))
			{
				QMessageBox::information(this, QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("有相同协议存在，请删除后重新加入"));
				return;
			}
			
			QTreeWidgetItem* pItem=item->clone();
			QTreeWidgetItem* currentItem=this->itemAt(event->pos());
			currentItem->addChild(pItem);
			xlDataManager::ProtStruct tempProtStruct=m_dataManager->protList.value(item->text(0));
			DevicDataManager::ProtStruct devProtStruct;
			devProtStruct.protocolName=tempProtStruct.ProtName;
			devProtStruct.protocolExt=tempProtStruct.ProtExt;
			for(int i=0;i<tempProtStruct.messages.size();i++)
			{
				xlDataManager::MessageStruct temMsg=m_dataManager->messageList.
					value(tempProtStruct.messages.at(i).c_str()); 
				DevicDataManager::MessageStruct devMsg;
				devMsg.messageName=temMsg.messageName;
				devMsg.messageExt=temMsg.messageExt;
				devMsg.messageP=QString::fromLocal8Bit("未定").toStdString();
				for(int j=0;j<temMsg.propList.size();j++)
				{
					xlDataManager::PropStruct tempPropStruct=temMsg.propList.at(j);
					DevicDataManager::PropStruct devPropStruct;
					devPropStruct.propName=tempPropStruct.propName;
					devPropStruct.propSize=tempPropStruct.propSize;
					devPropStruct.propStyle=tempPropStruct.propStyle;
					devPropStruct.propExt=tempPropStruct.propExt;
					devPropStruct.propHint=tempPropStruct.propHint;
					devMsg.propList.append(devPropStruct);
				}
				devProtStruct.messgeList.append(devMsg);
			}
			for (auto m = m_devManager->m_deviceList[topLevelItem(0)->text(0)].portList.begin();
				m != m_devManager->m_deviceList[topLevelItem(0)->text(0)].portList.end(); m++)
			{
				if (m->portName.c_str() == this->currentItem()->text(0))
				{
					m->protList << devProtStruct;
				}
			}
		
			event->setDropAction(Qt::CopyAction);
			m_devManager->UpdateAll();
		}
	}
	event->accept();	
	emit DragMoveFinished();
}

void ProtocolReceiveTreeWidget::SetDataManager(DevicDataManager* devManager)
{
	m_devManager=devManager;
}

void ProtocolReceiveTreeWidget::SetModeManager(xlDataManager* dataManager)
{
	m_dataManager=dataManager;
}
