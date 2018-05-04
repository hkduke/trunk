#pragma once
#include <string.h>
#include <stdlib.h>
#include "Export.h"

// 定义导出接口
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

	// 缺省端口
	#define DEFULT_PORT (9919)	

	enum TransactionType
	{
		TransactionType_File,
		TransactionType_Data
	};

	// 设备类型
	enum DeviceType
	{
		CAN_DEV ,
		IP,
	};

	// 设备地址类型
	enum  DeviceAddressType
	{
		CAN_DEV_ADDR = 1<<0 ,
		IP_V4_ADDR = 1<<1,
		IP_V6_ADDR = 1<<2,
	}; 

	// 节点状态
	enum NodeStatus
	{
		Running,
		Stop,
		Sleep,
	};

	// 节点连接状态
	enum ConnecStatus
	{
		Connected,
		Connecting,
		Waiting,
		Close
	};

	// 包类型
	enum EPackType
	{
		NodeJoin = 0, //节点发现包
		NodeDirectory = 1,// 节点目录包
		NodeExit = 2, // 节点目录包
		GainDirectory = 3, // 获取节点目录
		RefreshNodeDirectory = 4, // 更新节点目录
		TopicPublisher = 5,//主题发布
		TopicDiscribe = 6,//订阅主题
		TopicPublisherList = 7,//发布者主题列表
		MessageTranse = 8,//数据报文内容传输
		DiscribeFail = 9,//订阅失败
		DiscribeSuccess = 10,//订阅成功
		LookupPublisherSuccess = 11,//查询发布者成功
		LookupPublisherFail = 12,//查询发布者成功
		ACK = 13,//响应包
		PING = 14,//ping包
		RESTATE = 15,//重新置状态
		HEARTBEAT = 16,//心跳
		TopicPublisherRemove = 18,//主题移除
		TopicDiscribeList = 19,
		FileTranse =20 // 文件
	};

	// 参与者类型
	enum ParticipatorType
	{
		DataWriter , // 数据写入
		DataReader, // 数据读入
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
		DataPacket_Read = 1 << 10,	// 由系统产生 用户数据
		DataPacket_Write = 1 << 11,// 由系统产生 用户数据
		TimeWait = 1 << 12,
		WaitSmallest = 1 << 13,
		TopicPublisher_Read = 1 << 14,
		TopicPublisher_Write = 1 << 15,
		File_Read = 1 << 16,
		Ack_Read = 1 << 17,	// Ack
		EventTypeHandle_None = 1 << 30,

	};

	// 类型
	enum NetType
	{
		NetType_None,
		ESubscriber , // 订阅者
		EPublisher , // 发布者
		ESubAndPub,
	};
}

