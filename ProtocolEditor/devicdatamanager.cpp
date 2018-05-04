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
	tempStruct.portList.clear();
	m_deviceList[devName]=tempStruct;
}

bool DevicDataManager::IsExitProt(QString devName, QString portName, QString protName)
{
	for (int i = 0; i < this->m_deviceList.value(devName).portList.size(); i++)
	{
		if (this->m_deviceList.value(devName).portList.at(i).portName.c_str() == portName)
		{
			for (auto m = m_deviceList.value(devName).portList.at(i).protList.begin(); m != m_deviceList.value(devName).portList.at(i).protList.end(); m++)
			{
				qDebug() << m->protocolName.c_str();
				if (m->protocolName.c_str() == protName)
				{
							return true;
				}
			}
		}
	}
	return false;
}

bool DevicDataManager::IsExitPort(QString devName, QString portName)
{
	if (devName.isEmpty() || portName.isEmpty())
	{
		return false;
	}
	for (auto i = m_deviceList.begin(); i != m_deviceList.end(); i++)
	{
		if (i->deviceName.c_str() == devName)
		{
			for (auto j = i->portList.begin(); j != i->portList.end(); j++)
			{
				if (j->portName.c_str() == portName)
				{
					return true;
				}
			}
		}
	}
	return false;
}



bool DevicDataManager::IsExitMessage(QString m_oldDevName,QString m_port,QString m_oldProtName,QString oldMessageName)
{
	for(int i=0;i<this->m_deviceList.value(m_oldDevName).portList.size();i++)
	{
		if(this->m_deviceList.value(m_oldDevName).portList.at(i).portName.c_str()== m_port)
		{
			for (auto m=m_deviceList.value(m_oldDevName).portList.at(i).protList.begin();m!= m_deviceList.value(m_oldDevName).portList.at(i).protList.end();m++)
			{
				if (m->protocolName == m_oldProtName.toStdString())
				{
					for (int j = 0; j < m->messgeList.size(); j++)
					{
						if (m->messgeList[j].messageName.c_str() == oldMessageName)
						{
							return true;
						}
					}
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

bool DevicDataManager::PortStruct::operator==(const PortStruct & that) const
{
	return portName==that.portName && protList==that.protList;
}

bool DevicDataManager::DevStruct::operator==(const DevStruct & that) const
{
	return deviceName==that.deviceName && deviceExt == that.deviceExt && portList == that.portList;
}
