#pragma once
#include "../Communication/DataLink.h"
#include "../Core/Export.h"
#include "../Sockets/ServerSocket.h"
#include "TCPTransport.h"
#include "../Reactor/SocketAcceptor.h"
namespace NetCom
{
	class ServerSocket;
	class NETCOMMUNICATION_EXPORT TCPDataLink :public DataLink
	{
	public:
		TCPDataLink() {};
		~TCPDataLink();

		virtual void Send(DataSampleElement* element, bool relink = true);
		//virtual void SetSendStrategy(TransportSendStrategy * strategy) ;
		virtual void MakeConnect();
		virtual void Bind();
		ServerSocket  m_tcpServerSocket;
		StreamSocket m_sendStreamSocket; 
		SocketAcceptor<ServiceHandler>*  m_accpet;
	private:
		TCPTransport * m_tcpTransport;
	};


}
