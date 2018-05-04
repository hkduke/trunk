#pragma once
#include "../Communication/NodeDirectoryHandle.h"
//主要负责对目录结点信息的到达时的读事件
namespace NetCom
{
	class WaitDicHand;
	class NodeDirectoryPack;
	class NodeJoinWriteHandle;
	class NETCOMMUNICATION_EXPORT NodeDirectoryReadHandle :public NodeDirectoryHandle
	{
	public:
		NodeDirectoryReadHandle();
		virtual ~NodeDirectoryReadHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void * ptr) override;


		virtual int HandleClose(void *ptr) override;

	private:
		NodeJoinWriteHandle * m_writeHandle;//要求注册事件的结点句柄
	};



}