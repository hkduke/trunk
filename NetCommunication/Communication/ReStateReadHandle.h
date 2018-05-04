#pragma once
#include "ReStateHandle.h"
namespace NetCom
{
	class ReStateReadHandle:public ReStateHandle
	{
	public:
		ReStateReadHandle();
		~ReStateReadHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	};

}

