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
		//������ģ�����
		NodeDirectoryPack directoryPack;
		directoryPack.FillData();
		//Framework::GetInstance().GetTransportStratagy()->Send(directoryPack.Data(), directoryPack.GetPackTotalSize());
		//������
		SocketAddress sendSocket("255.255.255.255",NodeDiscover::GetInstance().m_sendPort);
		NodeDiscover::GetInstance().m_sendSocket->sendTo(directoryPack.Data(),
			directoryPack.GetPackTotalSize(), sendSocket);
		
		LogManager::GetInstance().WriteMessage("NodeDirectoryWriteHandle::HandleEnter��Ŀ¼���������");
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

