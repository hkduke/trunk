#pragma once
#include "ReStateHandle.h"

namespace NetCom
{
	class ReStateWriteHandle:public ReStateHandle
	{
	public:
		ReStateWriteHandle();
		~ReStateWriteHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	};

}

