#include "TopicSubscribReadHandle.h"
#include "../Core/TopicSubscribPack.h"
#include "../Core/Subscribe.h"
#include"../Core/Framework.h"
namespace NetCom
{
	TopicSubscribReadHandle::TopicSubscribReadHandle()
	{
	}


	TopicSubscribReadHandle::~TopicSubscribReadHandle()
	{
	}

	int TopicSubscribReadHandle::HandleEnter(void *ptr)
	{
		TopicSubscribPack pack;
		pack.PaserPack();
		//获取订阅者的主题号和节点号，创建新订阅者加入订阅者列表
		Subscribe* newSubscribe = new Subscribe;
		
		Framework::GetInstance().AddSubscribe(newSubscribe);

		//如果有响应则调用响应句柄



		return 0;
	}

	int TopicSubscribReadHandle::Handle(void *ptr)
	{
		return 0;
	}

	int TopicSubscribReadHandle::HandleClose(void *ptr)
	{
		return 0;
	}

}
