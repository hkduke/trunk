#pragma once
#include "../Communication/TopicPublisherHandle.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT TopicPublisherWriteHandle:public TopicPublisherHandle
	{
	public:
		TopicPublisherWriteHandle();
		~TopicPublisherWriteHandle();

		virtual int HandleEnter(EPackType ptr) ;


		virtual int Handle(void *ptr) ;


		virtual int HandleClose(void *ptr) ;

		

	};

}

