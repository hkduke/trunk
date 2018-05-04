#pragma once
#include "../Core/EventHandle.h"

namespace NetCom
{
	class PINGHandle:public EventHandle
	{
	public:
		PINGHandle();
		~PINGHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	};

}

