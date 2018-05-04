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
	//数据分包后的整体数据压入包内；放入发布者主题列表内
	int TopicPublisherReadHandle::HandleEnter(void *ptr)
	{
		//对主题包进行分解
		//对发布的主题包分包后，加入全局列表中
		TopicPublisherPack pack;
		pack.SetData((BYTE*)ptr, ToolClass::GetPacketSize(ptr));
		if (ToolClass::GetSourceDevID(ptr)
			== ResourceManager::GetInstance().GetCurrentNode()->GetNodeID())
		{
			return 0;
		}
		EPackType type =(EPackType) ToolClass::GetPacketType(ptr);
		//获取ID，检测是否是本地的发送的广播，如果是则忽略，如果不是则进行分包
		unsigned short id = ToolClass::GetSourceDevID(ptr);
		std::list<Participator*>  list = pack.PaserPack((BYTE*)ptr, ToolClass::GetPacketSize(ptr));
		LogManager::GetInstance().WriteMessage("TopicPublisherReadHandle::HandleEnter 收到来自节点ID：%d的主题信息", (int)id);
		//遍历全部的包，如果包在全局存在，则删除，不存在则加入,如果存在检测参与者主题是否全部存在
		//如果是定阅者则加入本地列表中，如果是发布者报文，检查如果本地发布该消息，则发布定阅者消息
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
		//如果获得的是发布包，则看看本地有没有订阅该主题，如果订阅了则发送本地订阅包
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
