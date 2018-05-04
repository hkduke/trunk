#include "EventManager.h"
#include "EventHandle.h"
#include "CommonTool.h"
#include "TopicPublisherPack.h"
#include "../Core/SingletonHolder.h"
#include "../Core/LogManager.h"
namespace NetCom
{
	EventManager::EventManager()
	{
		
	}


	EventManager::EventManager(EventHandle* event, EventTypeHandle)
	{

	}

	EventManager::~EventManager()
	{
	}

	void EventManager::RegisterEvent(EventHandle* event, EventTypeHandle)
	{
		
	}

	void EventManager::RunEventLoop()
	{
		
		while (true)
		{
			
			if (m_EventList.empty())
			{
				if(m_isDebug)LogManager::GetInstance().WriteMessage("EventManager::RunEventLoop:事件队列为空开始休眠");
				Thread::trySleep(static_cast<long>(10));
				continue;
			}
			
			EventHandle * event = m_EventList.front();
			
			void * data = event->GetAppendData();

			if (data == nullptr || event->GetExecuteCount()<=0)
			{
				m_mutex.lock();
				m_EventList.pop();
				m_mutex.unlock();
				if (m_isDebug)LogManager::GetInstance().WriteMessage("EventManager::RunEventLoop:事件被处理完成:事件队列大小:%d", (Int32)m_EventList.size());
				delete event;
				event = nullptr;
				if (m_isDebug)LogManager::GetInstance().WriteMessage(":EventManager::RunEventLoop:事件被删除，并且delete");
				continue;
			}

			EventTypeHandle type = event->GetEventType();
			switch (type)
			{
			
			case TopicPublisher_Read:
			{
				event->HandleEnter(data);
				break;
			}
			case TopicPublisher_Write:
			{
				event->HandleEnter(data);
				if (m_isDebug)LogManager::GetInstance().WriteMessage("事件开始处理:TopicPublisher_Write:数据:");
				break;
			}
			case DataPacket_Read:
			{
				event->HandleEnter(data);
				if (m_isDebug)LogManager::GetInstance().WriteMessage("事件开始处理:类型:DataPacket_Read:数据:");
				break;
			}
			case DataPacket_Write:
			{

				break;
			}
			case File_Read:
			{
				event->HandleEnter(data);
				if (m_isDebug)LogManager::GetInstance().WriteMessage("事件开始处理:类型:File_Read:数据:");
				break;
			}
			case Ack_Read:
			{
				event->HandleEnter(data);
				if (m_isDebug)LogManager::GetInstance().WriteMessage("事件开始处理:类型:Ack_Read:数据:");
				break;
			}
			default:
				break;
			}
			event->ModifyExecuteCount()--;
			//m_mutex.unlock();
		}
	}
	void EventManager::EventInit()
	{
		
	}

	void EventManager::PushEvent(EventHandle* handle)
	{
		if (m_isDebug)LogManager::GetInstance().WriteMessage("EventManager::PushEvent:压入事件处理");
		m_mutex.lock();
		m_EventList.push(handle);
		m_mutex.unlock();
		if (m_isDebug)LogManager::GetInstance().WriteMessage("EventManager::PushEvent:压入事件处理完成");
	}

	void EventManager::Init()
	{
		_thread = new Thread;
	}

	void EventManager::Run()
	{
		RunnableAdapter<EventManager>* runnable = new RunnableAdapter<EventManager>(*this, &EventManager::RunEventLoop);
		_thread->start(*runnable);
	}
	namespace
	{
		static SingletonHolder<EventManager> m_EventManager;
	}


	NetCom::EventManager& EventManager::GetInstance()
	{
		return *m_EventManager.get();
	}

	void EventManager::SetDebug(bool is)
	{
		m_isDebug = is;
	}

}


