#include "NodeDirectoryWriteHandle.h"
#include "../Communication/NodeDirectoryHandle.h"
#include "../Core/NodeDirectoryPack.h"
#include "../Core/Framework.h"
#include "../Sockets/DatagramSocket.h"
#include "../NodeDiscover/NodeDiscover.h"
#include "../Core/LogManager.h"
namespace NetCom
{
	NodeDirectoryWriteHandle::NodeDirectoryWriteHandle()
	{

	}

	NodeDirectoryWriteHandle::~NodeDirectoryWriteHandle()
	{
	}

	int NodeDirectoryWriteHandle::HandleEnter(void *ptr)
	{
		//封包报文，传送
		NodeDirectoryPack directoryPack;
		directoryPack.FillData();
		//Framework::GetInstance().GetTransportStratagy()->Send(directoryPack.Data(), directoryPack.GetPackTotalSize());
		//测试用
		SocketAddress sendSocket("255.255.255.255",NodeDiscover::GetInstance().m_sendPort);
		NodeDiscover::GetInstance().m_sendSocket->sendTo(directoryPack.Data(),
			directoryPack.GetPackTotalSize(), sendSocket);
		
		LogManager::GetInstance().WriteMessage("NodeDirectoryWriteHandle::HandleEnter，目录包发送完成");
		return -1;
	}

	int NodeDirectoryWriteHandle::Handle(void * ptr)
	{
		return -1;
	}

	int NodeDirectoryWriteHandle::HandleClose(void *ptr)
	{
		return -1;
	}

}

