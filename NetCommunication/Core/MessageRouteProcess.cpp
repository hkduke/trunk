#include "MessageRouteProcess.h"
#include "../Core/Framework.h"



namespace NetCom
{
	MessageRouteProcess::MessageRouteProcess()
	{
		Init();
	}

	MessageRouteProcess::~MessageRouteProcess()
	{
	}

	void MessageRouteProcess::Init()
	{
		m_pEventManager = new EventManager;
		bool b = Framework::GetInstance().ConfigBool("IsDebugRecive");
		m_pEventManager->SetDebug(b);
		_thread = new Thread;
		
	}

	void MessageRouteProcess::Run()
	{		RunnableAdapter<EventManager>* runnable = new RunnableAdapter<EventManager>(*m_pEventManager, &EventManager::RunEventLoop);		_thread->start(*runnable);		//_thread->join();
	}

	NetCom::EventManager * MessageRouteProcess::GetEventManager()
	{
		return m_pEventManager;
	}

}

