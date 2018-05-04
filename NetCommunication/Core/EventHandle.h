#pragma once
//#include <thread>
// 事件处理接口
#include "CoreCommon.h"
#include "../Core/Types.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT EventHandle
	{
	public:
		EventHandle(EventTypeHandle type);
		EventHandle();
		~EventHandle();
		// 事件进入 需重新实现(执行初始化动作 , 进入执行一次)
		virtual int  HandleEnter(void *ptr);

		// 事件处理 需重新实现
		virtual int Handle(void *ptr);

		// 事件关闭 需重新实现
		virtual int HandleClose(void *ptr);
		void SetEventType(EventTypeHandle type);
		EventTypeHandle GetEventType();
		void Activate();
		void Death();
		bool isActivate();
		void SetExecuteCount(UInt64 count);
		UInt64 GetExecuteCount();
		void SetDataLen(UInt32 len);
		UInt32 GetDataLen();
		void SetDataPtr(void * data);
		UInt64 & ModifyExecuteCount();
		// 设置事件优先级
		void SetPriority(int priority);
		virtual int Priority(void) const;
		void * GetAppendData();
		bool Copy(void * data, UInt32 len);
		bool m_MessageActive;

		EventTypeHandle m_eventType;
		int m_nPriority;	// 事件优先级
		void * m_data;
		UInt32 m_packLen;
		UInt64 m_executeCount;
	};
}

