#pragma once
#include "../Core/EventHandle.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT ACKHandle:public EventHandle
	{
	public:
		ACKHandle();
		~ACKHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	};

}

