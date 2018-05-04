#include "ResourceManager.h"
#include "../Core/Publisher.h"
#include "../Core/Subscribe.h"
#include "../Core/SingletonHolder.h"
#include "../Communication/DataSampleElementList.h"
#include "../Communication/DataLinkMap.h"
#include "../Communication/FileSendQueue.h"
#include "RunnableAdapter.h"
#include "../Communication/ReceiveQueue.h"
#include "../Core/Framework.h"
#include "../Core/LogManager.h"
#include "../Communication/FileTranseManager.h"
#include "../PackageTypeManager/PackManager.h"
namespace NetCom
{
	//构造时传入本结点的信息，方便查询
	ResourceManager::ResourceManager()
	{
		m_isInitCompelete = false;
		m_isTimeout = false;
		m_smallestNodeID = -1;
		m_smallestAliveTime = 0;
		lastSendDirTime = 0;
		m_smallestLastSend = 0;
		m_func = 0;
	}

	ResourceManager::~ResourceManager()
	{
	}

	void ResourceManager::SendTransportInit()
	{

	}

	void ResourceManager::ReceiveTransportInit()
	{
		m_pReceiveQueue = new ReceiveQueue();
		bool b = Framework::GetInstance().ConfigBool("IsDebugRecive");
		m_pReceiveQueue->SetDebug(b);
		m_pReceiveQueue->Run();
	}

	bool ResourceManager::Start()
	{

		m_fileManager = new FileTranseManager;
		SendTransportInit();
		ReceiveTransportInit();
		m_PackManager = new PackManager;
		return true;
	}

	bool ResourceManager::Stop()
	{
		m_nodestatus = NetCom::Stop;
		return true;
	}

	bool ResourceManager::ReStart()
	{
		m_nodestatus = NetCom::Sleep;
		return true;
	}
	//增加结点
	bool  ResourceManager::AddNode(NodeBase * newNode)
	{
		bool bRet = false;
		MutexLock();
		if (!IsNodeExit(newNode))
		{
			m_nodeList.push_back(newNode);
			LogManager::GetInstance().WriteMessage("新节点加入完成,id号为%d\n", (int)newNode->GetNodeID());
			if (m_func)
			{
				m_func(newNode->GetNodeID(), true);
			}

			bRet = true;
		}

		MutexUnlock();
		return bRet;
	}

	void ResourceManager::ClearNode()
	{
		MutexLock();
		for (int i = 0; i < m_nodeList.size(); i++)
		{
			delete m_nodeList.front();
			m_nodeList.pop_front();
		}
		MutexUnlock();
	}
	//上锁，在外部使用
	void ResourceManager::MutexLock()
	{
		m_nodeListMutex.lock();
	}
	//解锁，在外部使用
	void ResourceManager::MutexUnlock()
	{
		m_nodeListMutex.unlock();
	}
	void ResourceManager::ChangeNodeState(int uuid, NodeStatus state)
	{
		MutexLock();
		for (auto it = m_nodeList.begin(); it != m_nodeList.end(); it++)
		{
			if ((*it)->GetNodeID() == uuid)
			{
				(*it)->SetState(state);
				break;
			}
		}

		MutexUnlock();
	}

	bool ResourceManager::IsTimeOut()
	{
		return m_isTimeout;
	}

	void ResourceManager::SetTimeOut(bool timeOutState)
	{
		m_isTimeout = timeOutState;
	}

	bool ResourceManager::IsInitCompelete()
	{
		return m_isInitCompelete;
	}

	void ResourceManager::SetInitCompelete(bool initState)
	{
		m_isInitCompelete = initState;
	}

	NetCom::UInt32 ResourceManager::GetSmallestNodeID()
	{
		return m_smallestNodeID;
	}

	void ResourceManager::SetSmallestNodeID(UInt32 nodeID)
	{
		m_smallestNodeID = nodeID;
		LogManager::GetInstance().WriteMessage("ResourceManager::SetSmallestNodeID 最小结点为：%d\n", (int)nodeID);
	}

	void ResourceManager::SetNodeState(UInt32 nodeID, NodeStatus state)
	{
		for (auto it = m_nodeList.begin(); it != m_nodeList.end(); it++)
		{
			if ((*it)->GetNodeID() == nodeID)
			{
				(*it)->SetState(state);
			}
		}
	}

