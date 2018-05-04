#pragma once
#include "../Core/EventHandle.h"

namespace NetCom
{
	class NodeExitHandle :
		public EventHandle
	{
	public:
		NodeExitHandle();
		~NodeExitHandle();

		virtual int HandleEnter(void *ptr);

		virtual int Handle(void *ptr);

		virtual int HandleClose(void *ptr);

	};
}


