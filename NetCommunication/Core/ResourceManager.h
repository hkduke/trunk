#pragma once

#include "CoreCommon.h"
#include <iostream>
#include <list>
#include "NodeBase.h"
#include "SingleTmp.h"
#include"NodeBase.h"
#include "../Core/Thread.h"
#include<vector>
#include "../Core/Timestamp.h"

namespace NetCom
{
	class NodeDiscover;
	class Participator;
	class Timer;
	class ResourceManager;
	class DataSampleElementList;
	class ReceiveQueue;
	class DataLinkMap;
	class MsgPushCommon;
	class FileTranseManager;
	class PackManager;
	class NETCOMMUNICATION_EXPORT ResourceManager
	{
	public:
		typedef std::vector<Participator*> ParticpatorSet;
		typedef std::list<NodeBase* > NodeList;
		typedef void(*Func)(int, bool);
	public:
		ResourceManager();
		~ResourceManager();

		bool  Start();

		bool Stop();

		bool ReStart();

		NodeStatus m_nodestatus;	// 节点状态

		bool AddNode(NodeBase* newNode);//增加节点

		void ClearNode();//清空节点

		void MutexLock();//上锁

		void MutexUnlock();//解锁

		void ChangeNodeState(int uuid, NodeStatus state);

		bool IsTimeOut();

		void SetTimeOut(bool timeOutState);

		bool IsInitCompelete();

		void SetInitCompelete(bool initState);

		UInt32 GetSmallestNodeID();

		void SetSmallestNodeID(UInt32 nodeID);

		void SetNodeState(UInt32 nodeID, NodeStatus state);

		NodeBase* GetCurrentNode();
		//获取指定ID的节点
		NodeBase* GetNodeFromID(UInt32 nodeID);

		void SetCurrentNode(NodeBase* node);
		FileTranseManager * GetFileTranseManager();
		std::list<NodeBase* >& GetNodeList();

		void SetNodeList(std::list<NodeBase* >& list);

		bool IsNodeExit(NodeBase* node);

		bool IsNodeExit(UInt32 nodeID);

		void AddParticipator(Participator* participator);

		bool IsLocalParticipatorExist(Participator* participator);
		void SetCurrentIp(std::string ip);

		static ResourceManager& GetInstance();

		bool IsLParticipatorTopicExit(UInt32 participatorID, UInt32 topicID);

		ReceiveQueue& GetReceiveQueue();

		MsgPushCommon* GetSendQueue();

		void RegisterFunction(Func func);
		PackManager * GetPackManager();
		Func GetFunction();
	private:
		void SendTransportInit();
		void ReceiveTransportInit();
		Func m_func;
	public:

		bool IsSmallestNode();//检测当前节点是否是最小结点
		//最小结点最后发布的生存时间，用来仲裁
		Timestamp::TimeDiff m_smallestAliveTime;
		//接到最小结点发布的时间
		Timestamp m_smallestLastSend;
		//本节点最后发送时间，用来判断初始化时，目录发送的时间,专门记录本节点。
		Timestamp::TimeDiff lastSendDirTime;
	public:
		bool m_isInitCompelete;//是否在初始化

		UInt32 m_smallestNodeID;//记录当前最小结点信息

		bool m_isTimeout; //检查是否更新目录超时

		Mutex m_nodeListMutex;//节点修改锁	

		NodeBase* m_currentNode;//当前运行实例节点的信息

		std::list<NodeBase* > m_nodeList;//节点目录列表

		ParticpatorSet m_localParticipator;


		//维护本节点相关的发布定阅主题

		ParticpatorSet m_localRelateSubscrib;

		bool IsLocalRelateSubscribExist(UInt32 participatorID);

		bool IsLocalRelateSubscribTopicExist(UInt32 participatorID, UInt32 topicID);

		void AddLocalRelationSubscrib(Participator* participator);

		bool IsLocalPublicTopicExit(UInt32 topicID);

		bool IsLocalsubScribTopicExit(UInt32 topicID);

		std::vector<Participator*>& GetRelateSubscrib();


		std::vector<Participator*> GetLocalPublisherList();


		std::vector<Participator*> GetLocalSubscribList();

		void DeleteSubscrib(UInt32 nodeID);

		void DeleteNodeTopic(UInt32 nodeID);

		DataLinkMap *m_datamap;
		MsgPushCommon * m_pSendQueue;
		ReceiveQueue * m_pReceiveQueue;
		FileTranseManager * m_fileManager;
		PackManager * m_PackManager;
		//测试用函数
	public:
		//打印定阅表
		void PrintList();

	};
}


