#include "HeartBeatWriteHandle.h"
#include "../Core/Framework.h"
#include <iostream>
namespace NetCom
{
	HeartBeatWriteHandle::HeartBeatWriteHandle(long startInterval, long periodicInterval)
		:m_timer(new Timer(startInterval, periodicInterval))
	{
		m_heartBeatPack.FillData(0);
	}


	HeartBeatWriteHandle::~HeartBeatWriteHandle()
	{
	}

	int HeartBeatWriteHandle::HandleEnter(void *ptr)
	{
		
		m_timer->start(TimerCallback<HeartBeatWriteHandle>(*this, &HeartBeatWriteHandle::TimerFunction));
		return 0;
	}

	int HeartBeatWriteHandle::Handle(void *ptr)
	{
		return 0;
	}

	int HeartBeatWriteHandle::HandleClose(void *ptr)
	{
		m_timer->stop();
		delete m_timer;
		return 0;
	}

	void HeartBeatWriteHandle::TimerFunction(Timer & timer)
	{

		Framework::GetInstance().GetTransportStratagy()->Send(111,m_heartBeatPack.Data(),
			m_heartBeatPack.GetPackageSize());
		//std::cout << "timer coming in" << std::endl;
	}

}

