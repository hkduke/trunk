#include "WaitDicHand.h"
#include "../Communication/NodeJoinWriteHandle.h"
#include "../Communication/NodeDirectoryReadHandle.h"
#include "../Core/Framework.h"
#include "../Core/ResourceManager.h"
#include "../Core/Timer.h"
#include "../Communication/NodeDirectoryWriteHandle.h"
#include "../Core/LogManager.h"
namespace NetCom
{
	WaitDicHand::WaitDicHand(double timeCount)
		:m_timeCount(timeCount)
	{
	}


	WaitDicHand::~WaitDicHand()
	{
	}

	int WaitDicHand::HandleEnter(void *ptr)
	{
		//����һ����ʱ�����ڵ�m_timeCountʱִ�м��ʱ�䳬ʱһ�Σ�
		m_timer = new Timer(m_timeCount);
		m_timer->start(TimerCallback<WaitDicHand>(*this,&WaitDicHand::CheckTimeOutState));
		return -1;
	}

	int WaitDicHand::Handle(void *ptr)
	{
		return -1;
	}

	int WaitDicHand::HandleClose(void *ptr)
	{
		delete m_timer;
		return -1;
	}

	void WaitDicHand::CheckTimeOutState(Timer& timer)
	{
		//�����ʱ��ʱ�䵽��δ�н��Ŀ¼���������С���Ϊ�Լ�
		if (!ResourceManager::GetInstance().IsTimeOut())
		{
			ResourceManager::GetInstance().SetTimeOut(true);
			ResourceManager::GetInstance().
				SetSmallestNodeID(ResourceManager::GetInstance().GetCurrentNode()->GetNodeID());
			ResourceManager::GetInstance().m_smallestAliveTime = NodeDiscover::GetInstance().m_createTime.elapsed();
			ResourceManager::GetInstance().m_smallestLastSend = Timestamp();
			ResourceManager::GetInstance().SetInitCompelete(true);
			ResourceManager::GetInstance().AddNode(ResourceManager::GetInstance().GetCurrentNode());
			LogManager::GetInstance().WriteMessage("aitDicHand::CheckTimeOutState:: time out,�Ҷ��Լ�Ϊ��С��㣺idΪ%d\n"
			,(int) ResourceManager::GetInstance().GetCurrentNode()->GetNodeID());
			NodeDirectoryWriteHandle handle;
			handle.HandleEnter(0);
		}
	}
}

