#include "HeartBeatReadHandle.h"
#include "../Core/HeartBeatPack.h"
#include "../Core/ResourceManager.h"
#include"../Core/CommonTool.h"
#include "../Core/LogManager.h"
namespace NetCom
{
	HeartBeatReadHandle::HeartBeatReadHandle()
	{
	}


	HeartBeatReadHandle::~HeartBeatReadHandle()
	{
	}

	int HeartBeatReadHandle::HandleEnter(void *ptr)
	{
		HeartBeatPack pack;
		//ToolClass::PrintMessageHeader(ptr);
		//FIXME
		pack.SetData(ptr, ToolClass::GetPacketSize(ptr));
		UINT32 nodeID = ToolClass::GetSourceDevID(ptr);

		//根据反馈的信息，改变节点目录中的在线状态。获取发送该包的NodeId
		//将节点状态更改为运行
		if (ResourceManager::GetInstance().IsNodeExit(nodeID))
		{
			//LogManager::GetInstance().WriteMessage("HeartBeatCommit::Run：：接收到节点ID：%d发来的心跳",(int)nodeID);
			ResourceManager::GetInstance().GetNodeFromID(nodeID)->SetState(Running);
			if (ResourceManager::GetInstance().GetNodeFromID(nodeID))
			{
				ResourceManager::GetInstance().GetNodeFromID(nodeID)->SetState(Running);
			}
			else
			{
				LogManager::GetInstance().WriteMessage("HeartBeatReadHandle::HandleEnter 无效的结点发来的心跳包:%d", (int)nodeID);
			}

		}



		return 0;
	}

	int HeartBeatReadHandle::Handle(void *ptr)
	{
		return 0;
	}

	int HeartBeatReadHandle::HandleClose(void *ptr)
	{
		return 0;
	}

}

