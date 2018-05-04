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

	//�ڵ���뷢�ͱ���
	int NodeJoinWriteHandle::HandleEnter(void *ptr)
	{
		//�ڷ��ͱ���֮ǰ��������Դ�������󣬵�ǰ���Ҫ����ڵ��б���

		//���ͽ�㱨��
		NodeJoinPack nodeJoinPack;
		nodeJoinPack.FillData(0);
		//std::cout << "NodeJoinSize:"<<nodeJoinPack.GetPackTotalSize() << std::endl;
		//����	TransportSendStrategyȫ���෢�Ͷ���
		//Framework::GetInstance().GetTransportStratagy()->Send(nodeJoinPack.Data(), nodeJoinPack.GetPackTotalSize());

		/*������*/
		SocketAddress sendSocket("255.255.255.255", NodeDiscover::GetInstance().m_sendPort);
		std::cout<<NodeDiscover::GetInstance().m_sendSocket->sendTo(nodeJoinPack.Data(), nodeJoinPack.GetPackageSize(),sendSocket)<<std::endl;
		/*������*/


		//������ʱ�����ܼ����Ƿ�ʱ����
		//����Ŀ¼����
		
		//�ѽ��Ŀ¼��ȡ�����¼����������,�ȼ���
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

