#pragma once
#include "../Core/CoreCommon.h"
#include "../Core/Types.h"
#include <iostream>
#include "../Core/NodeBase.h"
#include<vector>
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT Participator
	{
	public:
		Participator();
		Participator(UInt32 id);
		~Participator();

		void Enable();
		void Close();
		void SetListenerType(ParticipatorType type);

		//获取和设置参与者ID
		UInt32  GetParticipatorID();
		void SetParticipatorID(UInt32  id);
		//获取和设置节点
		void SetNodeID(UInt32 nodeID);
		UInt32 GetNodeID();
		ParticipatorType GetParticipatorType();


		//在继承类中增删改查主题
		virtual void AddTopic(UInt32 id)=0;
		virtual bool IsTopicExist(UInt32 id)=0;
		virtual void ClearTopic() = 0;
		virtual std::vector<UInt32>& GetTopicList()=0;
		virtual void DeleteTopic(UInt32 id) = 0;

		bool m_isEnable;
		ParticipatorType m_listenerType;
		
		protected:
		UInt32 m_ID;
		UInt32 m_nodeID;

	};
}


