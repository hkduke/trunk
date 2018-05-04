#pragma once
//���ฺ������Ѿ�������ɵĽ��
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


