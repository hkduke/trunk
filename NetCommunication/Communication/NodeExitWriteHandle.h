#pragma once
#include "../Core/Export.h"
#include "../Communication/NodeExitHandle.h"
namespace NetCom
{
	class  NETCOMMUNICATION_EXPORT NodeExitWriteHandle:public NodeExitHandle
	{
	public:
		NodeExitWriteHandle();
		~NodeExitWriteHandle();

		virtual int HandleEnter(void *ptr) ;


		virtual int Handle(void *ptr) ;


		virtual int HandleClose(void *ptr) ;

	};

}


