#pragma once
#include "../Communication/NodeExitHandle.h"
namespace NetCom
{
	class NodeDirectoryReadHandle;

	class NodeDirectoryWriteHandle;

	class WaitSmallestHandle;
	class  NETCOMMUNICATION_EXPORT NodeExitReadHandle:public NodeExitHandle
	{
	public:
		NodeExitReadHandle();
		~NodeExitReadHandle();

		virtual int HandleEnter(void *ptr,bool isBeartHeart=false) ;


		virtual int Handle(void *ptr) ;


		virtual int HandleClose(void *ptr) ;
	private:
		WaitSmallestHandle* m_timeHandle;
		NodeDirectoryWriteHandle* m_nodeWriteHand;
		NodeDirectoryReadHandle* m_joinHandle;
	};

}


