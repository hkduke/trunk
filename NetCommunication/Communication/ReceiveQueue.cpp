#include "ReceiveQueue.h"
#include <assert.h>
#include "DataLinkMap.h"
#include "Transport.h"
#include "Framework.h"

#include "FileSendQueue.h"
#include "DataSampleElementList.h"
#include "CommonTool.h"
#include "PackRoute.h"
#include "LogManager.h"

namespace NetCom
{


	ReceiveQueue::ReceiveQueue(DataSampleElementList * ptr /*=nullptr*/)
	{
		if(ptr==nullptr)
			m_dataList = new DataSampleElementList;
		m_pPackRoute = new PackRoute;
		is_Debug = true;
	}

	void ReceiveQueue::SetDataLinkMap(DataLinkMap * ptr)
	{
		assert(ptr);
		m_pDataLinkMap = ptr;
	}

	void ReceiveQueue::SetTransport(Transport * ptr)
	{
		assert(ptr);
		m_pTransport = ptr;
	}

	NetCom::DataLinkMap * ReceiveQueue::GetDataLinkMap()
	{
		return m_pDataLinkMap;
	}

	void ReceiveQueue::Push(void * buffer, UInt32 len)
	{
		if(is_Debug)LogManager::GetInstance().WriteMessage("ReceiveQueue::Push:开始收到网络数据压入缓冲区");
		int msgType = ToolClass::GetPacketType(buffer);
		LogManager::GetInstance().WriteMessage("ReceiveQueue::befor Push:msgType:%d", int(msgType));
		m_pushMutex.lock();
		//UInt32 len =ToolClass::GetPacketSize(buffer);
		if (len <= 0)return;
		DataSampleElement * data = new DataSampleElement;
		assert(data);
		data->Copy(buffer, len);
		msgType = ToolClass::GetPacketType(data->GetBlockPtr());
		LogManager::GetInstance().WriteMessage("ReceiveQueue::Push:msgType:%d", int(msgType));
		m_dataList->Push(data);
		m_pushMutex.unlock();
		if (is_Debug)LogManager::GetInstance().WriteMessage("ReceiveQueue::Push:开始收到网络数据压入缓冲区完成:size:%d",Int32(len));
	}

	void ReceiveQueue::Run()
	{
		 _thread = new Thread;
		//SendQueue sq;
		RunnableAdapter<ReceiveQueue> *runnable = new RunnableAdapter<ReceiveQueue>(*this, &ReceiveQueue::ProcessQueue);
		_thread->start(*runnable);
		//_thread->join();
	}

	void ReceiveQueue::SetDebug(bool is)
	{
		is_Debug = is;
	}

	NetCom::ReceiveQueue ::~ReceiveQueue()
	{
	}

	void NetCom::ReceiveQueue::ProcessQueue()
	{
		while (1)
		{
			
			if (m_dataList->Size() <= 0)
			{
				if (is_Debug)LogManager::GetInstance().WriteMessage("ReceiveQueue::ProcessQueue:数据队列处理完成开始休眠");
				_thread->trySleep(10);
				continue;
			}
			for (size_t i = 0; i < m_dataList->Size(); i++)
			{
				if (is_Debug)LogManager::GetInstance().WriteMessage("ReceiveQueue::ProcessQueue:接受数据 ，队列大小:%d", (Int32)m_dataList->Size());
				m_Mutex.lock();
				DataSampleElement * ele = m_dataList->Front();
				m_dataList->Pop();
				m_Mutex.unlock();
				size_t blocksize = ele->GetBlockSize();
				BYTE * data = static_cast<BYTE*>(ele->GetBlockPtr());
				if (is_Debug)LogManager::GetInstance().WriteMessage("ReceiveQueue::ProcessQueue:接受数据 ，数据大小:%d", (Int32)blocksize);
				m_pPackRoute->GenerateHandle(data, blocksize);
				
				
			}
			
		}

		
	}

}

