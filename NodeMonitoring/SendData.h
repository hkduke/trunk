#pragma once
#include "../Core/Runnable.h"
#include<iostream>
#include <vector>
#include "../Core/Any.h"
#include"../Core/Export.h"
#include "../TCPTransport/TCPTransport.h"

namespace NetCom
{
	class StreamSocket;
	class  SendData /*:public Runnable*/
	{
	public:
		SendData(std::vector<Any>*);
		~SendData();

		virtual void run();
		StreamSocket *m_sendStreamSocket;
		bool  m_isStop;
		std::vector<Any> *vector;
		TCPTransport::IpaddressSet * m_ipset;
		
	};
}


