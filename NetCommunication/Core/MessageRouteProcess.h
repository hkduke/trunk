#pragma once

// 消息路由线程
#include "EventManager.h"
#include "../Core/RunnableAdapter.h"
#include "../Core/Thread.h"
namespace NetCom
{
	class MessageRouteProcess 
	{
	public:
		MessageRouteProcess();
		~MessageRouteProcess();

		void Init();

		virtual void Run();
		EventManager * GetEventManager();
		Thread *_thread;
		
	private:
		EventManager * m_pEventManager;	// 时间管理器
	};

}

