#pragma once
#include <string>
#include "CoreCommon.h"
#include <iostream>
// ½ÚµãµØÖ·

namespace NetCom
{
	class NETCOMMUNICATION_EXPORT NodeAddr
	{
	public:
		NodeAddr(const std::string &address );
		NodeAddr();
		~NodeAddr();
		bool operator==(const NodeAddr& that)const;
	public:
		void SetType(DeviceAddressType type);
		DeviceAddressType GetType();

		void SetAddress(unsigned int address);
		void SetAddress(std::string addr);
		void SetAddrSize(int size);
		int GetAddrSize();
		unsigned int GetAddress();
		std::string ToString();
	private:
		DeviceAddressType m_addrType;
		std::string m_Address;
		int m_addrSize;
		unsigned int m_addr;
	};

}

