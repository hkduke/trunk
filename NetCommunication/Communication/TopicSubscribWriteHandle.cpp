#include "TopicSubscribWriteHandle.h"
#include "../Core/TopicSubscribPack.h"
#include "../Core/Framework.h"
namespace NetCom
{
	TopicSubscribWriteHandle::TopicSubscribWriteHandle()
	{
	}

	//��
	TopicSubscribWriteHandle::TopicSubscribWriteHandle(UINT subscribID)
		:m_subscribID(subscribID)
	{
		
	}

	TopicSubscribWriteHandle::~TopicSubscribWriteHandle()
	{
	}

	//���ö��ĺ�
	void TopicSubscribWriteHandle::SetSubscribID(UINT subscribID)
	{
		m_subscribID = subscribID;
	}

	int TopicSubscribWriteHandle::HandleEnter(void *ptr)
	{
		//�Ѷ�������ID�ŷ������

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
