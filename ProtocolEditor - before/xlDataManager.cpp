#include "xlDataManager.h"
#include <QMessageBox>
#include <QDebug>
xlDataManager::xlDataManager(QObject* parent)
{
	m_isDirty = false;
}


xlDataManager::~xlDataManager(void)
{
}


//检测message就是否存在
bool xlDataManager::MessageIsExsit(QString messageN)
{
	QMap<QString,MessageStruct>::const_iterator itor=messageList.find(messageN);
	if(itor!=messageList.constEnd())
	{
		return true;
	}
	return false;
}

bool xlDataManager::ProtocolIsExsit(QString protN)
{
	QMap<QString,ProtStruct>::const_iterator itor=protList.find(protN);
	if(itor!=protList.constEnd())
	{
		return true;
	}
	return false;
}

//向管理器中加message
void xlDataManager::addMessage()
{
		MessageStruct copystruct;
		copystruct.messageName="default";
		copystruct.messageExt="default";
		copystruct.propList.clear();
		messageNameList.append("default");
		messageList[copystruct.messageName.c_str()]=copystruct;
		qDebug()<<copystruct.messageExt.c_str();
		m_isDirty = true;
}

void xlDataManager::addProtocol()
{
	QMap<QString,ProtStruct> protList;
	ProtStruct tempProtocol;
	tempProtocol.ProtName="default";
	m_protStrList.append("default");
	tempProtocol.messages.clear();
	protList["default"]=tempProtocol;
	m_isDirty = true;
}

void xlDataManager::delMessage(QString messagedef)
{
	qDebug()<<messageList[messagedef].messageExt.c_str();
	messageList.take(messagedef);
	for(int i=0;i<m_protStrList.size();i++)
	{
		protList[m_protStrList.at(i)].messages.removeAll(messagedef.toStdString());
	}
	qDebug()<<messageList[messagedef].messageExt.c_str();
	m_isDirty = true;
}

void xlDataManager::updataMessage_messageName(QString oldMessageName,QString newMessageName)
{
	qDebug()<<oldMessageName<<newMessageName;
	MessageStruct tempMessage=messageList[oldMessageName];
	tempMessage.messageName=newMessageName.toStdString();
	messageNameList.replace(messageNameList.indexOf(oldMessageName),newMessageName);
	messageList.remove(oldMessageName);
	messageList[newMessageName]=tempMessage;
	ReplaceProtData(oldMessageName,newMessageName);
	emit messageChanged();
	emit ProtMessageNameChanged();
	m_isDirty = true;
}

void xlDataManager::ReplaceProtData(QString oldMessageName, QString newMessageName)
{
	QMap<QString,ProtStruct>::iterator itor=protList.begin();
	for(itor;itor!=protList.end();itor++)
	{
		for(int i=0;i<itor->messages.size();i++)
		{
			if(itor->messages.at(i).c_str()==oldMessageName)
			{
				itor->messages[i]=newMessageName.toStdString();
			}
		}
	}
	m_isDirty = true;
}

void xlDataManager::updateMessageTreeOnly(QString oldMessageName,QString NewMessageExt)
{
	messageList[oldMessageName].messageExt=NewMessageExt.toStdString();

	emit messageChanged();
	m_isDirty = true;
}

void xlDataManager::updataProtocol_ProtocolName(QString oldProtocolName,QString newProtocolName)
{
	xlDataManager::ProtStruct tempStruct=protList[oldProtocolName];
	tempStruct.ProtName=newProtocolName.toStdString();
	protList[newProtocolName]=tempStruct;
	m_protStrList.replace(m_protStrList.indexOf(oldProtocolName),newProtocolName);
	protList.take(oldProtocolName);
	emit ProtChanged();
	m_isDirty = true;
}

QStringList xlDataManager::GetMessagePropStringFormat(QString messageNamestr)
{
	QStringList messagePropList;
	MessageStruct tempMessageStruct=messageList[messageNamestr];
	int rowNumber=tempMessageStruct.propList.size();
	QString propStr;
	for(int i=0;i<rowNumber;i++)
	{
		PropStruct tempPropStruct=tempMessageStruct.propList.at(i);
		QString propStr=QString("%1  %2  %3  %4").arg(tempPropStruct.propName.c_str())
			.arg(tempPropStruct.propStyle.c_str()).arg(QString::number(tempPropStruct.propSize))
			.arg(tempPropStruct.propHint.c_str());
		messagePropList<<propStr;
	}

	return messagePropList;
}

void xlDataManager::UpDataProtocol()
{
	emit ProtChanged();
	m_isDirty = true;
}

void xlDataManager::protListChangeds()
{
	emit protListChanged();
	m_isDirty = true;
}
/*
	功能：获取当前打开协议的版本号
*/
QString xlDataManager::GetVersionInfo()
{
	return m_versionInfor;
}

void xlDataManager::SetVersionInfo(QString versionIn)
{
	m_versionInfor = versionIn;
}

bool xlDataManager::IsDirty()
{
	return m_isDirty;
}

void xlDataManager::ResetDirtyState()
{
	m_isDirty=false;
}

void xlDataManager::SetDirty()
{
	m_isDirty = true;
}
