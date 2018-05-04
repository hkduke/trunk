#pragma once
#include "PINGHandle.h"
namespace NetCom
{
	class PINGReadHandle:public PINGHandle
	{
	public:
		PINGReadHandle();
		~PINGReadHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	};

}


