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
		//��ȡ�����ߵ�����źͽڵ�ţ������¶����߼��붩�����б�
		Subscribe* newSubscribe = new Subscribe;
		
		Framework::GetInstance().AddSubscribe(newSubscribe);

		//�������Ӧ�������Ӧ���



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
