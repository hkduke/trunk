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
	//读取文件函数
	bool read(QIODevice* device);
	//错误字符串格式
	QString errorString()const;
	//设置数据管理器
	void setxlDataManager(DevicDataManager * manager);

private:
	//读取xml文件内容
	void readXml();
	//读取设备内容
	void readDevice();
	//读取协议内容
	void readPro(DevicDataManager::PortStruct* portStruct);
	//读取报文内容
	void readMessage(DevicDataManager::ProtStruct* prot);
	//读取属性内容
	void readProp(DevicDataManager::MessageStruct* tempMessage);
	//读取端口内容
	void readPort(DevicDataManager::DevStruct* devStruct);

	QXmlStreamReader xml;//xml读取器对象
	QIcon folderIcon;
	QIcon bookMarkIcon;
	DevicDataManager* xlmManager;//设备数据管理
};

#endif