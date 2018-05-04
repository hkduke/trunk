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
	//����д�¼����������⣬�Ժ��Ͳ��Ի��Ϊȫ�֣������þֲ����棬Ӧ��ȫ���ڵ����
	int TopicPublisherWriteHandle::HandleEnter(EPackType ptr)
	{
		TopicPublisherPack topicPack;
		SocketAddress sendSocket("255.255.255.255", NodeDiscover::GetInstance().m_sendPort);
		topicPack.FillData(TopicDiscribe);
		// Framework::GetInstance().GetTransportStratagy()->Send(topicPack.Data(), topicPack.GetPackTotalSize());
		NodeDiscover::GetInstance().m_sendSocket->sendTo(topicPack.Data(),
			topicPack.GetPackageSize(), sendSocket);
		LogManager::GetInstance().WriteMessage(std::string("TopicPublisherWriteHandle::HandleEnter �������ⶨ����Ϣ"));
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


