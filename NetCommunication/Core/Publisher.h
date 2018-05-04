#pragma once
#include "nodebase.h"
#include<iostream>
#include <vector>
#include "../Communication/Participator.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT Publisher :
		public Participator
	{
	public:
		Publisher(void);

		Publisher(UInt32 id);

		~Publisher(void);

		virtual void ClearTopic() override;


		virtual std::vector<UInt32>& GetTopicList() override;


		virtual void DeleteTopic(UInt32 id) override;

	private:
		ConnecStatus m_Connect;
		std::vector<UInt32> m_pubTipicSet;

	public:

		virtual ConnecStatus GetConnectStatus();

		virtual void AddTopic(UInt32 id);

		virtual bool IsTopicExist(UInt32 id);

	};
}


