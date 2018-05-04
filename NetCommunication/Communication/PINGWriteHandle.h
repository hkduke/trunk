#pragma once
#include "PINGHandle.h"
namespace NetCom
{
	class PINGWriteHandle:public PINGHandle
	{
	public:
		PINGWriteHandle();
		~PINGWriteHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	};


}
