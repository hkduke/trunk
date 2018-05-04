#include "NodeExitWriteHandle.h"
#include "../Core/ResourceManager.h"
#include "../Core/NodeBase.h"
#include "../Core/NodeExitPack.h"
#include "../Communication/TransportSendStrategy.h"
#include "../NodeDiscover/NodeDiscover.h"
namespace NetCom{

	NodeExitWriteHandle::NodeExitWriteHandle()
	{
	}


	NodeExitWriteHandle::~NodeExitWriteHandle()
	{
	}


	int NodeExitWriteHandle::HandleEnter(void *ptr)
	{
		//��������˳����ģ����͹㲥,ȷ���Լ��˳�����Ϣ
		NodeExitPack nodeExitPack;
		nodeExitPack.FillData(0);
		/*TransportSendStrategy strategy;
		strategy.Send(nodeExitPack.Data(), nodeExitPack.GetPackTotalSize());*/
		/*������*/
		SocketAddress sendSocket("255.255.255.255", NodeDiscover::GetInstance().m_sendPort);
		NodeDiscover::GetInstance().m_sendSocket->sendTo(nodeExitPack.Data(), nodeExitPack.GetPackageSize(), sendSocket) ;
		/*������*/
		//������Ķ���
		return 0;
	}

	int NodeExitWriteHandle::Handle(void *ptr)
	{
		return 0;
	}

	int NodeExitWriteHandle::HandleClose(void *ptr)
	{
		return 0;
	}

}

