#pragma once
//该类负责加入已经建立完成的结点
#include "../Communication/NodeJoinHandle.h"

namespace NetCom
{
	class NodeDirectoryWriteHandle;
	class NETCOMMUNICATION_EXPORT NodeJoinReadHandle:public NodeJoinHandle
	{
		
	public:
		NodeJoinReadHandle();
		~NodeJoinReadHandle();
		
		virtual int HandleEnter(void *ptr) override;

		

		virtual int Handle(void *ptr) override;
	

		virtual int HandleClose(void *ptr) override;
	private:
		NodeDirectoryWriteHandle * m_nodeWriteHand;

	};

}


