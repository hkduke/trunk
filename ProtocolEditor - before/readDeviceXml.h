#pragma once
#ifndef READDEVICEXML_H
#define READDEVICEXML_H

#include <QXmlStreamReader>
#include <QIcon>
#include "devicdatamanager.h"
class readDeviceXml
{
public:
	readDeviceXml(void);
	~readDeviceXml(void);

	bool read(QIODevice* device);

	QString errorString()const;

	void setxlDataManager(DevicDataManager * manager);

private:
	void readXml();
	void readDevice();
	void readPro(DevicDataManager::DevStruct* devStruct);
	void readMessage(DevicDataManager::ProtStruct* prot);
	void readProp(DevicDataManager::MessageStruct* tempMessage);
	QXmlStreamReader xml;
	QIcon folderIcon;
	QIcon bookMarkIcon;
	DevicDataManager* xlmManager;
};

#endif