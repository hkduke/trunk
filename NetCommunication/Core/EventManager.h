#pragma once
#include "CoreCommon.h"
#include <queue>
#include "../Reactor/SocketReactor.h"
#include "RunnableAdapter.h"
#include "Thread.h"

namespace NetCom
{
	class EventHandle;
	class EventManager
	{
	public:
		EventManager(EventHandle* event, EventTypeHandle );
		EventManager();
		~EventManager();
		void RegisterEvent(EventHandle* event, EventTypeHandle);
		void RunEventLoop();

		void EventInit();
		void PushEvent(EventHandle* handle);
		void Init();
		void Run();
		std::queue<EventHandle*> m_EventList;
		static EventManager& GetInstance();
		void SetDebug(bool is);
	private:
		Thread * _thread;
		SocketReactor m_reactor;
		FastMutex m_mutex;
		FastMutex m_event_mutex;
		bool m_isDebug;
	};

}

