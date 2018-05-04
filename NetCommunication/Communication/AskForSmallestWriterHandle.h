#pragma once
#include "../Communication/AskForSmallestHandle.h"
namespace NetCom
{
	class AskForSmallestWriterHandle:AskForSmallestHandle
	{
	public:
		AskForSmallestWriterHandle();
		~AskForSmallestWriterHandle();

		virtual int HandleEnter(void *ptr);


		virtual int Handle(void *ptr);


		virtual int HandleClose(void *ptr);

	};


}

