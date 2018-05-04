#pragma once
#include <string.h>
#include <stdlib.h>
#include "Export.h"

// ���嵼���ӿ�
#ifdef __cplusplus
#define  EXTERN_CPP extern "C"
#else
#define EXTERN_CPP extern
#endif

#define MBYTE (1024*1024)
#define KBYTE (1024)
#define MALLOC(size)  malloc(size);
#define FREE(data)  free(data) ; data = nullptr;


namespace NetCom
{
	typedef unsigned int UINT;
	typedef unsigned char BYTE;

	// ȱʡ�˿�
	#define DEFULT_PORT (9919)	

	enum TransactionType
	{
		TransactionType_File,
		TransactionType_Data
	};

	// �豸����
	enum DeviceType
	{
		CAN_DEV ,
		IP,
	};

	// �豸��ַ����
	enum  DeviceAddressType
	{
		CAN_DEV_ADDR = 1<<0 ,
		IP_V4_ADDR = 1<<1,
		IP_V6_ADDR = 1<<2,
	}; 

	// �ڵ�״̬
	enum NodeStatus
	{
		Running,
		Stop,
		Sleep,
	};

	// �ڵ�����״̬
	enum ConnecStatus
	{
		Connected,
		Connecting,
		Waiting,
		Close
	};

	// ������
	enum EPackType
	{
		NodeJoin = 0, //�ڵ㷢�ְ�
		NodeDirectory = 1,// �ڵ�Ŀ¼��
		NodeExit = 2, // �ڵ�Ŀ¼��
		GainDirectory = 3, // ��ȡ�ڵ�Ŀ¼
		RefreshNodeDirectory = 4, // ���½ڵ�Ŀ¼
		TopicPublisher = 5,//���ⷢ��
		TopicDiscribe = 6,//��������
		TopicPublisherList = 7,//�����������б�
		MessageTranse = 8,//���ݱ������ݴ���
		DiscribeFail = 9,//����ʧ��
		DiscribeSuccess = 10,//���ĳɹ�
		LookupPublisherSuccess = 11,//��ѯ�����߳ɹ�
		LookupPublisherFail = 12,//��ѯ�����߳ɹ�
		ACK = 13,//��Ӧ��
		PING = 14,//ping��
		RESTATE = 15,//������״̬
		HEARTBEAT = 16,//����
		TopicPublisherRemove = 18,//�����Ƴ�
		TopicDiscribeList = 19,
		FileTranse =20 // �ļ�
	};

	// ����������
	enum ParticipatorType
	{
		DataWriter , // ����д��
		DataReader, // ���ݶ���
		None,
	};

	enum EventTypeHandle
	{
		NodeJoin_Read = 1 << 0,
		NodeJoin_Write = 1 << 1,
		NodeDirectory_Read = 1 << 2,
		NodeDirectory_Write = 1 << 3,
		NodeExit_Read = 1 << 4,
		NodeExit_Write = 1 << 5,
		GainDirectory_Read = 1 << 6,
		GainDirectory_Write = 1 << 7,
		RefreshNodeDirectory_Read = 1 << 8,
		RefreshNodeDirectory_Write = 1 << 9,
		DataPacket_Read = 1 << 10,	// ��ϵͳ���� �û�����
		DataPacket_Write = 1 << 11,// ��ϵͳ���� �û�����
		TimeWait = 1 << 12,
		WaitSmallest = 1 << 13,
		TopicPublisher_Read = 1 << 14,
		TopicPublisher_Write = 1 << 15,
		File_Read = 1 << 16,
		Ack_Read = 1 << 17,	// Ack
		EventTypeHandle_None = 1 << 30,

	};

	// ����
	enum NetType
	{
		NetType_None,
		ESubscriber , // ������
		EPublisher , // ������
		ESubAndPub,
	};
}

