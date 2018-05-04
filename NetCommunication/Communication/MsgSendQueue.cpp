#include "FileSendQueue.h"
#include <assert.h>
#include "DataLinkMap.h"
#include "Transport.h"
#include "Framework.h"

#include "MsgSendQueue.h"
#include "DataSampleElementList.h"
#include <map>
#include "../Core/LogManager.h"
namespace NetCom
{
	MsgSendQueue::MsgSendQueue(DataSampleElementQueue * ptr /*=nullptr*/) :m_Resourceindex(0)
	{
	}

	void MsgSendQueue::Init()
	{
		m_dataCount = 100000;
		m_dataList = new DataSampleElementQueue;
		//m_pDataLinkMap = new DataLinkMap;
		DataLinkMap::DataLinkSet & mapset = m_pDataLinkMap->GetDataLinkSet();
		m_ack = Framework::GetInstance().GetIsAck();
	}

	void MsgSendQueue::SetDataLinkMap(DataLinkMap * ptr)
	{
		assert(ptr);
		m_pDataLinkMap = ptr;
	}

	void MsgSendQueue::SetTransport(Transport * ptr)
	{
		assert(ptr);
		//m_pTransport = ptr;
	}

	NetCom::DataLinkMap * MsgSendQueue::GetDataLinkMap()
	{
		return m_pDataLinkMap;
	}

	NetCom::MsgSendQueue::DataSampleElementQueue * MsgSendQueue::GetDataSampleElementList()
	{
		return m_dataList;
	}

	void MsgSendQueue::Push(UInt32 topcic, UInt8 * data, UInt32 len, TransactionType type)
	{
		if (m_dataList->size() < m_dataCount)
		{
			//m_lock.lock();
			++m_Resourceindex;
// 			DataSampleElement * sample = new DataSampleElement;
// 			sample->SetResourceId(m_Resourceindex);
// 			sample->Copy(data, len);
			
			MsgSendTocpicQueueMap::iterator iterMap = m_mapMsgQueue.find(topcic);
			if (iterMap != m_mapMsgQueue.end())
			{
				iterMap->second->Push(data, len);
			}
			else
			{
				MsgSendTocpicQueue * msg = new MsgSendTocpicQueue;
				msg->Init();
				msg->Run();
				m_mapMsgQueue.insert(std::make_pair(topcic, msg));
			}
			//m_dataList->push(sample);
			//m_lock.unlock();
		}
		else
		{
			LogManager::GetInstance().WriteMessage("»º³åÇø³¬¹ıÅäÖÃ");
		}
	}

	void MsgSendQueue::Run()
	{
		_thread = new Thread;
		//SendQueue sq;
		RunnableAdapter<MsgSendQueue>* runnable = new RunnableAdapter<MsgSendQueue>(*this, &MsgSendQueue::ProcessQueue);
		_thread->start(*runnable);
		//_thread->join();
	}

	void MsgSendQueue::SetDataCount(UInt32 count)
	{
		m_dataCount = count;
	}

	NetCom::MsgSendQueue::~MsgSendQueue()
	{
	}

	void NetCom::MsgSendQueue::ProcessQueue()
	{
		//DataSampleElementList * ls = m_pDataLinkMap->GetDataSampleElementList();
		DataLinkMap::DataLinkSet & mapset = m_pDataLinkMap->GetDataLinkSet();
		//MsgSendQueue::DataSampleElementQueue& queqe = m_dataList->GetDataSampleQueque();
		while (1)
		{
			if (m_dataList->empty())
			{
				_thread->trySleep(10);
				continue;
			}

			while (!m_dataList->empty())
			{

				m_lock.lock();
				DataSampleElement * de = m_dataList->front();
				
				for (DataLinkMap::DataLinkSet::const_iterator iterMap = mapset.begin(); iterMap != mapset.end(); iterMap++)
				{
					DataLink * link = iterMap->second;
					if (/*link->GetDataControlInfo()== DataLink::SubPub*/1)
					{
						link->Send(de);

					}
				}
				if (de)
				{
					delete de;
					de = nullptr;
				}
				m_dataList->pop();
				m_lock.unlock();

			}
		}


	}

}

