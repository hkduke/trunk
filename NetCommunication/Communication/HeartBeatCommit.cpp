#include "HeartBeatCommit.h"
#include "../Sockets/SocketAddress.h"
#include "../NodeDiscover/NodeDiscover.h"
#include "../Core/LogManager.h"
#include "../Core/ResourceManager.h"
#include "../Communication/NodeExitReadHandle.h"
#include "../Core/CommonTool.h"
#include "../Core/ResourceManager.h"
#include "../Core/Mutex.h"
namespace NetCom
{
	HeartBeatCommit::HeartBeatCommit()
	{
		m_timer = nullptr;
		m_heartBeatePack.FillData(0);
	}


	HeartBeatCommit::~HeartBeatCommit()
	{
		if (m_timer)
		{
			delete m_timer;
		}
	}

	void HeartBeatCommit::Start(long startInterval, long periodicInterval)
	{
		m_timer = new Timer(startInterval, periodicInterval);
		m_timer->start(TimerCallback<HeartBeatCommit>(*this, &HeartBeatCommit::Run));
	}

	void HeartBeatCommit::Stop()
	{
	}

	void HeartBeatCommit::Run(Timer & timer)
	{
		static int count = 4;
		SocketAddress sendSocket("255.255.255.255", NodeDiscover::GetInstance().m_sendPort);
		NodeDiscover::GetInstance().m_sendSocket->sendTo(m_heartBeatePack.Data(),
			ToolClass::GetHeaderSize(), sendSocket);
		//LogManager::GetInstance().WriteMessage("HeartBeatCommit::Run：：心跳包发送完成");
		Docheck();
		
	}

	void HeartBeatCommit::Docheck()
	{
		Thread::current()->setName("testdd");
		//ResourceManager::GetInstance().MutexLock();
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
			else if (nodeState == NodeStatus::Sleep)
			{
				(*it)->SetState(NodeStatus::Stop);
			}
			else
			{
				FastMutex mutex;
				mutex.lock();
				if ((*it)->GetNodeID() == ResourceManager::GetInstance().GetSmallestNodeID())
				{
					NodeExitReadHandle *exitHandle = new NodeExitReadHandle;
					exitHandle->HandleEnter((void*)(*it)->GetNodeID(), true);
				}
				mutex.unlock();
			}
		}
	//	LogManager::GetInstance().WriteMessage("HeartBeatCommit::Docheck::节点检查完成");
		//ResourceManager::GetInstance().MutexUnlock();
	}
}
