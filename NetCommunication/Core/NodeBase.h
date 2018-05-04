#pragma once

#include "NodeAddr.h"
#include <string>
#include "Types.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT NodeBase
	{
	public:
		NodeBase();
		NodeBase(UInt8 nodeID);
		~NodeBase();



		bool Init();
		bool Start();
		bool Stop();
		bool Restart();
		void Sleep();		
		NodeStatus GetState();//获取状态
		void SetState(NodeStatus state);//设置状态
		NodeAddr & GetNodeAddr();//获取地址
		void SetNodeAddr(NodeAddr addr);//设置地址
		void SetNodeID(UInt32 nodeID);//设置节点ID
		UInt32 GetNodeID();//获取节点ID
		void SetNodeAddrIP(UInt32 ip);
		UInt32 GetNodeAddrIP();

		std::string GetNodeIpString();
		void SetNetStyle(DeviceAddressType type);
		DeviceAddressType GetNetStyle();
	public:

		//TODO ddd
	protected:
		NodeStatus m_NodeStatus;	// 节点状态		
		NodeAddr m_Address;	// 节点地址
		UInt8 m_NodeID;	// 节点标识
	};
}


