#include "readDeviceXml.h"
#include <QDebug>


readDeviceXml::readDeviceXml(void)
{
}


readDeviceXml::~readDeviceXml(void)
{
}
//读取XML文件主函数
bool readDeviceXml::read(QIODevice* device)
{
	xml.setDevice(device);
	if(xml.readNextStartElement())
	{
		if(xml.name() == "xml" && xml.attributes().value("version") == "1.0")
		{
			readXml();
		}
		else
		{
			xml.raiseError(QObject::tr("This file is not an xml version 1.0 file"));
		}
	}
	return !xml.error();

}
//错误提示
QString readDeviceXml::errorString()const
{
	return QObject::tr("%1\n line %2,colume %3")
		.arg(xml.errorString())
		.arg(xml.lineNumber())
		.arg(xml.columnNumber());
}
//设置数据管理对象
void readDeviceXml::setxlDataManager(DevicDataManager * manager)
{
	xlmManager=manager;
}
//读取xml首
void readDeviceXml::readXml()
{
	Q_ASSERT(xml.isStartElement() && xml.name() =="xml");
	while(xml.readNextStartElement())
	{
		if(xml.name() == "device")
		{
			readDevice();
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
}
//读取设备树
void readDeviceXml::readDevice()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "device");
	DevicDataManager::DevStruct device=DevicDataManager::DevStruct();
	while(xml.readNextStartElement())
	{

		if(xml.name() == "deviceName")
		{
			device.deviceName=xml.readElementText().toStdString();
			xlmManager->m_devNameList<<device.deviceName.c_str();
		}
		else if(xml.name()=="deviceExt")
		{
			device.deviceExt=xml.readElementText().toStdString();
		}
		else if(xml.name() == "port")
		{
			if(!device.deviceName.empty())
			{
				readPort(&device);
			}
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
	xlmManager->m_deviceList[device.deviceName.c_str()]=device;

}


//读取协议信息
void readDeviceXml::readPro(DevicDataManager::PortStruct* portStruct)
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "protocol");
	DevicDataManager::ProtStruct protStruct;
	while(xml.readNextStartElement())
	{
		if(xml.name() == "protocolName")
		{
			protStruct.protocolName = xml.readElementText().toStdString();
		}
		else if (xml.name() == "protocolExt")
		{
			protStruct.protocolExt=xml.readElementText().toStdString();
		}
		else if(xml.name() == "message")
		{
			if(!protStruct.protocolName.empty())
			{
				readMessage(&protStruct);
			}
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
	portStruct->protList.append(protStruct);

}
//读取报文信息
void readDeviceXml::readMessage(DevicDataManager::ProtStruct* prot)
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "message");
	DevicDataManager::MessageStruct tempMessage;

	while(xml.readNextStartElement())
	{
		if(xml.name() == "messageName")
		{
			tempMessage.messageName=xml.readElementText().toStdString();
			
		}
		else if(xml.name() == "messageP")
		{
			tempMessage.messageP=xml.readElementText().toStdString();
		}
		else if(xml.name()=="messageExt")
		{
			tempMessage.messageExt=xml.readElementText().toStdString();
		}
		else if(xml.name()=="messageProp")
		{
			readProp(&tempMessage);
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
	prot->messgeList.append(tempMessage);
}
//读取属性信息
void readDeviceXml::readProp(DevicDataManager::MessageStruct* protStruct)
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "messageProp");
	DevicDataManager::PropStruct propStruct;
	while(xml.readNextStartElement())
	{
		if(xml.name() == "propName")
		{
			propStruct.propName = xml.readElementText().toStdString();
		}
		else if (xml.name() == "propStyle")
		{
			propStruct.propStyle = xml.readElementText().toStdString();
		}
		else if (xml.name() == "propSize")
		{
			propStruct.propSize = xml.readElementText().toInt();
		}
		else if (xml.name() == "propHint")
		{
			propStruct.propHint = xml.readElementText().toStdString();
		}
		else if (xml.name() == "propExt")
		{
			propStruct.propExt = xml.readElementText().toStdString();
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
	protStruct->propList.append(propStruct);
}
//读取端口信息
void readDeviceXml::readPort(DevicDataManager::DevStruct * devStruct)
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "port");
	DevicDataManager::PortStruct portStruct;
	while (xml.readNextStartElement())
	{
		if (xml.name() == "portName")
		{
			portStruct.portName = xml.readElementText().toStdString();
		}
		else if (xml.name() == "protocol")
		{
			readPro(&portStruct);
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
	devStruct->portList.append(portStruct);
}
