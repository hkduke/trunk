#pragma once
#include "CoreCommon.h"
#include "../Core/Types.h"
#include "../Core/Any.h"
#include <iostream>
#include <vector>
#include "../Core/Export.h"
#define MAXPACKAGESIZE 1024//发送文件包分包最大值
//文件头部分，总共11个
//前面三个字段格式固定
const int DATALENTHSIZEPOSE = 1;
const int  DATALENTHSIZE = 2;//数据域长度大小,位置1

const int TOPICSIZE = 2;//主题大小,位置3
const int  TOPICSIZEPOSE = (DATALENTHSIZEPOSE + DATALENTHSIZE);

const int  SOURCEIDSIZE = 1;//源地址大小，位置5
const int  SOURCEIDSIZEPOSE = (TOPICSIZEPOSE + TOPICSIZE);//源地址大小

const int TARGETIDSIZE = 1;//目标地址大小 ,位置6
const int TARGETIDSIZEPOSE = (SOURCEIDSIZEPOSE + SOURCEIDSIZE);//目标地址大小 


const int  DATAGENERALTIMESIZE = 4;//数据产生时间,位置7
const int  DATAGENERALTIMESIZEPOSE = (TARGETIDSIZEPOSE + TARGETIDSIZE);

const int STANDAREDHEADSIZE = (DATAGENERALTIMESIZEPOSE + DATAGENERALTIMESIZE);//帧头大小,共11

const int   FRAMTAILCHECKSIZE= 2;//尾校验和
//数据域区域

const int FILETOPICIDSIZE = 3; //文件主题号大小,位置11
const int FILETOPICIDPOSE = STANDAREDHEADSIZE;

const int  FILECHECKLENTHSIZE = 1; //文件证码长度,位置14
const int  FILECHECKLENTHPOSE = (FILETOPICIDPOSE + FILETOPICIDSIZE);
const int FILECHECKPOSE = (FILECHECKLENTHPOSE + FILECHECKLENTHSIZE);
const int FILENAMLENTHSIZE = 1; // 文件名大小，位置
const int  FILECHECKSIZE = 1;//数据域校验和

const int NODEJOINNETTYPE=1;

namespace NetCom
{

	namespace  ToolClass
	{

		NETCOMMUNICATION_EXPORT UInt8  GenerateUint32UUID();

		//获取帧类型
		NETCOMMUNICATION_EXPORT int  GetPackFramType(void* buff);
		//获取包标志
		NETCOMMUNICATION_EXPORT int  GetPackFlag(void* buff);
		//获取优先级
		NETCOMMUNICATION_EXPORT int  GetPackProperity(void* buff);
		//获取报文类型
		NETCOMMUNICATION_EXPORT UINT16  GetPacketType(void* buff);
		//获取数据包大小
		NETCOMMUNICATION_EXPORT unsigned int GetPacketSize(void* buff);
		//获取数据产生时刻
		NETCOMMUNICATION_EXPORT UInt64 GetPackGeneralTime(void* buff);
		//获取数据信息源设备标识
		NETCOMMUNICATION_EXPORT UInt32 GetSourceDevID(void* buff);
		//获取数据设备目标设备信息
		NETCOMMUNICATION_EXPORT UInt32 GetSourceTargetID(void* buff);
		//获取确认标志
		NETCOMMUNICATION_EXPORT UInt16 GetAnsoweFlag(void* buff);
		//获取保留字
		NETCOMMUNICATION_EXPORT UInt16 GetReserveC(void* buff);

		//打印文件头
		NETCOMMUNICATION_EXPORT void PrintMessageHeader(void* buff);

		//设置帧类型
		NETCOMMUNICATION_EXPORT void  SetPackFramType(void* buff, int framType);
		//设置包标志
		NETCOMMUNICATION_EXPORT void  SetPackFlag(void* buff, int packFlag);
		//设置优先级
		NETCOMMUNICATION_EXPORT void  SetPackProperity(void* buff, int properity);
		//设置报文类型
		NETCOMMUNICATION_EXPORT void  SetPacketType(void* buff, EPackType packType);
		//设置数据包大小
		NETCOMMUNICATION_EXPORT void  SetPacketSize(void* buff, int packSize);
		//设置数据产生时刻
		NETCOMMUNICATION_EXPORT void  SetPackGeneralTime(void* buff, UInt64 generalTime);
		//设置数据信息源设备标识
		NETCOMMUNICATION_EXPORT void  SetSourceDevID(void* buff, UInt32 sourceID);
		//设置数据设备目标设备信息
		NETCOMMUNICATION_EXPORT void  SetSourceTargetID(void* buff, UInt32 targetID);
		//设置确认标志
		NETCOMMUNICATION_EXPORT void  SetAnsoweFlag(void* buff, UInt16 ansowFlag);
		//设置保留字
		NETCOMMUNICATION_EXPORT void  SetReserveC(void* buff, UInt16 reserver);
		//获取包头的大小
		NETCOMMUNICATION_EXPORT int GetHeaderSize();
		//获取包的IP字符
		NETCOMMUNICATION_EXPORT std::string TransAddressToStr(unsigned int address);

		//校验和函数
		
		//获取固定位置报文
		template<typename T>
		T GetFixData(void* buff, int begin)
		{
			std::vector<BYTE> vects;
			int size = sizeof(T);
			for (int i = begin; i < begin + size; i++)
			{
				vects.push_back(((BYTE*)buff)[i]);
			}
			return *(T*)vects.data();
		}
		//设置固定位置报文
		template<typename T>
		void  SetFixData(void* buff, int begin, T var)
		{
			memcpy((char*)buff + begin, &var, sizeof(var));
		}
	}
}