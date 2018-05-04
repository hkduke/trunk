#pragma once
#include "nodebase.h"
#include <iostream>
#include <vector>
#include "../Communication/Participator.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT Subscribe :
		public Participator
	{
	public:
		Subscribe(void);
		
		Subscribe(UINT subscribID);

		~Subscribe(void);

		virtual void ClearTopic();
		virtual std::vector<UInt32>& GetTopicList();
		virtual void DeleteTopic(UInt32 id);

		void AddTopic(UInt32 id);
		bool IsTopicExist(UInt32 id);

	public:
		UINT m_subscribeId;
		std::vector<UInt32> m_pubTipicSet;
	};
}