	NetCom::NodeBase* ResourceManager::GetCurrentNode()
	{
		return m_currentNode;
	}

	NodeBase * ResourceManager::GetNodeFromID(UInt32 nodeID)
	{
		NodeBase* base = NULL;
		for (auto it = m_nodeList.begin(); it != m_nodeList.end(); ++it)
		{
			if ((*it)->GetNodeID() == nodeID)
			{
				base = *it;
				break;
			}
		}
		return base;

	}

	void ResourceManager::SetCurrentNode(NodeBase * node)
	{
		m_currentNode = node;
	}

	NetCom::FileTranseManager * ResourceManager::GetFileTranseManager()
	{
		return m_fileManager;
	}

	std::list<NodeBase*>& ResourceManager::GetNodeList()
	{
		return m_nodeList;
	}

	void ResourceManager::SetNodeList(std::list<NodeBase*>& list)
	{
		m_nodeList = list;
	}

	bool ResourceManager::IsNodeExit(NodeBase * node)
	{
		for (auto it = m_nodeList.begin(); it != m_nodeList.end(); it++)
		{
			if (node->GetNodeID() == (*it)->GetNodeID())
			{
				return true;
			}
		}
		return false;
	}

	bool ResourceManager::IsNodeExit(UInt32 nodeID)
	{
		for (auto it = m_nodeList.begin(); it != m_nodeList.end(); it++)
		{
			if (nodeID == (*it)->GetNodeID())
			{
				return true;
			}
		}
		return false;
	}
	//增加发布定阅
	void ResourceManager::AddParticipator(Participator * participator)
	{
		//如果是本地的包，不存在则加入，已经存在则不理会
		if (participator->GetNodeID() == ResourceManager::GetCurrentNode()->GetNodeID())
		{
			if (!IsLocalParticipatorExist(participator))
			{
				m_localParticipator.push_back(participator);
				if (m_func)
				{
				m_func(participator->GetNodeID(), true);
				}
				
			}
		}
	}
	bool ResourceManager::IsLocalParticipatorExist(Participator* participator)
	{
		for (auto it = m_localParticipator.begin(); it != m_localParticipator.end(); ++it)
		{
			if ((*it)->GetParticipatorID() == participator->GetParticipatorID())
			{
				return true;
			}
		}
		return false;
	}

	void ResourceManager::SetCurrentIp(std::string ip)
	{
		//地址
		NodeAddr addr;
		addr.SetType(IP_V4_ADDR);
		addr.SetAddress(ip);
		//当前结点信息
		m_currentNode = new NetCom::NodeBase();
		m_currentNode->SetNodeID(Framework::GetInstance().ConfigInt("NodeId"));
		m_currentNode->SetNodeAddr(addr);
	}


	//判断是否是最小结点
	bool ResourceManager::IsSmallestNode()
	{
		return m_currentNode->GetNodeID() == m_smallestNodeID;
	}

	
	namespace
	{
		static SingletonHolder<ResourceManager>  m_pResourceManager;
	}
	ResourceManager & ResourceManager::GetInstance()
	{
		return *m_pResourceManager.get();
	}

	//检查本地参与者主题是否有存在
	bool ResourceManager::IsLParticipatorTopicExit(UInt32 participatorID, UInt32 topicID)
	{
		for (auto it = m_localParticipator.begin(); it != m_localParticipator.end(); ++it)
		{
			if ((*it)->GetParticipatorID() == participatorID)
			{
				for (auto iit = (*it)->GetTopicList().begin(); iit != (*it)->GetTopicList().end(); ++iit)
				{
					if (*iit == topicID)
					{
						return true;
					}
				}
			}

		}
		return false;
	}

	NetCom::MsgPushCommon* ResourceManager::GetSendQueue()
	{
		return m_pSendQueue;
	}

	void ResourceManager::RegisterFunction(Func func)
	{
		m_func = func;
	}

	NetCom::PackManager * ResourceManager::GetPackManager()
	{
		return m_PackManager;
	}

	ResourceManager::Func ResourceManager::GetFunction()
	{
		return m_func;
	}

