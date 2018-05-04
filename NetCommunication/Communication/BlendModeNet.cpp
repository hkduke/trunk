
#include <assert.h>
#include "DataLinkMap.h"
#include "Transport.h"
#include "Framework.h"

#include "BlendModeNet.h"

#include "../Core/ResourceManager.h"
//#include "../Core/Framework.h"
#include "../Communication/ReceiveQueue.h"
#include <map>

namespace NetCom
{
	BlendModeNet::BlendModeNet(DataSampleElementList * ptr /*=nullptr*/)
	{
		//if(ptr==nullptr)
			//Init();

	}

	void BlendModeNet::Init()
	{
		m_dataCount = 10000;
		m_dataList = new DataSampleElementList;
		m_pDataLinkMap = new DataLinkMap;
		DataLinkMap::DataLinkSet & mapset = m_pDataLinkMap->GetDataLinkSet();

		m_port = Framework::GetInstance().ConfigInt("EnableBlendMode.Port");

		m_sendSocket = new DatagramSocket;
		m_sendAddrss = SocketAddress(ResourceManager::GetInstance().GetCurrentNode()->GetNodeIpString(), m_port);
		m_sendSocket->bind(m_sendAddrss);
		m_sendSocket->setBroadcast(true);

		m_receiveAddrss = SocketAddress(IPAddress(), m_port);
		m_receiveSocket = new DatagramSocket(m_receiveAddrss);
		Run();
	}

	void BlendModeNet::SetDataLinkMap(DataLinkMap * ptr)
	{
		assert(ptr);
		m_pDataLinkMap = ptr;
	}

	void BlendModeNet::SetTransport(Transport * ptr)
	{
		assert(ptr);
		m_pTransport = ptr;
	}

	NetCom::DataLinkMap * BlendModeNet::GetDataLinkMap()
	{
		return m_pDataLinkMap;
	}

	NetCom::DataSampleElementList * BlendModeNet::GetDataSampleElementList()
	{
		return m_dataList;
	}

	void BlendModeNet::Push(UInt8 * data, UInt32 len)
	{
		if (m_dataList->Size() < m_dataCount)
		{
			DataSampleElement * sample = new DataSampleElement;
			sample->Copy(data, len);
			m_dataList->Push(sample);
		}
		else
		{
			std::cout << "缓冲区已经超过配置" << std::endl;
		}
	}

	void BlendModeNet::Run()
	{
		_thread = new Thread;
		//SendQueue sq;
		RunnableAdapter<BlendModeNet>* runnable = new RunnableAdapter<BlendModeNet>(*this, &BlendModeNet::ReadData);
		_thread->start(*runnable);
		//_thread->join();
	}

	void BlendModeNet::Send(UInt8 * data, UInt32 len)
	{
		SocketAddress sendSocket("255.255.255.255", m_port);
		m_sendSocket->sendTo(data, len, sendSocket);
	}

	void BlendModeNet::ReadData()
	{
		char buffer[1024 * 2];
		while (1)
		{
			memset(buffer, 0, sizeof(buffer));
			int n = m_receiveSocket->receiveBytes(buffer, sizeof(buffer) - 1);
			Framework::GetInstance().GetResourceManager()->GetReceiveQueue().Push(buffer,n);
		}
	}

	NetCom::BlendModeNet::~BlendModeNet()
	{
		if (m_sendSocket)
		{
			delete m_sendSocket;
			m_sendSocket = nullptr;
		}
		if (m_receiveSocket)
		{
			delete m_receiveSocket;
			m_receiveSocket = nullptr;
		}
	}

	void NetCom::BlendModeNet::ProcessQueue()
	{
		//DataSampleElementList * ls = m_pDataLinkMap->GetDataSampleElementList();
		DataLinkMap::DataLinkSet & mapset = m_pDataLinkMap->GetDataLinkSet();
		while (1)
		{
			if (m_dataList->Size() <= 0)
			{
				_thread->trySleep(10);
				continue;
			}
			for (DataLinkMap::DataLinkSet::const_iterator iterMap = mapset.begin();iterMap!= mapset.end();iterMap++)
			{
				DataLink * link = iterMap->second;
				link->SetDataSampleElementList(m_dataList);
				
				link->Send(m_dataList);
			}

		}

		
	}

}

