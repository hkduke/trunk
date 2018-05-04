#include "NodeJoinPack.h"
#include "../Core/DateTime.h"
#include "ResourceManager.h"
#include "../Core/NodeAddr.h"
#include "../Core/NodeBase.h"
#include "../Core/Any.h"
#include "../Core/CommonTool.h"
#include "../Core/LogManager.h"
namespace NetCom
{
	NodeJoinPack::NodeJoinPack()
	{
	}

	NodeJoinPack::~NodeJoinPack()
	{
	}
	//分解接收到的报文,解包并把结点加入管理中
	void* NodeJoinPack::PaserPack(BYTE *data,int lenth)
	{
		//设置data数据
		SetData(data,lenth);
		//获取节点需要的所有信息
		NodeAddr addr;
		//Any ip = GetPropValue(m_netIP);
		//PrintData();
		//int ipd = AnyCast<int>(ip);	
		//addr.SetAddress((unsigned int)AnyCast<int>(GetPropValue(m_netIP)));
		//addr.SetType((NetCom::DeviceAddressType)AnyCast<int>(GetPropValue(m_netStyle)));
		//NodeBase* base = new NodeBase(AnyCast<int>(GetPropValue(m_sourceID)));
		UINT32 ipd = ToolClass::GetFixData<UINT32>(m_data, ToolClass::GetHeaderSize()+ NODEJOINNETTYPE);
		DeviceAddressType netType= ToolClass::GetFixData<DeviceAddressType>(m_data, ToolClass::GetHeaderSize());
		addr.SetAddress(ipd);
		addr.SetType((DeviceAddressType)netType);
		NodeBase* base = new NodeBase(ToolClass::GetSourceDevID(m_data));
		base->SetNodeAddr(addr);
		base->SetState(Running);
		
		std::string netStyle;
		if ((int)netType == (int)DeviceAddressType::IP_V4_ADDR)
		{
			netStyle = "IP_V4_ADDR";
		}
		else if ((int)netType == (int)DeviceAddressType::IP_V6_ADDR)
		{
			netStyle = "IP_V6_ADDR";
		}
		else if ((int)netType == (int)DeviceAddressType::CAN_DEV_ADDR)
		{
			netStyle = "CAN_DEV_ADDR";
		}
		else
		{
			//netStyle = "未知网络";
		}
		ToolClass::PrintMessageHeader(m_data);
		LogManager::GetInstance().WriteMessage("网络类型：%s",netStyle);
		LogManager::GetInstance().WriteMessage("网络地址：%s", base->GetNodeIpString());
		return base;
	}

	int NodeJoinPack::FillData(BYTE *data)
	{
		ManagePack::FillData(data);

	/*	SetPropValue(m_netStyle, (int)ResourceManager::GetInstance().
			GetCurrentNode()->GetNodeAddr().GetType());
		SetPropValue(m_netIP,(int)ResourceManager::GetInstance().
			GetCurrentNode()->GetNodeAddr().GetAddress());
		SetPropValue(m_messageID, (int)NodeJoin);*/

		ToolClass::SetFixData<char>(m_data,(char) ToolClass::GetHeaderSize(),
			ResourceManager::GetInstance().GetCurrentNode()->GetNodeAddr().GetType());
		ToolClass::SetFixData<UInt32>(m_data, (char)ToolClass::GetHeaderSize()+ NODEJOINNETTYPE,
			(UInt32)ResourceManager::GetInstance().GetCurrentNode()->GetNodeAddr().GetAddress());
		ToolClass::SetPacketType(m_data, EPackType::NodeJoin);
		PaserPack(m_data, 256);
		//现用基类，如果有参数变化，则设置单独的
		return -1;
	}

	int NodeJoinPack::GetPackageSize()
	{
		return ToolClass::GetHeaderSize() + 5;
	}

}

