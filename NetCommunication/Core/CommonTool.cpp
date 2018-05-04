#include "CommonTool.h"
#include "../Core/UUID.h"
#include "UUIDGenerator.h"
#include "HashFunction.h"
#include <iostream>
#include <limits>
#include <vector>
#include"../Core/LogManager.h"
#include "../Sockets/IPAddress.h"
namespace NetCom
{



	inline UInt8 ToolClass::GenerateUint32UUID()
	{
		{
			UUIDGenerator& generator = UUIDGenerator::defaultGenerator();
			UUID uuid(generator.create());
			HashFunction<std::string> func;
			UInt32 id = func(uuid.toString(), UInt32(256));
			return UInt8(id);
		}
	}
	int ToolClass::GetPackFramType(void * buff)
	{
		char first = *((char*)buff);
		first >>= 7;
		first &= 1;
		return  first;
	}
	int ToolClass::GetPackFlag(void * buff)
	{
		char first = *((char*)buff);
		first >>= 5;
		first &= 3;
		return  first;
	}
	int ToolClass::GetPackProperity(void * buff)
	{
		char first = *((char*)buff);
		first &= 0x1F;
		return  first;
	}
	inline UINT16 ToolClass::GetPacketType(void * buff)
	{
		std::vector<BYTE> vects;
		vects.push_back(((BYTE*)buff)[3]);
		vects.push_back(((BYTE*)buff)[4]);
		return *(UINT16*)vects.data();
	}

	inline unsigned int ToolClass::GetPacketSize(void * buff)
	{
		std::vector<BYTE> vects;
		vects.push_back(((BYTE*)buff)[1]);
		vects.push_back(((BYTE*)buff)[2]);
		return *(UINT16*)vects.data();
	}

	UInt64 ToolClass::GetPackGeneralTime(void * buff)
	{
		std::vector<BYTE> vects;
		vects.push_back(((BYTE*)buff)[5]);
		vects.push_back(((BYTE*)buff)[6]);
		vects.push_back(((BYTE*)buff)[7]);
		vects.push_back(((BYTE*)buff)[8]);
		return *(UInt64*)vects.data();
	}

	UInt32 ToolClass::GetSourceDevID(void * buff)
	{
		std::vector<BYTE> vects;
		for (int i = 9; i < 13; i++)
		{
			vects.push_back(((BYTE*)buff)[i]);
		}
		return *(UInt32*)vects.data();
	}

	UInt32 ToolClass::GetSourceTargetID(void * buff)
	{
		std::vector<BYTE> vects;
		for (int i = 13; i < 17; i++)
		{
			vects.push_back(((BYTE*)buff)[i]);
		}
		return *(UInt32*)vects.data();
	}

	UInt16 ToolClass::GetAnsoweFlag(void * buff)
	{
		std::vector<BYTE> vects;
		for (int i = 17; i < 19; i++)
		{
			vects.push_back(((BYTE*)buff)[i]);
		}
		return *(UInt16*)vects.data();
	}

	UInt16 ToolClass::GetReserveC(void * buff)
	{
		std::vector<BYTE> vects;
		for (int i = 19; i < 21; i++)
		{
			vects.push_back(((BYTE*)buff)[i]);
		}
		return *(UInt16*)vects.data();
	}

	void ToolClass::PrintMessageHeader(void * buff)
	{
		LogManager::GetInstance().WriteMessage("设备帧类型：%d", (int)GetPackFramType(buff));
		LogManager::GetInstance().WriteMessage("包标志：%d", (int)GetPackFlag(buff));
		LogManager::GetInstance().WriteMessage("优先级：%d", (int)GetPackProperity(buff));
		EPackType type = (EPackType)GetPacketType(buff);
		std::string typName;
		switch (type)
		{
		case NetCom::NodeJoin:
			typName = "NodeJoin";
			break;
		case NetCom::NodeDirectory:
			typName = "NodeDirectory";
			break;
		case NetCom::NodeExit:
			typName = "NodeExit";
			break;
		case NetCom::TopicPublisher:
			typName = "TopicPublisher";
			break;
		case NetCom::TopicDiscribe:
			typName = "TopicDiscribe";
			break;
		case NetCom::MessageTranse:
			typName = "MessageTranse";
			break;
		case NetCom::HEARTBEAT:
			typName = "HEARTBEAT";
			break;
		default:
			break;
		}
		LogManager::GetInstance().WriteMessage("报文类型：%s", typName);
		LogManager::GetInstance().WriteMessage("数据包大小：%d", (int)GetPacketSize(buff));
		LogManager::GetInstance().WriteMessage("产生时刻：%d", (int)GetPackGeneralTime(buff));
		LogManager::GetInstance().WriteMessage("源设备标识：%d", (int)GetSourceDevID(buff));
		LogManager::GetInstance().WriteMessage("目标设备信息：%d", (int)GetSourceTargetID(buff));
		LogManager::GetInstance().WriteMessage("确认标志：%d", (int)GetAnsoweFlag(buff));
		LogManager::GetInstance().WriteMessage("保留字：%d", (int)GetReserveC(buff));
	}

	void ToolClass::SetPackFramType(void * buff, int framType)
	{
		*((char*)buff) &= 0x7F;
		framType &= 1;
		framType <<= 7;
		char first = *((char*)buff);
		first |= framType;
		*((char*)buff) = first;
	}

	void ToolClass::SetPackFlag(void * buff, int packFlag)
	{
		*((char*)buff) &= 0x9F;
		packFlag &= 3;
		packFlag <<= 5;
		char first = *((char*)buff);
		first |= packFlag;
		*((char*)buff) = first;
	}

	void ToolClass::SetPackProperity(void * buff, int properity)
	{
		properity &= 0x1F;
		char first = *((char*)buff);
		first |= properity;
		*((char*)buff) = first;
	}

	void ToolClass::SetPacketType(void * buff, EPackType packType)
	{
		UInt16 tempVar = (UInt16)packType;
		memcpy(((char*)buff) + 3, &tempVar, 2);
	}

	void ToolClass::SetPacketSize(void * buff, int packSize)
	{
		UInt16 tempVar = (UInt16)packSize;
		memcpy(((char*)buff) + 1, &tempVar, 2);
	}

	void ToolClass::SetPackGeneralTime(void * buff, UInt64 generalTime)
	{
		memcpy(((char*)buff) + 5, &generalTime, 4);
	}

	NETCOMMUNICATION_EXPORT void ToolClass::SetSourceDevID(void * buff, UInt32 sourceID)
	{
		memcpy(((char*)buff) + 9, &sourceID, 4);
	}

	void ToolClass::SetSourceTargetID(void * buff, UInt32 targetID)
	{
		memcpy(((char*)buff) + 13, &targetID, 4);
	}

	void ToolClass::SetAnsoweFlag(void * buff, UInt16 ansowFlag)
	{
		memcpy(((char*)buff) + 17, &ansowFlag, 2);
	}

	void ToolClass::SetReserveC(void * buff, UInt16 reserver)
	{
		memcpy(((char*)buff) + 19, &reserver, 2);
	}

	 int ToolClass::GetHeaderSize()
	{
		return 21;
	}

	std::string ToolClass::TransAddressToStr(unsigned int address)
	{
		in_addr addr;
		addr.S_un.S_addr = address;
		return inet_ntoa(addr);

	}

}
