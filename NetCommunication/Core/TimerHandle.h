#pragma once
#include "CoreCommon.h"
#include "EventHandle.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT TimerHandle :public EventHandle
	{
	public:
		TimerHandle();
		virtual ~TimerHandle();
	};


}


