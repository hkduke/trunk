#pragma once
#include "../Communication/NodeDirectoryHandle.h"
//��Ҫ�����Ŀ¼�����Ϣ�ĵ���ʱ�Ķ��¼�
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
		NodeJoinWriteHandle * m_writeHandle;//Ҫ��ע���¼��Ľ����
	};



}