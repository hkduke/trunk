#pragma once
#include "TopicSubscribHandle.h"
namespace NetCom
{
	class TopicSubscribReadHandle:public TopicSubscribHandle
	{
	public:
		TopicSubscribReadHandle();
		~TopicSubscribReadHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	};

}

