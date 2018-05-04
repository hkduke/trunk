#include "TopicPublisherReadHandle.h"
#include "../Core/Framework.h"
#include "../Core/TopicPublisherPack.h"
#include "../Core/Publisher.h"
#include "../Core/ResourceManager.h"
#include "../Core/CommonTool.h"
#include "../Communication/TopicPublisherWriteHandle.h"
#include "../Core/Any.h"
#include "../Core/LogManager.h"
namespace NetCom
{
	TopicPublisherReadHandle::TopicPublisherReadHandle()
	{
	}


	TopicPublisherReadHandle::~TopicPublisherReadHandle()
	{
	}
	//���ݷְ������������ѹ����ڣ����뷢���������б���
	int TopicPublisherReadHandle::HandleEnter(void *ptr)
	{
		//����������зֽ�
		//�Է�����������ְ��󣬼���ȫ���б���
		TopicPublisherPack pack;
		pack.SetData((BYTE*)ptr, ToolClass::GetPacketSize(ptr));
		if (ToolClass::GetSourceDevID(ptr)
			== ResourceManager::GetInstance().GetCurrentNode()->GetNodeID())
		{
			return 0;
		}
		EPackType type =(EPackType) ToolClass::GetPacketType(ptr);
		//��ȡID������Ƿ��Ǳ��صķ��͵Ĺ㲥�����������ԣ������������зְ�
		unsigned short id = ToolClass::GetSourceDevID(ptr);
		std::list<Participator*>  list = pack.PaserPack((BYTE*)ptr, ToolClass::GetPacketSize(ptr));
		LogManager::GetInstance().WriteMessage("TopicPublisherReadHandle::HandleEnter �յ����Խڵ�ID��%d��������Ϣ", (int)id);
		//����ȫ���İ����������ȫ�ִ��ڣ���ɾ���������������,������ڼ������������Ƿ�ȫ������
		//����Ƕ���������뱾���б��У�����Ƿ����߱��ģ����������ط�������Ϣ���򷢲���������Ϣ
		if (type == EPackType::TopicDiscribe)
		{
			for (auto it = list.begin(); it != list.end(); ++it)
			{
					for (auto iit = (*it)->GetTopicList().begin(); iit != (*it)->GetTopicList().end(); ++iit)
					{
						if (ResourceManager::GetInstance().IsLocalPublicTopicExit(*iit) && 
							!ResourceManager::GetInstance().IsLocalRelateSubscribTopicExist((*it)->GetParticipatorID(),*iit))
						{
							Subscribe * newSub = new Subscribe((*it)->GetParticipatorID());
							newSub->SetNodeID((*it)->GetNodeID());
							newSub->AddTopic(*iit);
							(*it)->AddTopic(*iit);
							ResourceManager::GetInstance().AddLocalRelationSubscrib(newSub);
						}
					}
			}
			for (auto it = list.begin(); it != list.end(); ++it)
			{
				delete *it;
			}
		}
		//�����õ��Ƿ��������򿴿�������û�ж��ĸ����⣬������������ͱ��ض��İ�
		else if (type == EPackType::TopicPublisher)
		{
			for (auto it = list.begin(); it != list.end(); ++it)
			{
				auto topicList = (*it)->GetTopicList();
				for (auto it = topicList.begin(); it != topicList.end(); ++it)
				{
					if (ResourceManager::GetInstance().IsLocalsubScribTopicExit(*it))
					{
						TopicPublisherWriteHandle handle;
						handle.HandleEnter(EPackType::TopicDiscribe);
					}
				}
			}
		}
		return 0;
		}

		int TopicPublisherReadHandle::Handle(void *ptr)
		{
			return 0;
		}

		int TopicPublisherReadHandle::HandleClose(void *ptr)
		{
			return 0;
		}

	}
