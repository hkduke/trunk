#include "NodeExitReadHandle.h"

#include "../Core/NodeBase.h"
#include "../Core/ResourceManager.h"
#include "../Communication/NodeDirectoryReadHandle.h"
#include "../Core/Framework.h"
#include "../Communication/NodeJoinReadHandle.h"
#include "../Communication/NodeDirectoryWriteHandle.h"
#include "../Communication/WaitSmallestHandle.h"
#include "../Core/NodeExitPack.h"
#include "../Core/LogManager.h"
namespace NetCom
{
	NodeExitReadHandle::NodeExitReadHandle() :m_timeHandle(nullptr), m_nodeWriteHand(nullptr), m_joinHandle(nullptr)
	{
	}

	NodeExitReadHandle::~NodeExitReadHandle()
	{
		if (m_timeHandle)
		{
			m_timeHandle->Death();
			delete m_timeHandle;
		}
		if (m_joinHandle)
		{
			m_joinHandle->Death();
			delete m_joinHandle;
		}
		if (m_nodeWriteHand)
		{
			m_nodeWriteHand->Death();
			delete m_nodeWriteHand;
		}
	}

	int NodeExitReadHandle::HandleEnter(void *ptr, bool isBeartHeart)
	{
		//�����㣬�ͷ������������Ϣ

		LogManager::GetInstance().WriteMessage("NodeExitReadHandle::HandleEnter �߳�ID��Ϊ��%d", (int)Thread::currentTid());

		UINT32 nodeID = 0;
		if (!isBeartHeart)
		{
			NodeExitPack pack;
			nodeID = pack.PaserPack(ptr);
		}
		else
		{
			nodeID = (int)ptr;
		}

		if (nodeID == ResourceManager::GetInstance().GetSmallestNodeID())
		{
			//TODO  ��������ɾ��
			//��Ȿ�ؽڵ��б����Լ��ǲ�����С��㣬����ǣ��򷢲����ؽڵ�Ŀ¼,��ʾ�����ڵ���½ڵ��б�
			ResourceManager::GetInstance().MutexLock();
			//������������С�ڵ��ڼ䲻�������ӽڵ�
			//Framework::GetInstance().GetEventManager()->RegisterEvent(m_joinHandle, NetCom::NodeDirectory_Read);
			ResourceManager::GetInstance().SetTimeOut(false);
			m_timeHandle = new WaitSmallestHandle(0, 100);
			m_timeHandle->HandleEnter(0);
			//Framework::GetInstance().GetEventManager()->RegisterEvent(m_timeHandle, NetCom::WaitSmallest);
		}
		else
		{
			ResourceManager::GetInstance().SetNodeState(nodeID, NetCom::Stop);
			LogManager::GetInstance().WriteMessage("NodeExitReadHandle::HandleEnter �ڵ�Id:%d�˳�\n",(int)nodeID);
		}
		return -1;
	}

	int NodeExitReadHandle::Handle(void *ptr)
	{
		return -1;

	}

	int NodeExitReadHandle::HandleClose(void *ptr)
	{
		if (m_timeHandle)
		{
			m_timeHandle->Death();
			delete m_timeHandle;
		}
		if (m_joinHandle)
		{
			m_joinHandle->Death();
			delete m_joinHandle;
		}
		if (m_nodeWriteHand)
		{
			m_nodeWriteHand->Death();
			delete m_nodeWriteHand;
		}
		return -1;
	}

}

