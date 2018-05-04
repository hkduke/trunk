#pragma once
#include "HeartBeatHandle.h"
namespace NetCom
{
	class HeartBeatReadHandle:public HeartBeatHandle
	{
	public:
		HeartBeatReadHandle();
		~HeartBeatReadHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	};
}


