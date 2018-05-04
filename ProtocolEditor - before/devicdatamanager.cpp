#include "devicdatamanager.h"
#include <QDebug>
DevicDataManager::DevicDataManager(QObject *parent)
	: QObject(parent)
{

}

DevicDataManager::~DevicDataManager()
{

}

bool DevicDataManager::DevIsExsit(QString devName)
{
	if(m_deviceList.find(devName)!=m_deviceList.constEnd())
	{
		return true;
	}
	return false;
}

QStringList DevicDataManager::GetMessagePropStringFormat(const MessageStruct msgStruct)
{
	QStringList messagePropList;
	int rowNumber=msgStruct.propList.size();
	QString propStr;
	for(int i=0;i<rowNumber;i++)
	{
		PropStruct tempPropStruct=msgStruct.propList.at(i);
		QString propStr=QString("%1  %2  %3  %4").arg(tempPropStruct.propName.c_str())
			.arg(tempPropStruct.propStyle.c_str()).arg(QString::number(tempPropStruct.propSize))
			.arg(tempPropStruct.propHint.c_str());
		messagePropList<<propStr;
	}

	return messagePropList;
}

void DevicDataManager::AddDev(QString devName)
{
	DevStruct tempStruct;
	tempStruct.deviceName=devName.toStdString();
	m_devNameList.append(devName);
	tempStruct.protList.clear();
	m_deviceList[devName]=tempStruct;
}

bool DevicDataManager::IsExitProt(QString devName,QString protName)
{
	for(int i=0;i<m_deviceList.value(devName).protList.size();i++)
	{
		if(m_deviceList.value(devName).protList.at(i).protocolName.c_str()==protName)
		{
			return true;
		}
	}
	return false;
}



bool DevicDataManager::IsExitMessage(QString m_oldDevName,QString m_oldProtName,QString oldMessageName)
{
	for(int i=0;i<this->m_deviceList.value(m_oldDevName).protList.size();i++)
	{
		if(this->m_deviceList.value(m_oldDevName).protList[i].protocolName.c_str()==m_oldProtName)
		{
			for(int j=0;j<this->m_deviceList.value(m_oldDevName).protList[i].messgeList.size();j++)
			{
				if(this->m_deviceList.value(m_oldDevName).protList[i].messgeList[j].messageName.c_str()==oldMessageName)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void DevicDataManager::UpdateAll()
{
		emit DataChanged();
}

void DevicDataManager::UpdateDevName(QString oldDevName,QString newDevName)
{
	DevStruct tempDevStruct = m_deviceList.value(oldDevName);
	tempDevStruct.deviceName=newDevName.toStdString();
	m_devNameList.replace(m_devNameList.indexOf(oldDevName),newDevName);

	m_deviceList.take(oldDevName);
	m_deviceList[newDevName]=tempDevStruct;
	emit DataChanged();
}

void DevicDataManager::UpdateExt(QString oldDevice,QString devExt)
{
	m_deviceList[oldDevice].deviceExt=devExt.toStdString();
	emit DataChanged();
}

void DevicDataManager::UpdateMsgName(QString devName,QString protName,QString oldName,QString newName)
{

}

bool DevicDataManager::MessageStruct::operator==(const MessageStruct& that)const
{
	return that.messageName==this->messageName
		&&that.messageExt==this->messageExt
		&&that.messageP==this->messageP
		&&that.propList==this->propList;
}

bool DevicDataManager::PropStruct::operator==(const PropStruct& that) const
{
	return this->propName==that.propName 
		&& this->propStyle==that.propStyle 
		&&this->propSize==that.propSize
		&&this->propHint==that.propHint
		&&this->propExt==that.propExt;
}

bool DevicDataManager::ProtStruct::operator==(const ProtStruct& that) const
{
	return this->protocolName==that.protocolName&&
	this->protocolExt==that.protocolExt&&
	this->messgeList==that.messgeList;
}
