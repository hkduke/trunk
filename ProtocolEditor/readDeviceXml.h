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
	//��ȡ�ļ�����
	bool read(QIODevice* device);
	//�����ַ�����ʽ
	QString errorString()const;
	//�������ݹ�����
	void setxlDataManager(DevicDataManager * manager);

private:
	//��ȡxml�ļ�����
	void readXml();
	//��ȡ�豸����
	void readDevice();
	//��ȡЭ������
	void readPro(DevicDataManager::PortStruct* portStruct);
	//��ȡ��������
	void readMessage(DevicDataManager::ProtStruct* prot);
	//��ȡ��������
	void readProp(DevicDataManager::MessageStruct* tempMessage);
	//��ȡ�˿�����
	void readPort(DevicDataManager::DevStruct* devStruct);

	QXmlStreamReader xml;//xml��ȡ������
	QIcon folderIcon;
	QIcon bookMarkIcon;
	DevicDataManager* xlmManager;//�豸���ݹ���
};

#endif