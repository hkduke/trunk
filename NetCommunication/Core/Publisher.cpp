#include "Publisher.h"
#include "CommonTool.h"
namespace NetCom
{
	Publisher::Publisher(void):Participator(ToolClass::GenerateUint32UUID())
	{
		m_listenerType = DataWriter;
		
	}


	Publisher::Publisher(UInt32 id)
	{
		SetParticipatorID(id);
		m_listenerType = DataWriter;
	}

	Publisher::~Publisher(void)
	{
	}

	void Publisher::ClearTopic()
	{
		m_pubTipicSet.clear();
	}

	std::vector<UInt32>& Publisher::GetTopicList()
	{
		return m_pubTipicSet;
	}

	void Publisher::DeleteTopic(UInt32 id)
	{
		auto it = std::find(m_pubTipicSet.begin(), m_pubTipicSet.end(), id);
		if (it != m_pubTipicSet.end())
		{
			m_pubTipicSet.erase(it);
		}
	}


	ConnecStatus Publisher::GetConnectStatus()
	{
		return m_Connect;
	}

	void Publisher::AddTopic(UInt32 id)
	{
		if (!IsTopicExist(id))
		{
			m_pubTipicSet.push_back(id);
		}
	}

	bool Publisher::IsTopicExist(UInt32 id)
	{
		/*for (auto it = m_pubTipicSet.begin(); it != m_pubTipicSet.end(); ++it)
		{
			if (*it == id)
			{
				return true;
			}
		}*/
		
		if (std::find(m_pubTipicSet.begin(), m_pubTipicSet.end(), id) != m_pubTipicSet.end())
		{
			return true;
		}
		return false;
	}

}
