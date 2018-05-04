#include "NodeJoinReadHandle.h"
#include"../Communication/NodeDirectoryWriteHandle.h"
#include"../Core/ResourceManager.h"
#include "../Core/Framework.h"
#include "NodeJoinPack.h"
#include "../NodeDiscover/NodeDiscover.h"
#include "../Core/LogManager.h"
namespace NetCom
{

	NodeJoinReadHandle::NodeJoinReadHandle() :m_nodeWriteHand(nullptr)
	{
	}


	NodeJoinReadHandle::~NodeJoinReadHandle()
	{
	}


	int NodeJoinReadHandle::HandleEnter(void *ptr)
	{
		//�����㻹δ��ʼ�����,�򱣴����б��ȴ�Ŀ¼���µĵ���
			//��������룬�������С��㣬����Ŀ¼�б�����ʲô������
		LogManager::GetInstance().WriteMessage("NodeJoinReadHandle::HandleEnter�����յ��ڵ���������ʼ���");
		NodeJoinPack joinPack;
		NodeBase* pnb = (NodeBase*)(joinPack.PaserPack((BYTE*)ptr,255));
		std::list<NodeBase*>& partList = ResourceManager::GetInstance().GetNodeList();
		//ͨ��������ı�������½��
		 if (pnb->GetNodeID() == ResourceManager::GetInstance().GetCurrentNode()->GetNodeID())
		{
			delete pnb;
			return 0;
		}
		if (!pnb)
		{
			//��ӡ���߽���ĳ�ֲ���
			//std::cout << "NodeJoinPack perse false!" << std::endl;
			return 0;
		}
		ResourceManager::GetInstance().AddNode(pnb);
		

		//����Լ��ǲ�����С��㣬�������С���ͷ���Ŀ¼
		if (ResourceManager::GetInstance().IsSmallestNode())
		{
			m_nodeWriteHand = new NodeDirectoryWriteHandle;
			Framework::GetInstance().GetEventManager()->RegisterEvent(m_nodeWriteHand, NetCom::NodeDirectory_Write);
			m_nodeWriteHand->HandleEnter(&NodeDiscover::GetInstance().m_sendSocket);
		}
		LogManager::GetInstance().WriteMessage("NodeJoinReadHandle::HandleEnter�����յ��ڵ�������������");

		return 0;
	}



	int NodeJoinReadHandle::Handle(void *ptr)
	{
		return -1;
	}



	int NodeJoinReadHandle::HandleClose(void *ptr)
	{
		delete m_nodeWriteHand;
		m_nodeWriteHand = NULL;
		return -1;
	}

}

