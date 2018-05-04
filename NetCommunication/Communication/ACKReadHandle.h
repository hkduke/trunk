#pragma once
#include "ACKHandle.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT ACKReadHandle:public ACKHandle
	{
	public:
		ACKReadHandle();
		~ACKReadHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;
	};

}

