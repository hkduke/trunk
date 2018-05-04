#include "FileSendQueue.h"
#include <assert.h>
#include "DataLinkMap.h"
#include "Transport.h"
#include "Framework.h"

#include "MsgPushCommon.h"
#include "DataSampleElementList.h"
#include <map>

namespace NetCom
{
	MsgPushCommon::MsgPushCommon(DataSampleElementList * ptr /*=nullptr*/) :m_Resourceindex(0)
	{
	}

	void MsgPushCommon::Init()
	{
		m_dataCount = 100000;
		m_dataList = new DataSampleElementList;
		//m_pDataLinkMap = new DataLinkMap;
		DataLinkMap::DataLinkSet & mapset = m_pDataLinkMap->GetDataLinkSet();
		m_ack = Framework::GetInstance().GetIsAck();

		m_pMsgSendQueue = new MsgSendQueue;
		m_pMsgSendQueue->Init();
		m_pFileSendQueue = new FileSendQueue;
		m_pFileSendQueue->Init();
	}

	void MsgPushCommon::SetDataLinkMap(DataLinkMap * ptr)
	{
		assert(ptr);
		//m_pDataLinkMap = ptr;
		m_pMsgSendQueue->SetDataLinkMap(ptr);
		m_pFileSendQueue->SetDataLinkMap(ptr);
	}

	void MsgPushCommon::SetTransport(Transport * ptr)
	{
		assert(ptr);
		//m_pTransport = ptr;
	}

	NetCom::DataLinkMap * MsgPushCommon::GetDataLinkMap()
	{
		return m_pDataLinkMap;
	}

	NetCom::DataSampleElementList * MsgPushCommon::GetDataSampleElementList()
	{
		return m_dataList;
	}

	void MsgPushCommon::Push(UInt32 topic, UInt8 * data, UInt32 len, TransactionType type)
	{

		//Timestamp currentTime;

		if (m_dataList->Size() < m_dataCount)
		{
			++m_Resourceindex;
			m_lock.lock();
			//++m_Resourceindex;
// 			DataSampleElement * sample = new DataSampleElement;
// 			sample->SetResourceId(m_Resourceindex);
// 			sample->Copy(data, len);

			if (type == TransactionType_File)
			{
				//m_ResourceTable.insert(ResourceIndexMap::ValueType(m_Resourceindex, sample));
				m_pFileSendQueue->Push(data, len, type);
			}
			else if (type == TransactionType_Data)
			{
				//m_pMsgSendQueue->GetDataSampleElementList()->push(sample);
				m_pMsgSendQueue->Push(topic, data, len, type);
			}
			else {}
			//std::cout << __FUNCTION__ << "::::" << (int)currentTime.elapsed() << std::endl;

						//m_dataList->Push(sample);
			m_lock.unlock();
		}
	}
	void MsgPushCommon::Run()
	{
		_thread = new Thread;
		//SendQueue sq;
		RunnableAdapter<FileSendQueue>* runnable = new RunnableAdapter<FileSendQueue>(*m_pFileSendQueue, &FileSendQueue::ProcessQueue);
		_thread->start(*runnable);

		_thread_file = new Thread;
		RunnableAdapter<MsgSendQueue>* runnable_file = new RunnableAdapter<MsgSendQueue>(*m_pMsgSendQueue, &MsgSendQueue::ProcessQueue);
		_thread_file->start(*runnable_file);
		//_thread->join();
	}

	void MsgPushCommon::SetDataCount(UInt32 count)
	{
		m_dataCount = count;
	}

	NetCom::MsgPushCommon::~MsgPushCommon()
	{
	}

	void NetCom::MsgPushCommon::ProcessQueue()
	{
		//DataSampleElementList * ls = m_pDataLinkMap->GetDataSampleElementList();
		DataLinkMap::DataLinkSet & mapset = m_pDataLinkMap->GetDataLinkSet();
		DataSampleElementList::DataSampleList& queqe = m_dataList->GetDataSampleQueque();
		while (1)
		{
			if (m_dataList->Size() <= 0)
			{
				_thread->trySleep(10);
				continue;
			}

			//while (!m_dataList->Empty())
			{

				//DataSampleElement * de = m_dataList->Front();
				for (DataSampleElementList::DataSampleList::iterator de = queqe.begin(); de != queqe.end(); ++de)
				{
					for (DataLinkMap::DataLinkSet::const_iterator iterMap = mapset.begin(); iterMap != mapset.end(); iterMap++)
					{
						DataLink * link = iterMap->second;
						if (m_ack)
						{
							DataLink::ResIdStatus &rs = link->GetCurrentResource();

							bool timeout = rs.GetResIdTimeOut();

							DataLink::ResIdStatus& status = link->GetCurrentResource();
							if ((link->GetCurrentResource().GetResId() == (*de)->GetResourceId() && rs.GetResSendFlag())||timeout)
							{
								rs.SetIsNeedResSend(false);	//已经发送不用再发送
								ResourceIndexMap::Iterator iter = m_ResourceTable.find(rs.GetResId());
								if (iter != m_ResourceTable.end())
								{
									link->Send(iter->second);
									rs.SetResIdTimeOut(false);
								}
							}
						}
					}
				}

			}
		}


	}

}

