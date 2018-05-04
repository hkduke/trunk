#include "AckQueue.h"
#include <assert.h>
#include "DataLinkMap.h"
#include "Transport.h"
#include "Framework.h"

#include "FileSendQueue.h"
#include "DataSampleElementList.h"
#include "CommonTool.h"
#include "LogManager.h"
#include "../Core/ACKPack.h"


namespace NetCom
{


	AckQueueManager::AckQueueManager(DataSampleElementList * ptr /*=nullptr*/)
	{
		//m_ackFun = nullptr;
 		is_Debug = false;
	}

	void AckQueueManager::SetDataLinkMap(DataLinkMap * ptr)
	{
		assert(ptr);
		m_pDataLinkMap = ptr;
	}

	void AckQueueManager::SetTransport(Transport * ptr)
	{
		assert(ptr);
		m_pTransport = ptr;
	}

	NetCom::DataLinkMap * AckQueueManager::GetDataLinkMap()
	{
		return m_pDataLinkMap;
	}

	void AckQueueManager::Push(void * buffer, UInt32 len)
	{
//		Timestamp timsTamp;
		if(is_Debug)LogManager::GetInstance().WriteMessage("AckQueueManager::Push:收到ACK");
		ACKPack pack;
		pack.PaserPack(buffer, len);
		UInt32 id = pack.GetSrcNodeId();
		UInt32 flag = pack.GetAckFlag();
		UInt32 frameser = pack.GetFrameSerial();
		m_pushMutex.lock();
		m_ackList.push(AckObj(id, flag, frameser));
		m_pushMutex.unlock();
		if (is_Debug)LogManager::GetInstance().WriteMessage("AckQueueManager::Push:开ACK完成:size:%d",Int32(len));
//		std::cout << __FUNCTION__<<"AckQueueManager::Push^^^^^^^^^^^^^ time elapsed::" << (int)timsTamp.elapsed() << std::endl;
	}

	void AckQueueManager::Run()
	{
		 _thread = new Thread;
		RunnableAdapter<AckQueueManager> *runnable = new RunnableAdapter<AckQueueManager>(*this, &AckQueueManager::ProcessQueue);
		_thread->start(*runnable);
	}

	void AckQueueManager::SetDebug(bool is)
	{
		is_Debug = is;
	}

	void AckQueueManager::RegsiterDataLinkFun(NetCom::DataLink* dl, NetCom::AckSendFun fun)
	{
		m_ackMapFun.insert(std::make_pair(dl, fun));
	}

	NetCom::AckQueueManager ::~AckQueueManager()
	{
	}

	void NetCom::AckQueueManager::ProcessQueue()
	{
		while (1)
		{

			if (m_ackList.empty())
			{
				if (is_Debug)LogManager::GetInstance().WriteMessage("AckQueue::ProcessQueue:数据队列处理完成开始休眠");
				_thread->trySleep(10);
				continue;
			}
			while (!m_ackList.empty())
			{
				m_pushMutex.lock();
				AckObj *ack = &m_ackList.front();
				
				// 匹配链路
				for (auto iterMap = m_ackMapFun.begin();iterMap!= m_ackMapFun.end();iterMap++)
				{
					DataLink * link = iterMap->first;
					if (link->GetdscNodeId() == ack->srcNode)
					{
						if ((ack->ackFlag))	// 1 失败
						{
							link->SetAckSendFlag(false);
						}
						else
						{
							link->SetAckSendFlag(true);
							//DataLink::ResIdStatus rs;
							link->GetCurrentResource().SetIsNeedResSend(true);
							
							link->GetCurrentResource().SetResId(++(ack->frameSerial));
							link->GetCurrentResource().SetAckStatus(ack->ackFlag);

							// 链路确认
							link->SetAffirm(true);
						}
						
						break;
					}
				}

				m_ackList.pop();
				m_pushMutex.unlock();
			}
			
		}

		
	}

}

