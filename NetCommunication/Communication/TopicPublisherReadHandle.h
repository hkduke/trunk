#pragma once
#include "../Communication/TopicPublisherHandle.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT TopicPublisherReadHandle:public TopicPublisherHandle
	{
	public:
		TopicPublisherReadHandle();
		~TopicPublisherReadHandle();

		virtual int HandleEnter(void *ptr);


		virtual int Handle(void *ptr);


		virtual int HandleClose(void *ptr);

	};

}


