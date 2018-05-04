#pragma once
#include "TopicSubscribHandle.h"
namespace NetCom
{
	class TopicSubscribWriteHandle :public TopicSubscribHandle
	{
	public:
		TopicSubscribWriteHandle();

		TopicSubscribWriteHandle(UINT subscribID);//��ID�Ź���

		~TopicSubscribWriteHandle();

		void SetSubscribID(UINT subscribID);//���ö���ID

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	private:

		UINT m_subscribID;//����������ID

	};
}


