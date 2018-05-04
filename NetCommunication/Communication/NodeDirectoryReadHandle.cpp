#include "NodeDirectoryReadHandle.h"
#include "../Core/WaitDicHand.h"
#include "../Core/NodeDirectoryPack.h"
#include "../Communication/NodeJoinWriteHandle.h"
#include "../Core/NodeDirectoryPack.h"
#include "../Core/CoreComponent.h"
#include "../Core/NodeBase.h"
#include "../Core/CommonTool.h"
#include "../Core/Timestamp.h"
#include "../Core/Any.h"
#include "../Communication/TopicPublisherWriteHandle.h"
#include "../Core/ResourceManager.h"
#include <list>

#include "../Core/LogManager.h"
using namespace std;
NetCom::NodeDirectoryReadHandle::NodeDirectoryReadHandle()
{
}

NetCom::NodeDirectoryReadHandle::~NodeDirectoryReadHandle()
{
}

int NetCom::NodeDirectoryReadHandle::HandleEnter(void *ptr)
{
	ResourceManager* manager = &ResourceManager::GetInstance();
	NodeDirectoryPack m_nodePack;
	m_nodePack.SetData((BYTE*)ptr, 256);
	int nodeId = ToolClass::GetSourceDevID(ptr);
	//如果是本结点发来的，则退出
	if (nodeId == ResourceManager::GetInstance().GetCurrentNode()->GetNodeID())
	{
		LogManager::GetInstance().WriteMessage("本节点广播的目录收到，不进行任何处理。");
		return 0;
	}
	//获取仲裁时间,发送包的时间,只要有目录来就要参与目录更新

	Timestamp::TimeDiff diff(ToolClass::GetFixData<UInt64>(ptr, ToolClass::GetHeaderSize()));
	//最后一次发送目录收到的时间到现在的时间与最小结点发过来的时间就是到现在最小结点的生存时间
	Timestamp::TimeDiff currentDiff = ResourceManager::GetInstance().m_smallestLastSend.elapsed();
	Timestamp::TimeDiff smallestLiveTime = ResourceManager::GetInstance().m_smallestAliveTime + currentDiff;

	//要处理目录的情况有4种：
	//初始化未完成时，正常更新目录，在节点加入时只进行一次
	//作为主节点，最后发目录时的生存时间小于其它节点发送目录的生存时间
	//不为主节点，记录的接收到目录时现最小结点的生存时间，小于其它节点发送来的生存时间
	//主节点发送来的目录更新信息
	if (!manager->IsInitCompelete() || diff > smallestLiveTime)
	{
		if (!manager->IsInitCompelete())
		{
			manager->SetTimeOut(true);
			manager->SetInitCompelete(true);
		}
		manager->SetSmallestNodeID(nodeId);
		LogManager::GetInstance().WriteMessage("NodeDirectoryReadHandle::HandleEnter最小结点为,id号为%d\n",
			(int)nodeId);
		manager->m_smallestAliveTime = diff;
		ResourceManager::GetInstance().m_smallestLastSend = Timestamp();
		manager->MutexUnlock();

		//更新目录
		std::list<NodeBase*>& nodelist = ResourceManager::GetInstance().GetNodeList();
		std::list<NodeBase*> nodeLs = m_nodePack.PaserPack((BYTE*)ptr, ToolClass::GetPacketSize(ptr));
		//更新为统一的最小结点目录
		ResourceManager::GetInstance().MutexLock();
		NodeBase* tempNode = nullptr;
		for (auto it = nodeLs.begin(); it != nodeLs.end(); ++it)
		{
			bool isExit = false;
			for (auto iit = nodelist.begin(); iit != nodelist.end(); ++iit)
			{
				if ((*iit)->GetNodeID() == (*it)->GetNodeID() && (*iit)->GetNodeAddrIP() == (*it)->GetNodeAddrIP())
				{
					tempNode = *it;
					delete *it;
					isExit = true;
				}				
				else if ((*iit)->GetNodeID() != (*it)->GetNodeID() && (*iit)->GetNodeAddrIP() == (*it)->GetNodeAddrIP())
				{
					(*iit)->SetNodeID((*it)->GetNodeID());
					delete *it;
					isExit = true;
				}	
				else if ((*iit)->GetNodeID() == (*it)->GetNodeID() && (*iit)->GetNodeAddrIP() != (*it)->GetNodeAddrIP())
				{
					(*iit)->SetNodeAddr((*it)->GetNodeAddr());
					delete *it;
					isExit = true;
				}

			}
			if (!isExit)
			{
				ResourceManager::GetInstance().AddNode(*it);	//发送节点
			}

		
		}
	}		
	TopicPublisherWriteHandle handle;
	handle.HandleEnter(EPackType::TopicPublisher);
	ResourceManager::GetInstance().MutexUnlock();
	return 1;
}


int NetCom::NodeDirectoryReadHandle::Handle(void * ptr)
{
	return 1;
}

int NetCom::NodeDirectoryReadHandle::HandleClose(void *ptr)
{
	delete m_writeHandle;
	return 1;
}
