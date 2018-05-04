#pragma once
#include "../Core/EventHandle.h"
#include "../Core/TimerHandle.h"

//本类继承自TimerHandle事件，处理时间内处理情况
namespace NetCom
{
	class NodeJoinWriteHandle;
	class NodeDirectoryReadHandle;
	class Timer;
	class NETCOMMUNICATION_EXPORT WaitDicHand:public TimerHandle
	{
	public:
		WaitDicHand(double m_timeCount);

		~WaitDicHand();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

		void CheckTimeOutState(Timer& timer);

	public:

		double m_timeCount;//计时时间

		Timer* m_timer;//计时时钟
	};


}


