#include "TCPTransport.h"
#include "../Reactor/SocketConnector.h"
#include "ClientServiceHandler.h"
#include "../Core/CoreCommon.h"
#include "../Core/Framework.h"
#include "../Core/ResourceManager.h"
#include "../Core/Publisher.h"
#include "../Communication/DataLinkMap.h"
#include "TCPDataLink.h"
#include <assert.h>
#include <Windows.h>

#include "../Core/CommonTool.h"
#include "../Core/ResourceManager.h"
#include "../Communication/DataSampleElementList.h"
#include "../Communication/SendQueue.h"
#include "../Core/LogManager.h"
namespace NetCom
{

	TCPTransport::TCPTransport()
	{
	}

	TCPTransport::~TCPTransport()
	{

	}


	void ServiceHandler::Send(BYTE * data, UINT len)
	{
		char * recvbuf = (char*)MALLOC(len);
		memset(recvbuf, 0x00, sizeof(recvbuf));
		_socket.sendBytes(recvbuf, len);

	}

	void ServiceHandler::ProcessData(const string& RecvData)
	{

	}

	void ServiceHandler::onReadable(ReadableNotification* pNf)
	{
		pNf->release();
		char buffer[1024];

		int n = _socket.receiveBytes(buffer, sizeof(buffer));

		if (n > 0)
		{
// 			MessageTransePack pack;
// 			//std::cout << any<int>(pack.GetPropValue(pack.m_messageID)) << std::endl;
// 			int i = ToolClass::GetPacketType(buffer);
// 			if (ToolClass::GetPacketType(buffer) != MessageTranse)
// 				return;
// 			pack.PaserPack(buffer, n);
// 			//std::cout << AnyCast<int>(pack.GetPropValue(pack.m_messageID)) << std::endl;
			//m_pPackRoute->GenerateHandle((UInt8*)buffer);
			//m_receiveData.Push(buffer);
			Framework::GetInstance().GetResourceManager()->GetReceiveQueue().Push(buffer,n);
			//_socket.sendBytes(buffer, n);
		}
		else
		{
			_socket.shutdownSend();
			LogManager::GetInstance().WriteMessage("ServiceHandler::onReadable：shutdownSend");
			delete this;
		}
	}

	void ServiceHandler::onWirteble(ReadableNotification* pNf)
	{
		
	}

	void ServiceHandler::onTimeout(ReadableNotification* pNf)
	{

	}

	void ServiceHandler::onShutdown(ReadableNotification* pNf)
	{
		LogManager::GetInstance().WriteMessage("连接被onShutdown");
		pNf->release();
		_shutdown = true;
	}

	void ServiceHandler::_onError(int errorCode)
	{
		_failed = true;
		_reactor.stop();
	}

	void ServiceHandler::onError(ErrorNotification* pNotification)
	{
		pNotification->release();
		_onError(_socket.impl()->socketError());
	}

	void ServiceHandler::onAccept(ReadableNotification* pNotification)
	{
		LogManager::GetInstance().WriteMessage("接收新的连接:onAccept");
	}

