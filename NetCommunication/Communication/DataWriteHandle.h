#pragma once
#include "EventHandle.h"
#include <string.h>
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT  DataWriteHandle : public EventHandle
	{
	public:
		DataWriteHandle();
		~DataWriteHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	};
}


