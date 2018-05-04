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

		//���ݷ�������Ϣ���ı�ڵ�Ŀ¼�е�����״̬����ȡ���͸ð���NodeId
		//���ڵ�״̬����Ϊ����
		if (ResourceManager::GetInstance().IsNodeExit(nodeID))
		{
			//LogManager::GetInstance().WriteMessage("HeartBeatCommit::Run�������յ��ڵ�ID��%d����������",(int)nodeID);
			ResourceManager::GetInstance().GetNodeFromID(nodeID)->SetState(Running);
			if (ResourceManager::GetInstance().GetNodeFromID(nodeID))
			{
				ResourceManager::GetInstance().GetNodeFromID(nodeID)->SetState(Running);
			}
			else
			{
				LogManager::GetInstance().WriteMessage("HeartBeatReadHandle::HandleEnter ��Ч�Ľ�㷢����������:%d", (int)nodeID);
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

