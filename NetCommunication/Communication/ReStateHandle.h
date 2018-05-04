#pragma once
#include "../Core/EventHandle.h"
namespace NetCom
{
	class ReStateHandle:public EventHandle
	{
	public:
		ReStateHandle();
		~ReStateHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	};

}

