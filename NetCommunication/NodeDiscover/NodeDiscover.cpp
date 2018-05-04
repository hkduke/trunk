#include "NodeDiscover.h"
#include "../Core/CommonTool.h"
#include "../Communication/NodeJoinReadHandle.h"
#include "../Communication/TransportSendStrategy.h"
#include "../core/WaitDicHand.h"
#include "../Communication/NodeDirectoryReadHandle.h"
#include "../Communication/NodeDirectoryWriteHandle.h"
#include "../Core/NodeDirectoryPack.h"
#include"../core/CoreComponent.h"
#include "../Core/Thread.h"
#include "../Communication/NodeExitReadHandle.h"
#include"../Core/NodeJoinPack.h"
#include "../Core/DateTime.h"
#include "../Core/Timestamp.h"
#include "../Communication/NodeJoinWriteHandle.h"
#include "../Communication/TopicPublisherReadHandle.h"
#include "../Communication/TopicPublisherWriteHandle.h"
#include "../Core/LogManager.h"
#include "../Communication/HeartBeatReadHandle.h"
//#include "../Core/MessageTransePack.h"
#include "../Core/Framework.h"
#include "../Core/EventHandle.h"
#include "../Communication/FileTranseHandle.h"
#include"../Communication/DataWriteHandle.h"
#include "../PackageTypeManager/PackManager.h"
namespace NetCom
{
	NodeDiscover::NodeDiscover()
	{
		m_fun = nullptr;
		m_beatCommit = nullptr;
		m_Manager = nullptr;
		NodeBase* base1 = new NodeBase();
	/*	base1->SetNetStyle(IP_V4_ADDR);
		base1->SetNodeAddrIP("");
		base1->SetState(Stop);*/

	}


	NodeDiscover::~NodeDiscover(void)
	{
		if (m_beatCommit)
		{
			delete m_beatCommit;
		}
		if (m_Manager)
		{
			delete m_Manager;
		}
	}

	void NodeDiscover::DiscoverNode(BYTE* data)
	{

	}

	void NodeDiscover::RegisterHandle(Func  func)
	{
		m_fun = func;
	}

	void NodeDiscover::OnDiscoverNode()
	{

	}

	void NodeDiscover::SetCurrentNode(NetCom::NodeBase* node)
	{
		m_currentNode = node;
	}

	void NodeDiscover::SetSendPort(int port)
	{
		m_sendPort = port;
	}

	void NodeDiscover::SetRecivePort(int port)
	{
		m_receivePort = port;
	}

