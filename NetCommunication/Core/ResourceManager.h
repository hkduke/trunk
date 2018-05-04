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

		NodeStatus m_nodestatus;	// �ڵ�״̬

		bool AddNode(NodeBase* newNode);//���ӽڵ�

		void ClearNode();//��սڵ�

		void MutexLock();//����

		void MutexUnlock();//����

		void ChangeNodeState(int uuid, NodeStatus state);

		bool IsTimeOut();

		void SetTimeOut(bool timeOutState);

		bool IsInitCompelete();

		void SetInitCompelete(bool initState);

		UInt32 GetSmallestNodeID();

		void SetSmallestNodeID(UInt32 nodeID);

		void SetNodeState(UInt32 nodeID, NodeStatus state);

		NodeBase* GetCurrentNode();
		//��ȡָ��ID�Ľڵ�
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

		bool IsSmallestNode();//��⵱ǰ�ڵ��Ƿ�����С���
		//��С�����󷢲�������ʱ�䣬�����ٲ�
		Timestamp::TimeDiff m_smallestAliveTime;
		//�ӵ���С��㷢����ʱ��
		Timestamp m_smallestLastSend;
		//���ڵ������ʱ�䣬�����жϳ�ʼ��ʱ��Ŀ¼���͵�ʱ��,ר�ż�¼���ڵ㡣
		Timestamp::TimeDiff lastSendDirTime;
	public:
		bool m_isInitCompelete;//�Ƿ��ڳ�ʼ��

		UInt32 m_smallestNodeID;//��¼��ǰ��С�����Ϣ

		bool m_isTimeout; //����Ƿ����Ŀ¼��ʱ

		Mutex m_nodeListMutex;//�ڵ��޸���	

		NodeBase* m_currentNode;//��ǰ����ʵ���ڵ����Ϣ

		std::list<NodeBase* > m_nodeList;//�ڵ�Ŀ¼�б�

		ParticpatorSet m_localParticipator;


		//ά�����ڵ���صķ�����������

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
		//�����ú���
	public:
		//��ӡ���ı�
		void PrintList();

	};
}


