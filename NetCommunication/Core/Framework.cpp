#include "Framework.h"
#include "../Core/Publisher.h"
#include "../Core/Subscribe.h"
#include "../Core/CoreComponent.h"
#include "../Communication/NodeJoinWriteHandle.h"
#include "../Core/RunnableAdapter.h"
#include "../Core/Thread.h"
#include "../Core/SingletonHolder.h"
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
#include "../Core/PluginManager.h"
#include "../Core/Mutex.h"
#include "../Core/WaitDicHand.h"
#include "NodeBase.h"
#include "../Core/SimpleFileChannel.h"
#include "../Core/LogManager.h"
#include "../Core/LogStream.h"
#include "../Core/Timer.h"
#include "../Communication/BlendModeNet.h"
#include "../Communication/AckQueue.h"
#include <locale.h>
#include <tchar.h>

namespace NetCom
{

	Framework::Framework()
		: m_isBlendMode(false)
	{
		m_nodediscover = nullptr;
		m_timer = nullptr;
		m_strategy = nullptr;
		m_eventManager = nullptr;
		m_pUserInterface = nullptr;
		m_pPluginManager = nullptr;
		m_pBlendModeNet = nullptr;
	}


	Framework::~Framework()
	{
		if (m_nodediscover)
		{
			delete m_nodediscover;
		}
		if (m_timer)
		{
			m_timer->stop();
			delete m_timer;
		}
		if (m_strategy)
		{
			delete m_strategy;
		}
		if (m_eventManager)
		{
			delete m_eventManager;
		}

		if (m_pUserInterface)
		{
			delete m_pUserInterface;
		}
		if (m_pPluginManager)
		{
			delete m_pPluginManager;
		}
	}

	int Framework::Init()
	{
		m_isAck = ConfigBool("FileACK");
		if (m_isAck)
		{
			m_pAckQueueManager = new AckQueueManager;
			m_pAckQueueManager->Run();
		}



		LogManager::GetInstance().LogInit();
		_tsetlocale(LC_ALL, _T("chs"));
		LogManager::GetInstance().WriteMessage("ReceiveQueue::Push:开始收到网络数据压入缓冲区");

		LoadCommunicationPlugin();
		m_pUserInterface = &UserInterface::GetInstance();
		m_pUserInterface->Init();

		ResourceManager::GetInstance().Start();
		std::string ip = ConfigString("IpAddress");
		ResourceManager::GetInstance().SetCurrentIp(ip);

		EventManager::GetInstance().Init();
		EventManager::GetInstance().SetDebug(ConfigBool("IsDebugRecive"));
		NodeBase * curNode = ResourceManager::GetInstance().GetCurrentNode();

		m_nodediscover = new NodeDiscover();
		m_nodediscover->SetCurrentNode(curNode);
		m_nodediscover->SetRecivePort(514);
		m_nodediscover->SetSendPort(514);

		EventManager::GetInstance().Run();
		m_nodediscover->Init();

		m_runnable = new RunnableAdapter<NodeDiscover>(*m_nodediscover, &NodeDiscover::StartDiscover);
		m_nodeDiscoverThread.start(*m_runnable);

		//启动混合模式
		m_isBlendMode = ConfigBool("EnableBlendMode");
		if (m_isBlendMode)
		{
			m_pBlendModeNet = new BlendModeNet;
			m_pBlendModeNet->Init();
		}

		m_strategy = new TransportSendStrategy;



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

	bool Framework::LoadCommunicationPlugin()
	{
		m_pPluginManager = new PluginManager;
		m_pPluginManager->LoadPlugin("E:/work/4Y4B/trunk/Release/TCPTransport");
		return true;
	}

	NetCom::BlendModeNet * Framework::GetBlendModeNet()
	{
		return m_pBlendModeNet;
	}

	NetCom::DataLinkMap * Framework::GetDataLinkMap()
	{
		return m_strategy->GetDataLinkMap();
	}

	NetCom::AckQueueManager * Framework::GetAckQueueManager()
	{
		return m_pAckQueueManager;
	}

	bool Framework::GetIsAck()
	{
		return m_isAck;
	}

	void Framework::RegisterRecvFunction(PackManager::RecvFunc fun, UInt32 topicId)
	{
		ResourceManager::GetInstance().GetPackManager()->Fill(topicId);
		ResourceManager::GetInstance().GetPackManager()->RegisterFunction(fun, topicId);
	}

	namespace
	{
		static SingletonHolder<Framework> m_app;
	}

	NetCom::Framework& Framework::GetInstance()
	{
		return *m_app.get();
	}
	std::string Framework::ConfigString(std::string item)
	{
		AutoPtr<IniFileConfiguration> pConf(new IniFileConfiguration("./Config/NetConf.ini"));
		std::string ip("127.0.0.1");
		//if (pConf->hasProperty(item))
		{
			ip = pConf->getString("NetCommunication." + item);
		}
		//else
		{
			//LogManager::GetInstance().WriteMessage("没有配置此项String数据:%s",item);
		}
		return ip;
	}

	UInt32 Framework::ConfigInt(std::string item)
	{
		AutoPtr<IniFileConfiguration> pConf(new IniFileConfiguration("./Config/NetConf.ini"));
		//if (pConf->hasProperty(item))
		{
			return pConf->getInt("NetCommunication." + item);
		}
		//else
		{
			LogManager::GetInstance().WriteMessage("没有配置此项Int数据:%s", item);
			return 1;
		}
	}

	bool Framework::ConfigBool(std::string item)
	{
		AutoPtr<IniFileConfiguration> pConf(new IniFileConfiguration("./Config/NetConf.ini"));
		//if (pConf->hasProperty(item))
		{
			return pConf->getBool("NetCommunication." + item);
		}
		//else
		{
			//LogManager::GetInstance().WriteMessage("没有配置此项Bool数据:%s", item);
			//return false;// 注意
		}
	}

}


