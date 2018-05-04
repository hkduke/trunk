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
	//����Ǳ���㷢���ģ����˳�
	if (nodeId == ResourceManager::GetInstance().GetCurrentNode()->GetNodeID())
	{
		LogManager::GetInstance().WriteMessage("���ڵ�㲥��Ŀ¼�յ����������κδ���");
		return 0;
	}
	//��ȡ�ٲ�ʱ��,���Ͱ���ʱ��,ֻҪ��Ŀ¼����Ҫ����Ŀ¼����

	Timestamp::TimeDiff diff(ToolClass::GetFixData<UInt64>(ptr, ToolClass::GetHeaderSize()));
	//���һ�η���Ŀ¼�յ���ʱ�䵽���ڵ�ʱ������С��㷢������ʱ����ǵ�������С��������ʱ��
	Timestamp::TimeDiff currentDiff = ResourceManager::GetInstance().m_smallestLastSend.elapsed();
	Timestamp::TimeDiff smallestLiveTime = ResourceManager::GetInstance().m_smallestAliveTime + currentDiff;

	//Ҫ����Ŀ¼�������4�֣�
	//��ʼ��δ���ʱ����������Ŀ¼���ڽڵ����ʱֻ����һ��
	//��Ϊ���ڵ㣬���Ŀ¼ʱ������ʱ��С�������ڵ㷢��Ŀ¼������ʱ��
	//��Ϊ���ڵ㣬��¼�Ľ��յ�Ŀ¼ʱ����С��������ʱ�䣬С�������ڵ㷢����������ʱ��
	//���ڵ㷢������Ŀ¼������Ϣ
	if (!manager->IsInitCompelete() || diff > smallestLiveTime)
	{
		if (!manager->IsInitCompelete())
		{
			manager->SetTimeOut(true);
			manager->SetInitCompelete(true);
		}
		manager->SetSmallestNodeID(nodeId);
		LogManager::GetInstance().WriteMessage("NodeDirectoryReadHandle::HandleEnter��С���Ϊ,id��Ϊ%d\n",
			(int)nodeId);
		manager->m_smallestAliveTime = diff;
		ResourceManager::GetInstance().m_smallestLastSend = Timestamp();
		manager->MutexUnlock();

		//����Ŀ¼
		std::list<NodeBase*>& nodelist = ResourceManager::GetInstance().GetNodeList();
		std::list<NodeBase*> nodeLs = m_nodePack.PaserPack((BYTE*)ptr, ToolClass::GetPacketSize(ptr));
		//����Ϊͳһ����С���Ŀ¼
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
				ResourceManager::GetInstance().AddNode(*it);	//���ͽڵ�
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
