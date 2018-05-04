#pragma once

#include <vector>
#include <iostream>
#include "CoreCommon.h"

#include "EventManager.h"
#include "../Communication/TransportSendStrategy.h"
#include"../NodeDiscover/NodeDiscover.h"
#include "../Core/Types.h"
#include "../Communication/AckQueue.h"

#include "../Core/ResourceManager.h"
// 通信全局资源
#include "../PackageTypeManager/PackManager.h"

namespace NetCom
{
	class NodeDiscover;
	class Participator;
	class Publisher;
	class Subscribe;
	class Timer;
	class ResourceManager;
	class UserInterface;
	class PluginManager;
	class BlendModeNet;
	class AckQueueManager;
	class PackManager;
	class NETCOMMUNICATION_EXPORT Framework
	{
		
	public:
		Framework();
		~Framework();
		// 初始化全局
		int Init();

		// 心跳
		void Heartbeat();// 待定
		static Framework& GetInstance();
		std::string ConfigString(std::string item);
		UInt32 ConfigInt(std::string item);
		bool ConfigBool(std::string item);
	public:
		ITransportSendStrategy * GetTransportStratagy();

		EventManager*  GetEventManager();

		ResourceManager* GetResourceManager();
		NodeDiscover * GetNodeDiscover();
		UserInterface * GetUserInterface();
		bool LoadCommunicationPlugin();
		BlendModeNet * GetBlendModeNet();
		DataLinkMap * GetDataLinkMap();
		AckQueueManager *GetAckQueueManager();
		bool GetIsAck();
		void RegisterRecvFunction(PackManager::RecvFunc fun , UInt32 topicId);
	public:
		NodeDiscover * m_nodediscover;
		Thread  m_nodeDiscoverThread;
		UInt32 m_NRevicerSize;
		RunnableAdapter<NodeDiscover> * m_runnable;
		Timer *m_timer;

	private:
		ITransportSendStrategy* m_strategy;
		EventManager* m_eventManager;
		UserInterface * m_pUserInterface;
		PluginManager * m_pPluginManager;
		BlendModeNet * m_pBlendModeNet;
		AckQueueManager * m_pAckQueueManager;
		bool m_isBlendMode;	// 
		bool m_isAck;
	};
	
}

