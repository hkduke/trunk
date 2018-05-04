#include "WaitSmallestHandle.h"

#include "../Communication/NodeJoinWriteHandle.h"
#include "../Communication/NodeDirectoryWriteHandle.h"
#include "../Core/Framework.h"
#include "../Core/ResourceManager.h"
//针对节点立即要退出的情况，为避免没有结点的情况，对链表进行循环式遍历
namespace NetCom
{

	WaitSmallestHandle::WaitSmallestHandle(double timeCount, int number):m_numberN(number),m_timeCount(timeCount)
	{
		m_writeHandle = NULL;

	}

	WaitSmallestHandle::~WaitSmallestHandle()
	{
		if (m_writeHandle)
		{
			m_writeHandle->Death();
			delete m_writeHandle;
		}
		if (m_timer)
		{
			delete m_timer;
		}
	}
	//设置定时器，定时调用检查是否超时收到目录列表
	int WaitSmallestHandle::HandleEnter(void *ptr)
	{
		m_timer = new Timer((long)m_timeCount, m_numberN);
		m_timer->start(TimerCallback<WaitSmallestHandle>(*this, &WaitSmallestHandle::ThreadAction));
		return -1;
	}

	int WaitSmallestHandle::Handle(void *ptr)
	{
		return 0;
	}

	int WaitSmallestHandle::HandleClose(void *ptr)
	{
		if (m_writeHandle)
		{
			m_writeHandle->Death();
			delete m_writeHandle;
		}
		if (m_timer)
		{
			delete m_timer;
		}
		
		return 0;
	}
	//超时更新检查
	void WaitSmallestHandle::ThreadAction(Timer& timer)
	{
		//计数开始
		static int count = 0;
		//如果不超时标志没有被置真，则没有目录列表进入，进入对下个节点的等待
		if (!ResourceManager::GetInstance().IsTimeOut())
		{
			//查找至目标结点，检查是否是自己本结点
			auto it = ResourceManager::GetInstance().GetNodeList().begin();	
			//遍历到下一次的节点
			for (it= ResourceManager::GetInstance().GetNodeList().begin(); 
				it != ResourceManager::GetInstance().GetNodeList().end(); ++it)
			{
				for (int i = 0; i < count; ++i)
				{
					it++;
				}
				if ((*it)->GetState() != NodeStatus::Stop )
				{
					count++;
					break;
				}
			}
			
			ResourceManager::GetInstance().SetSmallestNodeID((*it)->GetNodeID());
			ResourceManager::GetInstance().m_smallestAliveTime = 0;
			//如果是本结点，则发送目录，退出时间计时
			if (ResourceManager::GetInstance().IsSmallestNode())
			{
				if (m_writeHandle)
				{
					m_writeHandle->Death();
					delete m_writeHandle;
				}
				m_writeHandle = new NodeDirectoryWriteHandle;
				//Framework::GetInstance().GetEventManager()->RegisterEvent(m_writeHandle, NetCom::NodeDirectory_Write);
				m_writeHandle->HandleEnter(0);
				ResourceManager::GetInstance().MutexUnlock();
				timer.stop();
			}
		}			
		else
		{
			timer.stop();
		}
	}

}

