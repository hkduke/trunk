#pragma once

#include "../Communication/Transport.h"
#include "../Sockets/StreamSocket.h"
#include "../Reactor/SocketNotification.h"
#include "../Reactor/SocketAcceptor.h"
#include "../Reactor/SocketConnector.h"
#include <string>
#include <iostream>
#include<fstream>
#include "ClientServiceHandler.h"

#include "../Communication/ReceiveQueue.h"
#include <map>
#include "FailConnector.h"

#define TRANSPORTPORT 515
using namespace std;
namespace NetCom
{
	class SendData;

	class ServiceHandler
	{
	public:
		ServiceHandler(StreamSocket& socket, SocketReactor& reactor) : _socket(socket), _reactor(reactor)
		{
			_reactor.addEventHandler(_socket, Observer<ServiceHandler, ReadableNotification>(*this, &ServiceHandler::onReadable));
			//_reactor.addEventHandler(_socket, Observer<SocketConnector, WritableNotification>(*this, &SocketConnector::onWirteble));
			//_reactor.addEventHandler(_socket, Observer<ServiceHandler, TimeoutNotification>(*this, &ServiceHandler::onTimeout));
			//_reactor.addEventHandler(_socket, Observer<ServiceHandler, ShutdownNotification>(*this, &ServiceHandler::onShutdown));
			_reactor.addEventHandler(_socket, Observer<ServiceHandler, ErrorNotification>(*this, &ServiceHandler::onError));
			//_reactor.addEventHandler(_socket, Observer<ServiceHandler, ReadableNotification>(*this, &ServiceHandler::onAccept));
		}

		~ServiceHandler()
		{
			_reactor.removeEventHandler(_socket, Observer<ServiceHandler, ReadableNotification>(*this, &ServiceHandler::onReadable));
		}

		void Send(BYTE * data, UINT len);
	private:
		void ProcessData(const string& RecvData);
		void onReadable(ReadableNotification* pNf);
		void onWirteble(ReadableNotification* pNf);
		void onTimeout(ReadableNotification* pNf);
		void onShutdown(ReadableNotification* pNf);
		void _onError(int errorCode);
		void onAccept(ReadableNotification* pNotification);
		void onError(ErrorNotification* pNotification);
		StreamSocket   _socket;
		SocketReactor& _reactor;
		bool _shutdown;
		bool _failed;
	};

	class NETCOMMUNICATION_EXPORT TCPTransport :public Transport ,public Runnable
	{
	public:
		typedef struct  IPConnect
		{
			bool connect;
			StreamSocket* stream;
		};
	public:
		typedef std::map<std::string, IPConnect> IpaddressSet;
		TCPTransport();
		~TCPTransport();

		virtual bool Init();
		virtual void run();
		virtual void Start();
		//virtual void Send(const UInt8 * data , UInt32 len);
		virtual bool Install();
		virtual void SendAll(UInt8 * data , UInt32 len);
		void EstablishReactor();
		void RealseHandle();
		IpaddressSet & GetIpaddressSet();
		SocketAcceptor<ServiceHandler> *m_acceptor;
		SocketConnector<ClientServiceHandler> * m_connector;
		SocketReactor m_reactor;
		ServerSocket serverSocket;
		StreamSocket* m_sendStreamSocket;
		SendData * m_pSendData;
		bool m_isconnect;
		IpaddressSet m_connectstatus;
	};

	void NodeJion(void *);
}

