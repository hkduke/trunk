#pragma once
#include "../Communication/NodeJoinHandle.h"


namespace NetCom
{
	class WaitDicHand;
	class NodeDirectoryPack;
	class NodeDirectoryReadHandle;
	class TransportSendStrategy;
	class Transport;
	class NETCOMMUNICATION_EXPORT NodeJoinWriteHandle:public NodeJoinHandle
	{
	public:
		NodeJoinWriteHandle();
		virtual ~NodeJoinWriteHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

		//处理时间是否到期的回调函数
		virtual int TimeOutDel(void *ptr);
	public:
		Transport * m_transport;
		WaitDicHand* m_waitDicHand;//定时器句柄
		NodeDirectoryReadHandle *m_directHandle;//要调用的读目录操作事件的句柄
	};
}


