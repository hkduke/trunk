#include "Framework.h"
#include "../Core/Publisher.h"
#include "../Core/Subscribe.h"
#include "../Core/CoreComponent.h"
#include "../Communication/NodeJoinWriteHandle.h"

#include"../Core/Any.h"
#include "../Communication/NodeJoinReadHandle.h"
#include "../Communication/TransportSendStrategy.h"
#include "../core/WaitDicHand.h"
#include "../Communication/NodeDirectoryReadHandle.h"
#include "../Communication/NodeDirectoryWriteHandle.h"
#include "../Core/NodeDirectoryPack.h"
#include"../core/CoreComponent.h"
#include"../Sockets/IPAddress.h"
#include "../Sockets/Socket.h"
#include "../Sockets/DatagramSocket.h"
#include "../Communication/NodeExitReadHandle.h"
#include"../core/MessageTransePack.h"
#include "../Core/CommonTool.h"
#include"../Core/NodeJoinPack.h"
#include "../Core/Framework.h"
#include "../Core/DateTime.h"
#include "../Core/Timestamp.h"
#include "../Communication/NodeJoinWriteHandle.h"
#include "../Core/MessageRouteProcess.h"
#include "../Core/SingletonHolder.h"
#include "../Core/UserInterface.h"
#include "../Core/IniFileConfiguration.h"
namespace NetCom
{

	Framework::Framework()
		:m_strategy(new TransportSendStrategy)
	{
	}


	Framework::~Framework()
	{
	}

	int Framework::Init()
	{
		m_pUserInterface = &UserInterface::GetInstance();
		m_pUserInterface->Init();

		ResourceManager::GetInstance().Start();
		std::string ip = Config("IpAddress");
		ResourceManager::GetInstance().SetCurrentIp(ip);

		EventManager::GetInstance().Init();
		NodeBase * curNode = ResourceManager::GetInstance().GetCurrentNode();

		m_nodediscover = new NodeDiscover();
		m_nodediscover->SetCurrentNode(curNode);
		m_nodediscover->SetRecivePort(514);
		m_nodediscover->SetSendPort(514);

		EventManager::GetInstance().Run();
		m_nodediscover->Init();		
		  
		m_runnable= new RunnableAdapter<NodeDiscover>(*m_nodediscover, &NodeDiscover::StartDiscover);
		 m_nodeDiscoverThread.start(*m_runnable);
		return 0;
	}


	void Framework::Heartbeat()
	{
	}



	ITransportSendStrategy * Framework::GetTransportStratagy()
	{
		return m_strategy;
	}

	EventManager * Framework::GetEventManager()
	{
		return m_eventManager;
	}
	
	NetCom::ResourceManager* Framework::GetResourceManager()
	{
		return &ResourceManager::GetInstance();
	}
	NodeDiscover * Framework::GetNodeDiscover()
	{
		return m_nodediscover;
	}

	NetCom::UserInterface * Framework::GetUserInterface()
	{
		return m_pUserInterface;
	}

	namespace
	{
		static SingletonHolder<Framework> m_app;
	}

	NetCom::Framework& Framework::GetInstance()
	{
		return *m_app.get();
	}
	std::string Framework::Config(std::string item)
	{
		AutoPtr<IniFileConfiguration> pConf(new IniFileConfiguration("./Config/NetConf.ini"));
		std::string ip = pConf->getString("NetCommunication."+ item);
		return ip;
	}
}


