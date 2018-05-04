#include "NodeJoinWriteHandle.h"
#include "../Core/NodeBase.h"
#include"../Core/ResourceManager.h"
#include "../Core/NodeJoinPack.h"
#include "../Core/WaitDicHand.h"
#include "../Core/Framework.h"
#include "../Core/NodeDirectoryPack.h"
#include "../Communication/NodeDirectoryReadHandle.h"
#include "../Communication/TransportSendStrategy.h"
#include "../Communication/Transport.h"
#include "../Core/EventManager.h"
#include "../Sockets/DatagramSocket.h"
#include "../NodeDiscover/NodeDiscover.h"
namespace NetCom {

	NodeJoinWriteHandle::NodeJoinWriteHandle()
	{
	}


	NodeJoinWriteHandle::~NodeJoinWriteHandle()
	{
	}

	//节点加入发送报文
	int NodeJoinWriteHandle::HandleEnter(void *ptr)
	{
		//在发送报文之前，创建资源管理器后，当前结点要加入节点列表中

		//发送结点报文
		NodeJoinPack nodeJoinPack;
		nodeJoinPack.FillData(0);
		//std::cout << "NodeJoinSize:"<<nodeJoinPack.GetPackTotalSize() << std::endl;
		//现用	TransportSendStrategy全局类发送对象
		//Framework::GetInstance().GetTransportStratagy()->Send(nodeJoinPack.Data(), nodeJoinPack.GetPackTotalSize());

		/*测试用*/
		SocketAddress sendSocket("255.255.255.255", NodeDiscover::GetInstance().m_sendPort);
		std::cout<<NodeDiscover::GetInstance().m_sendSocket->sendTo(nodeJoinPack.Data(), nodeJoinPack.GetPackageSize(),sendSocket)<<std::endl;
		/*测试用*/


		//开启定时器功能计算是否超时发送
		//设置目录更新
		
		//把结点目录读取加入事件处理队列中,先加入
		m_directHandle = new NodeDirectoryReadHandle;
		Framework::GetInstance().GetEventManager()->RegisterEvent(m_directHandle, NetCom::NodeDirectory_Read);
		
		m_waitDicHand =new WaitDicHand(10);
		Framework::GetInstance().GetEventManager()->RegisterEvent(m_waitDicHand, NetCom::TimeWait);
		return 1;
	}

	int NodeJoinWriteHandle::Handle(void *ptr)
	{
		return 1;
	}

	int NodeJoinWriteHandle::HandleClose(void *ptr)
	{
		m_waitDicHand->Death();
		m_directHandle->Death();
		delete m_waitDicHand;
		delete m_directHandle;
		return 1;
	}

	int NodeJoinWriteHandle::TimeOutDel(void *ptr)
	{
		return 1;
	}

}

