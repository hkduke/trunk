#pragma once
#include "../Communication/NodeDirectoryHandle.h"
#include "../Communication/TransportSendStrategy.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT NodeDirectoryWriteHandle:public NodeDirectoryHandle
	{
	public:
		NodeDirectoryWriteHandle();
		virtual ~NodeDirectoryWriteHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void * ptr) override;


		virtual int HandleClose(void *ptr) override;


	};

}