	bool TCPTransport::Init()
	{
		//建立类型
		Transport::Init();
		EstablishReactor();
		ResourceManager::NodeList list = ResourceManager::GetInstance().GetNodeList();
		std::string ip = ResourceManager::GetInstance().GetCurrentNode()->GetNodeIpString();
		int index = 0;
		for (ResourceManager::NodeList::iterator iterList = list.begin();iterList!= list.end(); iterList++,++index)
		{
			NodeAddr  naddr = (*iterList)->GetNodeAddr();
			std::string addr = naddr.ToString();
			if(ip == naddr.ToString())continue;
			//std::cout << "地址为："<<(*iterList)->GetNodeAddr().ToString() << std::endl;

			LogManager::GetInstance().WriteMessage("建立传输地址：%s", (*iterList)->GetNodeAddr().ToString());
			IpaddressSet::iterator iterMap = m_connectstatus.find(naddr.ToString());
			if (iterMap == m_connectstatus.end())
			{
				m_sendStreamSocket = new StreamSocket();
				SocketAddress ssa = SocketAddress(addr, TRANSPORTPORT);

				m_sendStreamSocket->connect(ssa);
				
				TCPDataLink * link = new TCPDataLink;
				link->SetTransport(this);
				link->SetDataSampleElementList(GetDataSampleElementList());
				IPConnect ip;
				ip.stream = m_sendStreamSocket;
				ip.connect = true;
				DataLinkMap * mapData = /*GetDataLinkMap()*/ Framework::GetInstance().GetDataLinkMap();

				link->m_tcpServerSocket = serverSocket;
				link->m_sendStreamSocket = *m_sendStreamSocket;
				
				link->m_accpet = m_acceptor;
				link->m_NodeAddr = naddr;

				mapData->Insert(index, link);
				m_connectstatus.insert(std::pair<std::string, IPConnect>(naddr.ToString(), ip));
			}
			else
			{
				if (iterMap->second.connect)
				{
					LogManager::GetInstance().WriteMessage("连接已经建立：%s", (*iterList)->GetNodeAddr().ToString());
				}
			}


		}
//		const ResourceManager::ParticpatorSet& parlist = ResourceManager::GetInstance().GetGlobalParticpator();

		return true;
	}


	void TCPTransport::run()
	{
		m_reactor.run();
	}

	void TCPTransport::Start()
	{

	}

// 	void TCPTransport::Send(const UInt8 * data, UInt32 len)
// 	{
// 		assert(data&&len>0);
// 		//m_sendStreamSocket->sendBytes(data, len);
// 		DataSampleElementList * ls = GetDataSampleElementList();
// 		
// 	}

	bool TCPTransport::Install()
	{
		return false;
	}

	void TCPTransport::SendAll(UInt8 * data, UInt32 len)
	{
// 		const DataLinkMap::DataLinkSet &map = GetDataLinkMap()->GetDataLinkSet();
// 		DataSampleElementList * list = ResourceManager::GetInstance().GetSendQueue()->GetDataSampleElementList();
// 		for (DataLinkMap::DataLinkSet::const_iterator iterMap = map.begin();iterMap!=map.end();iterMap++)
// 		{
// 			DataLink * link = iterMap->second;
// 			link->Send(list);
// 		}


	}

	void TCPTransport::EstablishReactor()
	{
		if (!GetReactorEstablish())
		{
			ResourceManager::NodeList list = ResourceManager::GetInstance().GetNodeList();
			std::string ip = ResourceManager::GetInstance().GetCurrentNode()->GetNodeIpString();
			SocketAddress selfIp(ip, TRANSPORTPORT);
			serverSocket =   ServerSocket(selfIp);
			int index = 0;
			SocketAddress addselfsocket (ip, TRANSPORTPORT);
			/* SocketAcceptor<ServiceHandler> **/m_acceptor = new SocketAcceptor<ServiceHandler>(serverSocket, m_reactor);
			SocketConnector<NetCom::ClientServiceHandler> m_connector(addselfsocket, m_reactor);

			FailConnector connector(addselfsocket, m_reactor);


			SetReactorEstablishFlag(true);
			Thread* t2 = new Thread;
			//RunnableAdapter<NetCom::TCPTransport> *m_runnable = new RunnableAdapter<NetCom::TCPTransport>(*this, &NetCom::TCPTransport::run);
			t2->start(m_reactor);
			//t2->start(*m_runnable);
		}

	}

	void TCPTransport::RealseHandle()
	{
		if (m_connector)
		{
			delete m_connector;
			m_connector = nullptr;
		}
	}

	TCPTransport::IpaddressSet & TCPTransport::GetIpaddressSet()
	{
		return m_connectstatus;
	}

}


