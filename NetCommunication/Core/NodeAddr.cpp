#include "NodeAddr.h"
#include "../Sockets/IPAddress.h"
namespace NetCom
{
	NodeAddr::NodeAddr(const std::string &address):m_Address(address)
	{

	}

	NodeAddr::NodeAddr():m_Address("")
	{

	}


	NodeAddr::~NodeAddr()
	{
	}

	bool NodeAddr::operator==(const NodeAddr& that)const
	{
		return this->m_addrType == that.m_addrType&&
			this->m_Address == that.m_Address&&
			this->m_addrSize == that.m_addrSize;
	}

	void NodeAddr::SetType(DeviceAddressType type)
	{
		m_addrType = type;
	}

	DeviceAddressType NodeAddr::GetType()
	{
		return m_addrType;
	}

	void NodeAddr::SetAddress(unsigned int address)
	{
		m_addr = address;
		in_addr addr;
		addr.S_un.S_addr = address;
		m_Address = inet_ntoa(addr);
	}



	void NodeAddr::SetAddress(std::string addr)
	{
		 
		 m_addr=inet_addr(addr.c_str());
		 m_Address = addr;
	}

	void NodeAddr::SetAddrSize(int size)
	{
		m_addrSize = size;
	}

	

	int NodeAddr::GetAddrSize()
	{
		return m_addrSize;
	}

	UInt32 NodeAddr::GetAddress()
	{
		return m_addr;
	}

	std::string NodeAddr::ToString()
	{
		return m_Address;
	}

}

