#include "readDeviceXml.h"
#include <QDebug>


readDeviceXml::readDeviceXml(void)
{
}


readDeviceXml::~readDeviceXml(void)
{
}

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

QString readDeviceXml::errorString()const
{
	return QObject::tr("%1\n line %2,colume %3")
		.arg(xml.errorString())
		.arg(xml.lineNumber())
		.arg(xml.columnNumber());
}

void readDeviceXml::setxlDataManager(DevicDataManager * manager)
{
	xlmManager=manager;
}

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
		else if(xml.name() == "protocol")
		{
			if(!device.deviceName.empty())
			{
				readPro(&device);
			}
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
	xlmManager->m_deviceList[device.deviceName.c_str()]=device;

}

void readDeviceXml::readPro(DevicDataManager::DevStruct* devStruct)
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
		else if (xml.name() == "port")
		{
			protStruct.port = xml.readElementText().toStdString();
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
	devStruct->protList.append(protStruct);

}

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

void readDeviceXml::readProp(DevicDataManager::MessageStruct* protStruct)
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "messageProp");
	DevicDataManager::PropStruct propStruct;
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