#pragma once
#include "../Core/EventHandle.h"

namespace NetCom
{

	class NETCOMMUNICATION_EXPORT DataHandle :public EventHandle
	{
	public:
		DataHandle();
		~DataHandle();

		virtual int HandleEnter(void *ptr);

		virtual int Handle(void *ptr);

		virtual int HandleClose(void *ptr);

	};
}


