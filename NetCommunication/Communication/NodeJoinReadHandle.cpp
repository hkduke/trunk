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
		//假设结点还未初始化完成,则保存入列表，等待目录更新的到来
			//如果结点加入，检测是最小结点，则发送目录列表，否则什么都不做
		LogManager::GetInstance().WriteMessage("NodeJoinReadHandle::HandleEnter，接收到节点加入包，开始解包");
		NodeJoinPack joinPack;
		NodeBase* pnb = (NodeBase*)(joinPack.PaserPack((BYTE*)ptr,255));
		std::list<NodeBase*>& partList = ResourceManager::GetInstance().GetNodeList();
		//通过解出来的报文填充新结点
		 if (pnb->GetNodeID() == ResourceManager::GetInstance().GetCurrentNode()->GetNodeID())
		{
			delete pnb;
			return 0;
		}
		if (!pnb)
		{
			//打印或者进行某种操作
			//std::cout << "NodeJoinPack perse false!" << std::endl;
			return 0;
		}
		ResourceManager::GetInstance().AddNode(pnb);
		

		//检测自己是不是最小结点，如果是最小结点就发送目录
		if (ResourceManager::GetInstance().IsSmallestNode())
		{
			m_nodeWriteHand = new NodeDirectoryWriteHandle;
			Framework::GetInstance().GetEventManager()->RegisterEvent(m_nodeWriteHand, NetCom::NodeDirectory_Write);
			m_nodeWriteHand->HandleEnter(&NodeDiscover::GetInstance().m_sendSocket);
		}
		LogManager::GetInstance().WriteMessage("NodeJoinReadHandle::HandleEnter，接收到节点加入包，解包完成");

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

