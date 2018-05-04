#include "WaitSmallestHandle.h"

#include "../Communication/NodeJoinWriteHandle.h"
#include "../Communication/NodeDirectoryWriteHandle.h"
#include "../Core/Framework.h"
#include "../Core/ResourceManager.h"
//��Խڵ�����Ҫ�˳��������Ϊ����û�н�����������������ѭ��ʽ����
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
	//���ö�ʱ������ʱ���ü���Ƿ�ʱ�յ�Ŀ¼�б�
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
	//��ʱ���¼��
	void WaitSmallestHandle::ThreadAction(Timer& timer)
	{
		//������ʼ
		static int count = 0;
		//�������ʱ��־û�б����棬��û��Ŀ¼�б���룬������¸��ڵ�ĵȴ�
		if (!ResourceManager::GetInstance().IsTimeOut())
		{
			//������Ŀ���㣬����Ƿ����Լ������
			auto it = ResourceManager::GetInstance().GetNodeList().begin();	
			//��������һ�εĽڵ�
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
			//����Ǳ���㣬����Ŀ¼���˳�ʱ���ʱ
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

