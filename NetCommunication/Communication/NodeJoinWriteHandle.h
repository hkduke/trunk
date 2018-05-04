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

		//����ʱ���Ƿ��ڵĻص�����
		virtual int TimeOutDel(void *ptr);
	public:
		Transport * m_transport;
		WaitDicHand* m_waitDicHand;//��ʱ�����
		NodeDirectoryReadHandle *m_directHandle;//Ҫ���õĶ�Ŀ¼�����¼��ľ��
	};
}


