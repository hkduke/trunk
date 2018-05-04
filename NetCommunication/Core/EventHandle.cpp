#include "EventHandle.h"
#include "CoreCommon.h"
#include <assert.h>
namespace NetCom
{
	EventHandle::EventHandle(EventTypeHandle type):m_MessageActive(true), m_eventType(type), m_executeCount(1)
	{
	}

	EventHandle::EventHandle()
	{
		m_executeCount = 1;
	}

	EventHandle::~EventHandle()
	{
	}

	int EventHandle::HandleEnter(void *ptr)
	{
		return 1;
	}


	int EventHandle::Handle(void *ptr)
	{
		return 1;
	}

	int EventHandle::HandleClose(void *ptr)
	{
		return 1;
	}

	void EventHandle::SetEventType(EventTypeHandle type)
	{
		m_eventType = type;
	}

	EventTypeHandle EventHandle::GetEventType()
	{
		return m_eventType;
	}

	void EventHandle::Activate()
	{
		m_MessageActive = true;
	}

	void EventHandle::Death()
	{
		m_MessageActive = false;
	}

	bool EventHandle::isActivate()
	{
		return m_MessageActive;
	}

	void EventHandle::SetExecuteCount(UInt64 count)
	{
		m_executeCount = count;
	}

	NetCom::UInt64 EventHandle::GetExecuteCount()
	{
		return m_executeCount;
	}

	void EventHandle::SetDataLen(UInt32 len)
	{
		m_packLen = len;
	}

	UInt32 EventHandle::GetDataLen()
	{
		return m_packLen;
	}

	void EventHandle::SetDataPtr(void * data)
	{
		m_data = data;
	}

	NetCom::UInt64 & EventHandle::ModifyExecuteCount()
	{
		return m_executeCount;
	}

	void EventHandle::SetPriority(int priority)
	{

	}

	int EventHandle::Priority(void) const
	{
		return m_nPriority;
	}

	void * EventHandle::GetAppendData()
	{
		return m_data;
	}

	bool EventHandle::Copy(void * data, UInt32 len)
	{
		m_data = MALLOC(len);
		if (!m_data)return false;
		memset(m_data, 0, len);
		memcpy(m_data, data, len);
		return true;
	}

}
