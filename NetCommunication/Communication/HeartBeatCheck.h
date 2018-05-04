#pragma once
#include "../Core/Export.h"
#include "../Core/Timer.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT HeartBeatCheck
	{
	public:
		HeartBeatCheck();
		~HeartBeatCheck();
		void Start(long startInterval = 0, long periodicInterval = 0);
		void Stop();

	private:
		Timer * m_timer;
		void Run(Timer& timer);
	};

}

