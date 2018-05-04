#pragma once
#include "../Core/EventHandle.h"
namespace NetCom
{
	class HeartBeatHandle:public EventHandle
	{
	public:
		HeartBeatHandle();
		~HeartBeatHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	};
}



