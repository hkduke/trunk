#include "readDeviceXml.h"
#include <QDebug>


readDeviceXml::readDeviceXml(void)
{
}


readDeviceXml::~readDeviceXml(void)
{
}
//��ȡXML�ļ�������
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
//������ʾ
QString readDeviceXml::errorString()const
{
	return QObject::tr("%1\n line %2,colume %3")
		.arg(xml.errorString())
		.arg(xml.lineNumber())
		.arg(xml.columnNumber());
}
//�������ݹ������
void readDeviceXml::setxlDataManager(DevicDataManager * manager)
{
	xlmManager=manager;
}
//��ȡxml��
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
//��ȡ�豸��
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


//��ȡЭ����Ϣ
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
//��ȡ������Ϣ
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
//��ȡ������Ϣ
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
//��ȡ�˿���Ϣ
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
