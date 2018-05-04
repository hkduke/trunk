#include "xlreader.h"
#include <QDebug>

//xlReader::xlReader(QTreeWidget* treeWidget):treeWidget(treeWidget)
//{
//	//QStyle* style = treeWidget->style();
//	//bookMarkIcon.addPixmap(style->standardPixmap(QStyle::SP_FileIcon));
//}

xlReader::xlReader()
{

}

bool xlReader::read(QIODevice* device)
{
	xml.setDevice(device);
	if(xml.readNextStartElement())
	{
		if(xml.name() == "xml" && xml.attributes().value("version") == "1.0")
		{
			xlmManager->SetVersionInfo(xml.attributes().value("protocolVersion").toString());
			readXml();
		}
		else
		{
			xml.raiseError(QObject::tr("This file is not an xml version 1.0 file"));
		}
	}
	return !xml.error();
}

bool xlReader::ReadNextXml()
{
	return true;
}

QString xlReader::errorString() const
{
	return QObject::tr("%1\n line %2,colume %3")
		.arg(xml.errorString())
		.arg(xml.lineNumber())
		.arg(xml.columnNumber());
}


void xlReader::setxlDataManager(xlDataManager * manager)
{
	xlmManager=manager;
}

//void xlReader::readXml(QTreeWidget* item)
//{
//	Q_ASSERT(xml.isStartElement() && xml.name() =="xml");
//	QTreeWidgetItem* rootItem;
//	rootItem=new QTreeWidgetItem();
//	item->addTopLevelItem(rootItem);
//	rootItem->setText(0,QObject::tr("协议列表"));
//	while(xml.readNextStartElement())
//	{
//		if(xml.name() == "protocol")
//		{
//			readProt(rootItem);
//		}
//		else
//		{
//			xml.skipCurrentElement();
//		}
//	}
//}


void xlReader::readXml()
{
	Q_ASSERT(xml.isStartElement() && xml.name() =="xml");
	while(xml.readNextStartElement())
	{
		if(xml.name() == "protocol")
		{
			readProt();
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
}

void xlReader::readProt()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "protocol");
	xlDataManager::ProtStruct tempProt=xlDataManager::ProtStruct();
	while(xml.readNextStartElement())
	{
		if(xml.name() == "protocolName")
		{
			tempProt.ProtName=xml.readElementText().toStdString();
			xlmManager->m_protStrList.append(tempProt.ProtName.c_str());
		}
		else if(xml.name()=="protocolExt")
		{
			tempProt.ProtExt=xml.readElementText().toStdString();
		}
		else if(xml.name() == "message")
		{
			if(!tempProt.ProtName.empty())
			{
				readMessage(&tempProt);
			}

		}
		else
		{
			xml.skipCurrentElement();
		}
	}
	xlmManager->protList[tempProt.ProtName.c_str()]=tempProt;
}

//QTreeWidgetItem* xlReader::createChildItem(QTreeWidgetItem* item)
//{
//	QTreeWidgetItem* childItem;
//	if(item)
//	{
//		childItem=new QTreeWidgetItem(item);
//	}
//	else
//	{
//		childItem = new QTreeWidgetItem(treeWidget);
//
//	}
//	childItem->setData(0,Qt::UserRole,xml.name().toString());
//	return childItem;
//}
//读取顶层协议列表名称
//void xlReader::readProt(QTreeWidgetItem* item)
//{
//	Q_ASSERT(xml.isStartElement() && xml.name() == "protocol");
//	QTreeWidgetItem* protListitem=NULL;
//	while(xml.readNextStartElement())
//	{
//		if(xml.name() == "protocolName")
//		{
//			protListitem=createChildItem(item);
//			QString protListName=xml.readElementText();
//			protListitem->setText(0,protListName);
//			protListitem->setIcon(0,bookMarkIcon);
//		}
//		else if(xml.name() == "message")
//		{
//			if(protListitem)
//			{
//				readMessage(protListitem);
//			}
//
//		}
//		else
//		{
//			xml.skipCurrentElement();
//		}
//	}
//
//}


//读取协议名称
//void xlReader::readMessage(QTreeWidgetItem* item)
//{
//	Q_ASSERT(xml.isStartElement() && xml.name() == "message");
//	xlDataManager::MessageStruct tempMessage;
//
//	while(xml.readNextStartElement())
//	{
//		if(xml.name() == "messageName")
//		{
//			QString protString=xml.readElementText();
//			QTreeWidgetItem * normalItem = createChildItem(item);
//			normalItem->setText(0,protString);
//			normalItem->setIcon(0,bookMarkIcon);
//			qDebug()<<xlmManager->messageNameList<<protString;
//			if(-1==xlmManager-> messageNameList.indexOf(protString))
//			{
//				qDebug()<<"enter";
//				xlmManager->messageNameList.append(protString);
//				tempMessage.messageName=protString.toStdString();	
//			}
//			else
//			{
//				continue;
//			}
//		}
//		else if(xml.name() == "messageExt")
//		{
//			QString protString=xml.readElementText();
//			tempMessage.messageExt = protString.toStdString();
//		}
//		else if(xml.name() == "messageProp")
//		{
//			readMessagePro(&tempMessage);
//		}
//		else
//		{
//			xml.skipCurrentElement();
//		}
//	}
//	xlmManager->messageList[tempMessage.messageName.c_str()]=tempMessage;
//
//}

void xlReader::readMessage(xlDataManager::ProtStruct* prot)
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "message");
	xlDataManager::MessageStruct tempMessage;

	while(xml.readNextStartElement())
	{
		if(xml.name() == "messageName")
		{
			QString protString=xml.readElementText();
			prot->messages.append(protString.toStdString());		
			if(-1==xlmManager-> messageNameList.indexOf(protString))
			{
				qDebug()<<"enter";
				xlmManager->messageNameList.append(protString);
				tempMessage.messageName=protString.toStdString();	
			}
			else
			{
				continue;
			}
		}
		else if(xml.name() == "messageExt")
		{
			QString protString=xml.readElementText();
			tempMessage.messageExt = protString.toStdString();
		}
		else if(xml.name() == "messageProp")
		{
			readMessagePro(&tempMessage);
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
	xlmManager->messageList[tempMessage.messageName.c_str()]=tempMessage;

}

//读取属性
void xlReader::readMessagePro(xlDataManager::MessageStruct* protStruct)
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "messageProp");
	xlDataManager::PropStruct propStruct;
	while(xml.readNextStartElement())
	{
		QString propStr=xml.readElementText();
		if(xml.name() == "propName")
		{
			propStruct.propName =propStr.toStdString();
		}
		else if (xml.name() == "propStyle")
		{
			propStruct.propStyle =propStr.toStdString();
		}
		else if (xml.name() == "propSize")
		{
			propStruct.propSize =propStr.toInt();
		}
		else if (xml.name() == "propHint")
		{
			propStruct.propHint =propStr.toStdString();
		}
		else if (xml.name() == "propExt")
		{
			propStruct.propExt =propStr.toStdString();
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
	protStruct->propList.append(propStruct);
}
