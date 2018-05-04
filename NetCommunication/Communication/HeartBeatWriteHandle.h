#pragma once
#include "HeartBeatHandle.h"
#include "../Core/HeartBeatPack.h"
#include"../Core/Timer.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT HeartBeatWriteHandle:public HeartBeatHandle
	{
	public:
		HeartBeatWriteHandle(long startInterval = 0, long periodicInterval = 0);
		~HeartBeatWriteHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

		void TimerFunction(Timer& timer);
	private:
		Timer* m_timer;
		HeartBeatPack m_heartBeatPack;

	private:

		
	};

}

