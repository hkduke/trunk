#include "FileSendQueue.h"
#include <assert.h>
#include "DataLinkMap.h"
#include "Transport.h"
#include "Framework.h"
#include "../Core/CommonTool.h"
#include "FileSendQueue.h"
#include "DataSampleElementList.h"
#include <map>
#include "../Core/Timestamp.h"
namespace NetCom
{
	FileSendQueue::FileSendQueue(DataSampleElementList * ptr /*=nullptr*/) :m_Resourceindex(0), m_FileBlend(nullptr)
	{
	}

	void FileSendQueue::Init()
	{
		m_dataCount = 100000;
		m_dataList = new DataSampleElementList;
		//m_pDataLinkMap = new DataLinkMap;
		DataLinkMap::DataLinkSet & mapset = m_pDataLinkMap->GetDataLinkSet();
		m_ack = Framework::GetInstance().GetIsAck();



	}

	void FileSendQueue::SetDataLinkMap(DataLinkMap * ptr)
	{
		assert(ptr);
		m_pDataLinkMap = ptr;
	}

	void FileSendQueue::SetTransport(Transport * ptr)
	{
		assert(ptr);
		//m_pTransport = ptr;
	}

	NetCom::DataLinkMap * FileSendQueue::GetDataLinkMap()
	{
		return m_pDataLinkMap;
	}

	NetCom::DataSampleElementList * FileSendQueue::GetDataSampleElementList()
	{
		return m_dataList;
	}
#include "../Core/Timestamp.h"
	void FileSendQueue::Push(UInt8 * data, UInt32 len, TransactionType type)
	{
	//	Timestamp currentTime;
	
		if (m_dataList->Size() < m_dataCount)
		{
			//m_lock.lock();
			++m_Resourceindex;
			DataSampleElement * sample = new DataSampleElement;
			sample->SetResourceId(m_Resourceindex);

			sample->Copy(data, len);
			
			//if (type == TransactionType_File)
			m_ResourceTable.insert(ResourceIndexMap::ValueType(m_Resourceindex, sample));

			m_dataList->Push(sample);	//std::cout << __FUNCTION__ << "::::::::::::" << (int)currentTime.elapsed() << std::endl;	
			//m_lock.unlock();
		}
		else
		{
			std::cout << "缓冲区已经超过配置" << std::endl;
		}	
				
	}

	void FileSendQueue::Run()
	{
		_thread = new Thread;
		//SendQueue sq;
		RunnableAdapter<FileSendQueue>* runnable = new RunnableAdapter<FileSendQueue>(*this, &FileSendQueue::ProcessQueue);
		_thread->start(*runnable);
		//_thread->join();
	}

	void FileSendQueue::SetDataCount(UInt32 count)
	{
		m_dataCount = count;
	}

	NetCom::FileSendQueue::~FileSendQueue()
	{
	}

	void NetCom::FileSendQueue::ProcessQueue()
	{
		//DataSampleElementList * ls = m_pDataLinkMap->GetDataSampleElementList();
		static Timestamp FixTime;



		DataLinkMap::DataLinkSet & mapset = m_pDataLinkMap->GetDataLinkSet();
		DataSampleElementList::DataSampleList& queqe = m_dataList->GetDataSampleQueque();
		m_FileBlend = Framework::GetInstance().GetBlendModeNet();
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

					if (!m_FileBlend)
					{
						for (DataLinkMap::DataLinkSet::const_iterator iterMap = mapset.begin(); iterMap != mapset.end(); iterMap++)
						{	
							
							DataLink * link = iterMap->second;
							if (m_ack)
							{
								DataLink::ResIdStatus &rs = link->GetCurrentResource();

								bool timeout = rs.GetResIdTimeOut();

								DataLink::ResIdStatus& status = link->GetCurrentResource();	
								
								int nLinkResId = link->GetCurrentResource().GetResId();
								int nDeResId = (*de)->GetResourceId();
								if ((link->GetCurrentResource().GetResId() == (*de)->GetResourceId() && rs.GetResSendFlag()) || timeout)
								{
									
									
									ResourceIndexMap::Iterator iter = m_ResourceTable.find(rs.GetResId());
										
									if (iter != m_ResourceTable.end())
									{
										Timestamp currentTime;
										std::cout << __FUNCTION__ << ":::::FileSendQueue::ProcessQueue:::" << (int)(currentTime - FixTime) << std::endl;
										std::cout << __FUNCTION__ << ":::::FileSendQueue::ProcessQueue:::nLinkResId" << (int)(nLinkResId) << std::endl;
										link->Send(iter->second);
										FixTime = Timestamp();
										rs.SetResIdTimeOut(false);
									}
									rs.SetIsNeedResSend(false);	//已经发送不用再发送
								}
							
							
							}

						}
					}
					
					// 混合模式
					if (m_FileBlend)
					{
						m_FileBlend->Send((UInt8*)(*de)->GetBlockPtr(), (*de)->GetBlockSize());
						m_dataList->Pop();
						if (de == queqe.end())
						{
							m_FileBlend = nullptr;
						}

					}
				}
		
			
			}
		}


	}

}

