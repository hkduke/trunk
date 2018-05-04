#pragma once
#include "../Core/EventHandle.h"

namespace NetCom
{
	class NodeDirectoryHandle :
		public EventHandle
	{
	public:
		NodeDirectoryHandle();
		~NodeDirectoryHandle();

		virtual int HandleEnter(void *ptr);

		virtual int Handle(void * ptr);

		virtual int HandleClose(void *ptr);



	};
}


