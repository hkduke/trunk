#include "NodeBase.h"
#include "../Core/CommonTool.h"


namespace NetCom
{
	NodeBase::NodeBase()
	{
		//m_NodeID = ToolClass::GenerateUint32UUID();
		this->SetState(Running);
	}


	NodeBase::NodeBase(UInt8 nodeID):m_NodeID(nodeID)
	{
		this->SetState(Running);
	}

	NodeBase::~NodeBase()
	{
	}

	NodeStatus NodeBase::GetState()
	{
		return m_NodeStatus;
	}
	//根据读取的配置信息，确定自己的协议类型，创建连接，
	bool NodeBase::Init()
	{
		return true;
	}

	bool NodeBase::Start()
	{
		return true;
	}

	bool NodeBase::Stop()
	{
		return true;
	}

	bool NodeBase::Restart()
	{
		return true;
	}

	void NodeBase::Sleep()
	{
		//FIXME

	}

	void NodeBase::SetState(NodeStatus state)
	{
		m_NodeStatus = state;
	}

	 NodeAddr&  NodeBase::GetNodeAddr()
	{
		// TODO: insert return statement here
		return m_Address;
	}

	void NodeBase::SetNodeAddr(NodeAddr addr)
	{
		m_Address = addr;
	}

	void NodeBase::SetNodeID(UInt32 nodeID)
	{
		this->m_NodeID = nodeID;
	}

	UInt32 NodeBase::GetNodeID()
	{
		return m_NodeID;
	}

	void NodeBase::SetNodeAddrIP(UInt32 ip)
	{
		m_Address.SetAddress(ip);
	}

	UInt32 NodeBase::GetNodeAddrIP()
	{
		return m_Address.GetAddress();
	}

	std::string NodeBase::GetNodeIpString()
	{
		return m_Address.ToString();
	}
	void NodeBase::SetNetStyle(DeviceAddressType type)
	{
		m_Address.SetType(type);
	}

	DeviceAddressType NodeBase::GetNetStyle()
	{
		return m_Address.GetType();
	}

}
