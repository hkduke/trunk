#pragma once
#include "../Core/CoreCommon.h"
#include "../Core/SingleTmp.h"
#include <iostream>
#include "Framework.h"
#include "../Core/Publisher.h"
#include "../Core/Subscribe.h"
#include"../Sockets/IPAddress.h"
#include "../Sockets/Socket.h"
#include "../Sockets/DatagramSocket.h"
#include "../Core/Timestamp.h"
#include "../Communication/HeartBeatCommit.h"
#include"../Communication/HeartBeatCheck.h"
namespace NetCom
{
	class ResourceManager;
	class WaitDicHand;
	class Timer;
	class NodeBase;
	class NETCOMMUNICATION_EXPORT NodeDiscover:public Singleton<NodeDiscover>
	{
	public:
		NodeDiscover();
		~NodeDiscover(void);
		typedef void(*Func)(void*);
		void DiscoverNode(BYTE * data);	// 发送发现帧生成节点唯一标识
		void RegisterHandle(Func func);
		Func m_fun;
		void StartDiscover();
		void Init();
		void OnDiscoverNode();
		void  SetCurrentNode(NetCom::NodeBase* node);
		void SetSendPort(int port);
		void SetRecivePort(int port);
	public:
		SocketAddress m_sendAddrss;
		SocketAddress m_receiveAddrss;
		DatagramSocket* m_sendSocket;
		DatagramSocket* m_receiveSocket;
		int m_sendPort;
		int m_receivePort;
		std::string m_ip;
		WaitDicHand* m_waitHand;
		Timer *m_timer;
		NetCom::NodeBase* m_currentNode;
		ResourceManager *m_Manager;
		Timestamp m_createTime;
		HeartBeatCommit* m_beatCommit;
		HeartBeatCheck* m_heartBeatCheck;

		//测试节点
		//NodeBase nodeList[3];
	};
}

// 节点发现 包装各设备节点发现

