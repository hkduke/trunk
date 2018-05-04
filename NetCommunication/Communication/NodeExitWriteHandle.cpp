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
		//创建结点退出报文，发送广播,确认自己退出的消息
		NodeExitPack nodeExitPack;
		nodeExitPack.FillData(0);
		/*TransportSendStrategy strategy;
		strategy.Send(nodeExitPack.Data(), nodeExitPack.GetPackTotalSize());*/
		/*测试用*/
		SocketAddress sendSocket("255.255.255.255", NodeDiscover::GetInstance().m_sendPort);
		NodeDiscover::GetInstance().m_sendSocket->sendTo(nodeExitPack.Data(), nodeExitPack.GetPackageSize(), sendSocket) ;
		/*测试用*/
		//清理本身的对象
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