	bool ResourceManager::IsLocalRelateSubscribExist(UInt32 participatorID)
	{
		for (auto it = m_localRelateSubscrib.begin(); it != m_localRelateSubscrib.end(); ++it)
		{
			if ((*it)->GetParticipatorID() == participatorID)
			{
				return true;
			}
		}
		return false;
	}


	bool ResourceManager::IsLocalRelateSubscribTopicExist(UInt32 participatorID, UInt32 topicID)
	{
		for (auto it = m_localRelateSubscrib.begin(); it != m_localRelateSubscrib.end(); ++it)
		{
			if ((*it)->GetParticipatorID() == participatorID)
			{
				for (auto iit = (*it)->GetTopicList().begin(); iit != (*it)->GetTopicList().end(); ++iit)
				{
					if (*iit == topicID)
					{
						return true;
					}
				}

			}
		}
		return false;
	}
	//增加本地相关的定阅者，如果本地参与者是读类型，本地发布中有该主题且列表内没有则加入
	void ResourceManager::AddLocalRelationSubscrib(Participator * participator)
	{
		if (participator->GetParticipatorType() == DataReader)
		{
			std::vector<UInt32> vectorTopic = participator->GetTopicList();
			//对比要加入的定阅的主题是否有节点与本地发布的主题相同，相同则加入
			for (auto it = vectorTopic.begin(); it != vectorTopic.end(); ++it)
			{
				for (auto iit = m_localParticipator.begin(); iit != m_localParticipator.end(); ++iit)
				{
					//加入条件为本地有发布者发布了该主题，如果是写者该参与者中有该主题
					if ((*iit)->GetParticipatorType() == DataWriter
						&& (*iit)->IsTopicExist(*it))
					{
						m_localRelateSubscrib.push_back(participator);
						LogManager::GetInstance().WriteMessage(
							"新加的主题为：订阅者节点Id：%d,;订阅者的ID：%d:订阅者的主题为:%d\n",
							(int)participator->GetNodeID(), (int)participator->GetParticipatorID(), (int)*it);
					}
				}

			}
		}
	}

	bool ResourceManager::IsLocalPublicTopicExit(UInt32 topicID)
	{
		for (auto it = m_localParticipator.begin(); it != m_localParticipator.end(); ++it)
		{
			if ((*it)->IsTopicExist(topicID) && (*it)->GetParticipatorType() == DataWriter)
			{
				return true;
			}
		}
		return false;
	}
	bool ResourceManager::IsLocalsubScribTopicExit(UInt32 topicID)
	{
		for (auto it = m_localParticipator.begin(); it != m_localParticipator.end(); ++it)
		{
			if ((*it)->IsTopicExist(topicID) && (*it)->GetParticipatorType() == DataReader)
			{
				return true;
			}
		}
		return false;
	}

	std::vector<Participator*>& ResourceManager::GetRelateSubscrib()
	{
		return m_localRelateSubscrib;
	}

	std::vector<Participator*> ResourceManager::GetLocalPublisherList()
	{
		std::vector<Participator*> vector;
		for (auto it = m_localParticipator.begin(); it != m_localParticipator.end(); ++it)
		{
			if ((*it)->GetParticipatorType() == DataWriter)
			{
				vector.push_back(*it);
			}
		}
		return vector;
	}
	std::vector<Participator*> ResourceManager::GetLocalSubscribList()
	{
		std::vector<Participator*> vector;
		for (auto it = m_localParticipator.begin(); it != m_localParticipator.end(); ++it)
		{
			if ((*it)->GetParticipatorType() == DataReader)
			{
				vector.push_back(*it);
			}
		}
		return vector;
	}

	void ResourceManager::DeleteSubscrib(UInt32 nodeID)
	{
		for (auto it = m_localRelateSubscrib.begin(); it != m_localRelateSubscrib.end(); ++it)
		{
			if ((*it)->GetNodeID() == nodeID)
			{
				delete *it;
				m_localRelateSubscrib.erase(it);
				break;
			}
		}
	}

	ReceiveQueue & ResourceManager::GetReceiveQueue()
	{
		// TODO: insert return statement here
		return *m_pReceiveQueue;
	}

	/*const NetCom::ResourceManager::ParticpatorSet & ResourceManager::GetGlobalParticpator()
	{
		return m_gParicipator;
	}*/


}
