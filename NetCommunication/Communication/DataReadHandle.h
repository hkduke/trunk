#pragma once
#include "../Core/EventHandle.h"
//#include "../Core/PackManager.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT DataReadHandle :public EventHandle
	{
	public:
		DataReadHandle();
		~DataReadHandle();
		virtual int  HandleEnter(void *ptr);

		// 事件处理 需重新实现
		virtual int Handle(void *ptr);

		// 事件关闭 需重新实现
		virtual int HandleClose(void *ptr);
		
	};
}