	//************************************
	// Method:    StartDiscover
	// FullName:  NetCom::NodeDiscover::StartDiscover
	// Access:    public 
	// Returns:   void
	// Qualifier:
	//************************************
	void NodeDiscover::StartDiscover()
	{
		//启动线程中进行包的解析

		char buffer[1024 * 2];
		while (/*!ResourceManager::GetInstance().IsTimeOut()*/1)
		{
			memset(buffer, 0, sizeof(buffer));
			int n = m_receiveSocket->receiveBytes(buffer, sizeof(buffer) - 1);

			buffer[n] = '\0';
			EPackType packageType = (EPackType)ToolClass::GetPacketType(buffer);
			UINT32 nodeID = ToolClass::GetSourceDevID(buffer);
			switch (packageType)
			{
			case NetCom::NodeJoin:
			{
				if (nodeID == ResourceManager::GetInstance().GetCurrentNode()->GetNodeID())
				{
					LogManager::GetInstance().WriteMessage(std::string("收到自己发来的节点加入包"));
					break;
				}

				NodeJoinReadHandle readhandle;
				readhandle.HandleEnter(buffer);
				auto lists = ResourceManager::GetInstance().GetNodeList();
				LogManager::GetInstance().WriteMessage(" 节点列表中有：%d个\n",(int) lists.size());
				for (auto it = lists.begin(); it != lists.end(); it++)
				{
					LogManager::GetInstance().WriteMessage(" 节点ID：%d\n",(int)(*it)->GetNodeID());
					LogManager::GetInstance().WriteMessage(" IP地址：%s\n", (*it)->GetNodeIpString());
				}
	
				if (m_fun)
				{
					m_fun(0);
				}
				break;
			}

			case NetCom::NodeDirectory:
			{

				if (nodeID == ResourceManager::GetInstance().GetCurrentNode()->GetNodeID())
				{
					TopicPublisherWriteHandle handle;
					handle.HandleEnter(EPackType::TopicPublisher);
					LogManager::GetInstance().WriteMessage(std::string("收到自己发来的节点目录包，进入下一次接收"));
					break;
				}
				NodeDirectoryReadHandle handle;
				handle.HandleEnter(buffer);
				auto lists = ResourceManager::GetInstance().GetNodeList();
				if (m_fun)
				{
					m_fun(0);
				}
				LogManager::GetInstance().WriteMessage(" 节点列表中有：%d个\n", (int)lists.size());
				for (auto it = lists.begin(); it != lists.end(); it++)
				{
					LogManager::GetInstance().WriteMessage(" 节点ID：%d\n", (int)(*it)->GetNodeID());
					LogManager::GetInstance().WriteMessage(" IP地址：%s\n", (*it)->GetNodeIpString());
				}

				break;
			}
			case NetCom::NodeExit:
			{
				if (nodeID == ResourceManager::GetInstance().GetCurrentNode()->GetNodeID())
				{
					LogManager::GetInstance().WriteMessage("收到自己发来的节点退出包，退出");
					break;
				}
				NodeExitReadHandle handle;
				handle.HandleEnter(buffer);
				break;
			}
			case NetCom::TopicPublisher:

			{
				if (nodeID == ResourceManager::GetInstance().GetCurrentNode()->GetNodeID())
				{
					LogManager::GetInstance().WriteMessage("收到自己发来的主题发布包，退出");
					break;
				}
				break;
			}
			case NetCom::TopicDiscribe:
			{
				if (nodeID == ResourceManager::GetInstance().GetCurrentNode()->GetNodeID())
				{
					LogManager::GetInstance().WriteMessage("收到自己发来的主题订阅包，退出");
					break;
				}
				TopicPublisherReadHandle handle;
				handle.HandleEnter(buffer);



				break;
			}
			case NetCom::MessageTranse:
			/*{
				MessageTransePack pack;
				pack.PaserPack(buffer, 1024, ToolClass::GetPacketType(buffer));
			}*/
				break;
			case FileTranse: // 文件传输
			{
				/*	FileTranseHandle handle;
					handle.HandleEnter(buffer);*/
				break;
			}
			case NetCom::DiscribeSuccess:
				break;
			case NetCom::LookupPublisherSuccess:
				break;
			case NetCom::LookupPublisherFail:
				break;
			case NetCom::ACK:
				break;
			case NetCom::PING:
				break;
			case NetCom::RESTATE:
				break;
			case NetCom::HEARTBEAT:
			{
				HeartBeatReadHandle handle;
				handle.HandleEnter(buffer);
				break;
			}
			default:
				break;
			}
		}
	}
	void NodeDiscover::Init()
	{
		//初始化节点，初始化网络
		m_sendSocket = new DatagramSocket;
		m_sendAddrss = SocketAddress(m_currentNode->GetNodeIpString(), m_sendPort);
		m_sendSocket->bind(m_sendAddrss, true);
		m_sendSocket->setBroadcast(true);
		m_createTime = Timestamp();

		//std::cout << "当前节点ID：" << m_currentNode->GetNodeID() << std::endl;

		//资源管理初始化

		//ResourceManager::GetInstance().AddNode(m_currentNode);

		Publisher* publisher = new Publisher;
		publisher->SetNodeID(ResourceManager::GetInstance().GetCurrentNode()->GetNodeID());
		Subscribe* subs = new Subscribe;
		subs->SetNodeID(ResourceManager::GetInstance().GetCurrentNode()->GetNodeID());
		m_receiveAddrss = SocketAddress(IPAddress(), m_receivePort);
		m_receiveSocket = new DatagramSocket(m_receiveAddrss);
		PackManager::Init();
		PackManager manager;
		/*manager.Fill(11);
		manager.Parse(manager.GetData(), 256);*/

		//启动心跳机制
// 		m_beatCommit = new HeartBeatCommit;
// 		int beatHeartTime = Framework::GetInstance().ConfigInt("BeatHeartTime");
// 		m_beatCommit->Start(0, beatHeartTime);
		CoreComponent::GetInstance().Run(ESubscriber);
		std::string strType = Framework::GetInstance().ConfigString("ParticipatorType");
		int topicID = Framework::GetInstance().ConfigInt("TopicID");
		if (strType == "Pub")
		{
			publisher->AddTopic(topicID);
		}
		else if (strType == "Sub")
		{
			subs->AddTopic(topicID);
		}
		ResourceManager::GetInstance().AddParticipator(publisher);
		ResourceManager::GetInstance().AddParticipator(subs);

		////发布节点加入信息
		NodeJoinWriteHandle handlew;
		handlew.HandleEnter(&m_sendSocket);
		////定时器测试
		UInt32 time = Framework::GetInstance().ConfigInt("NodeDiscoverTimer");
		m_waitHand = new WaitDicHand(time);
		m_waitHand->HandleEnter(0);
	}
}


