#include "TopicPublisherWriteHandle.h"
#include "../Core/LogManager.h"
#include "../Core/TopicPublisherPack.h"
#include "../Core/Framework.h"
#include "../Core/ResourceManager.h"
namespace NetCom
{
	TopicPublisherWriteHandle::TopicPublisherWriteHandle()
	{
	}


	TopicPublisherWriteHandle::~TopicPublisherWriteHandle()
	{
	}
	//触发写事件，发送主题，以后发送策略会改为全局，现在用局部代替，应该全部节点接收
	int TopicPublisherWriteHandle::HandleEnter(EPackType ptr)
	{
		TopicPublisherPack topicPack;
		SocketAddress sendSocket("255.255.255.255", NodeDiscover::GetInstance().m_sendPort);
		topicPack.FillData(TopicDiscribe);
		// Framework::GetInstance().GetTransportStratagy()->Send(topicPack.Data(), topicPack.GetPackTotalSize());
		NodeDiscover::GetInstance().m_sendSocket->sendTo(topicPack.Data(),
			topicPack.GetPackageSize(), sendSocket);
		LogManager::GetInstance().WriteMessage(std::string("TopicPublisherWriteHandle::HandleEnter 发送主题定阅信息"));
		return 0;
	}

	int TopicPublisherWriteHandle::Handle(void *ptr)
	{
		return 0;
	}

	int TopicPublisherWriteHandle::HandleClose(void *ptr)
	{
		return 0;
	}

}


