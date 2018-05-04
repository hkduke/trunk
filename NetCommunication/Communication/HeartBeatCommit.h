#pragma once
#include "../Core/Export.h"
#include "../Core/Timer.h"
#include "../Core/HeartBeatPack.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT HeartBeatCommit
	{
	public:
		HeartBeatCommit();
		~HeartBeatCommit();
		void Start(long startInterval = 0, long periodicInterval = 0);
		void Stop();
		
	private:
		Timer * m_timer;
		void Run(Timer& timer);
		HeartBeatPack m_heartBeatePack;
		void Docheck();
	};
}


