#include"NodeJoinHandle.h"

// #include "Poco/Net/ServerSocket.h"
// #include "Poco/Net/StreamSocket.h"
// #include "Poco/Net/SocketStream.h"
// #include "Poco/Net/SocketAddress.h"
#include "../Core/NodeBase.h"
#include <string>

namespace NetCom
{
	NodeJoinHandle::NodeJoinHandle()
	{
		
	}


	NodeJoinHandle::~NodeJoinHandle()
	{
	}

	int NodeJoinHandle::HandleEnter(void *ptr)
	{
		NodeBase *pnb = static_cast<NodeBase *>(ptr);
		assert(pnb);
	
		NodeAddr   addr = pnb->GetNodeAddr();
		// 	AnyNet::SocketAddress sa(addr.GetAddress().data(), 8080);
		// 	AnyNet::ServerSocket srv(sa);// does bind + listen
		//向目录管理器中加入节点


		return -1;
	}

	int NodeJoinHandle::Handle(void *ptr)
	{
		
		return -1;
	}

	int NodeJoinHandle::HandleClose(void *ptr)
	{
		return -1;
	}


	void NodeJoinHandle::run()
	{
		
	}

}
