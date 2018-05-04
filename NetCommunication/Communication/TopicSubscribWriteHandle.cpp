#include "TopicSubscribWriteHandle.h"
#include "../Core/TopicSubscribPack.h"
#include "../Core/Framework.h"
namespace NetCom
{
	TopicSubscribWriteHandle::TopicSubscribWriteHandle()
	{
	}

	//带
	TopicSubscribWriteHandle::TopicSubscribWriteHandle(UINT subscribID)
		:m_subscribID(subscribID)
	{
		
	}

	TopicSubscribWriteHandle::~TopicSubscribWriteHandle()
	{
	}

	//设置订阅号
	void TopicSubscribWriteHandle::SetSubscribID(UINT subscribID)
	{
		m_subscribID = subscribID;
	}

	int TopicSubscribWriteHandle::HandleEnter(void *ptr)
	{
		//把定阅主题ID号封包后发送

		TopicSubscribPack pack(m_subscribID);
		pack.FillData(0);

		Framework::GetInstance().GetTransportStratagy()->Send(pack.Data(), pack.GetPackTotalSize());

		return 0;
	}

	int TopicSubscribWriteHandle::Handle(void *ptr)
	{
		return 0;
	}

	int TopicSubscribWriteHandle::HandleClose(void *ptr)
	{
		return 0;
	}

}
