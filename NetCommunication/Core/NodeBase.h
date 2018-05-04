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
		NodeStatus GetState();//��ȡ״̬
		void SetState(NodeStatus state);//����״̬
		NodeAddr & GetNodeAddr();//��ȡ��ַ
		void SetNodeAddr(NodeAddr addr);//���õ�ַ
		void SetNodeID(UInt32 nodeID);//���ýڵ�ID
		UInt32 GetNodeID();//��ȡ�ڵ�ID
		void SetNodeAddrIP(UInt32 ip);
		UInt32 GetNodeAddrIP();

		std::string GetNodeIpString();
		void SetNetStyle(DeviceAddressType type);
		DeviceAddressType GetNetStyle();
	public:

		//TODO ddd
	protected:
		NodeStatus m_NodeStatus;	// �ڵ�״̬		
		NodeAddr m_Address;	// �ڵ��ַ
		UInt8 m_NodeID;	// �ڵ��ʶ
	};
}


