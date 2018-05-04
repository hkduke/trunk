#pragma once
#include "../Core/EventHandle.h"
#include "../Core/TimerHandle.h"
#include<../Core/Timer.h>
namespace NetCom
{
	class NodeDirectoryWriteHandle;
	class WaitSmallestHandle:public TimerHandle
	{
	public:
		WaitSmallestHandle(double timeCount,int number);
		~WaitSmallestHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	protected:
		int m_numberN;
		double m_timeCount;
		NodeDirectoryWriteHandle* m_writeHandle;
		Timer* m_timer;
	private:
		void ThreadAction(Timer& timer);
	};
}


