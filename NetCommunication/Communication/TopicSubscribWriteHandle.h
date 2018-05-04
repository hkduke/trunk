#pragma once
#include "TopicSubscribHandle.h"
namespace NetCom
{
	class TopicSubscribWriteHandle :public TopicSubscribHandle
	{
	public:
		TopicSubscribWriteHandle();

		TopicSubscribWriteHandle(UINT subscribID);//带ID号构造

		~TopicSubscribWriteHandle();

		void SetSubscribID(UINT subscribID);//设置定阅ID

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	private:

		UINT m_subscribID;//订阅者主题ID

	};
}


