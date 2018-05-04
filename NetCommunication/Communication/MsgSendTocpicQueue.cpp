#include "FileSendQueue.h"
#include <assert.h>
#include "DataLinkMap.h"
#include "Transport.h"
#include "Framework.h"

#include "MsgSendTocpicQueue.h"
#include "DataSampleElementList.h"
#include <map>
#include "../Core/LogManager.h"
namespace NetCom
{
	MsgSendTocpicQueue::MsgSendTocpicQueue(DataSampleElementQueue * ptr /*=nullptr*/) :m_Resourceindex(0)
	{
	}

	void MsgSendTocpicQueue::Init()
	{
		m_dataCount = 100000;
		m_dataList = new DataSampleElementQueue;
		//m_pDataLinkMap = new DataLinkMap;
		DataLinkMap::DataLinkSet & mapset = m_pDataLinkMap->GetDataLinkSet();
		m_ack = Framework::GetInstance().GetIsAck();
	}

	void MsgSendTocpicQueue::SetDataLinkMap(DataLinkMap * ptr)
	{
		assert(ptr);
		m_pDataLinkMap = ptr;
	}

	void MsgSendTocpicQueue::SetTransport(Transport * ptr)
	{
		assert(ptr);
		//m_pTransport = ptr;
	}

	NetCom::DataLinkMap * MsgSendTocpicQueue::GetDataLinkMap()
	{
		return m_pDataLinkMap;
	}

	NetCom::MsgSendTocpicQueue::DataSampleElementQueue * MsgSendTocpicQueue::GetDataSampleElementList()
	{
		return m_dataList;
	}

	void MsgSendTocpicQueue::Push(UInt8 * data, UInt32 len, TransactionType type)
	{
		if (m_dataList->size() < m_dataCount)
		{
			++m_Resourceindex;
			DataSampleElement * sample = new DataSampleElement;
			sample->SetResourceId(m_Resourceindex);
			sample->Copy(data, len);
			
			m_lock.lock();
			m_ResourceTable.insert(ResourceIndexMap::ValueType(m_Resourceindex, sample));
			m_dataList->push(sample);
			m_lock.unlock();
		}
		else
		{
			LogManager::GetInstance().WriteMessage("缓冲区超过配置");
		}
	}

	void MsgSendTocpicQueue::Run()
	{
		_thread = new Thread;
		//SendQueue sq;
		RunnableAdapter<MsgSendTocpicQueue>* runnable = new RunnableAdapter<MsgSendTocpicQueue>(*this, &MsgSendTocpicQueue::ProcessQueue);
		_thread->start(*runnable);
		//_thread->join();
	}

	void MsgSendTocpicQueue::SetDataCount(UInt32 count)
	{
		m_dataCount = count;
	}

	NetCom::MsgSendTocpicQueue::~MsgSendTocpicQueue()
	{
	}

	void NetCom::MsgSendTocpicQueue::ProcessQueue()
	{
		//DataSampleElementList * ls = m_pDataLinkMap->GetDataSampleElementList();
		DataLinkMap::DataLinkSet & mapset = m_pDataLinkMap->GetDataLinkSet();
		//MsgSendQueue::DataSampleElementQueue& queqe = m_dataList->GetDataSampleQueque();
		UInt32 datasize = mapset.size();
		
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
				DataSampleElement * dataItem = m_dataList->front();
				UInt32 dataindex = 0;
				for (DataLinkMap::DataLinkSet::const_iterator iterMap = mapset.begin(); iterMap != mapset.end(); iterMap++)
				{
					DataLink * link = iterMap->second;
					if (m_ack)
					{
						
						DataLink::ResIdStatus &rs = link->GetCurrentResource();
						if (rs.GetResId() >= (dataItem->GetResourceId()))
						{
							continue;
						}
						bool timeout = rs.GetResIdTimeOut();

						if ( link->GetIsAckSendFlag() || timeout)
						{
							m_currentResId = dataItem->GetResourceId();
							rs.SetResId(m_currentResId);
							rs.SetIsNeedResSend(false);	//已经发送不用再发送
							ResourceIndexMap::Iterator iter = m_ResourceTable.find(rs.GetResId());
							if (iter != m_ResourceTable.end())
							{
								link->Send(iter->second);
								rs.SetResIdTimeOut(false);
							}

						}

					}
					if (link->GetAffirm())
					{
						++dataindex;
					}
				}
				if (dataindex == datasize)
				{
					m_ResourceTable.erase(dataItem->GetResourceId());
					m_dataList->pop();
					delete dataItem;
					dataItem = nullptr;
					m_lock.unlock();

				}
			}

		}
	}

}

