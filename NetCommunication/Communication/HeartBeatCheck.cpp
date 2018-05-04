#include "HeartBeatCheck.h"
#include "../Core/ResourceManager.h"
#include "../Communication/Participator.h"
#include "../Communication/NodeExitReadHandle.h"
namespace NetCom
{
	HeartBeatCheck::HeartBeatCheck()
	{
		m_timer = nullptr;
	}


	HeartBeatCheck::~HeartBeatCheck()
	{
		if (m_timer)
		{
			delete m_timer;
		}
	}

	void HeartBeatCheck::Start(long startInterval /*= 0*/, long periodicInterval /*= 0*/)
	{
		m_timer = new Timer(startInterval, periodicInterval);
		m_timer->start(TimerCallback<HeartBeatCheck>(*this, &HeartBeatCheck::Run));
		return;
	}

	void HeartBeatCheck::Stop()
	{
		if (m_timer)
		{
			m_timer->stop();
		}

	}

	void HeartBeatCheck::Run(Timer & timer)
	{
		ResourceManager::GetInstance().MutexLock();
		const std::list<NodeBase*>& list = ResourceManager::GetInstance().GetNodeList();
		for (auto it = list.begin(); it != list.end(); ++it)
		{

			if ((*it)->GetNodeID() == ResourceManager::GetInstance().GetCurrentNode()->GetNodeID())
			{
				continue;
			}
			NodeStatus nodeState = (*it)->GetState();
			if (nodeState == NodeStatus::Running)
			{
				(*it)->SetState(NodeStatus::Sleep);
			}
			else if(nodeState== NodeStatus::Sleep)
			{
				(*it)->SetState(NodeStatus::Stop);
			}
			else
			{
					NodeExitReadHandle *exitHandle = new NodeExitReadHandle;
					exitHandle->HandleEnter((void*)(*it)->GetNodeID(),true);
			}
		}

		ResourceManager::GetInstance().MutexUnlock();
	}

}


