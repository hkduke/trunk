#include "Subscribe.h"
#include "../Core/CommonTool.h"
#include "../Core/LogManager.h"
namespace NetCom
{
	Subscribe::Subscribe(void):Participator(ToolClass::GenerateUint32UUID())
	{
		m_listenerType = DataReader;
	}

	Subscribe::Subscribe(UINT subscribID):m_subscribeId(subscribID)
	{
		this->SetParticipatorID(subscribID);
		m_listenerType = DataReader;
	}


	Subscribe::~Subscribe(void)
	{
		
	}

	void Subscribe::ClearTopic()
	{
		m_pubTipicSet.clear();
	}

	std::vector<UInt32>& Subscribe::GetTopicList()
	{
		// TODO: 在此处插入 return 语句
		return m_pubTipicSet;
	}

	void Subscribe::DeleteTopic(UInt32 id)
	{
		auto it = std::find(m_pubTipicSet.begin(), m_pubTipicSet.end(), id);
		if (it != m_pubTipicSet.end())
		{
			m_pubTipicSet.erase(it);
		}
	}


	void Subscribe::AddTopic(UInt32 id)
	{
		if (!IsTopicExist(id))
		{
			m_pubTipicSet.push_back(id);
		}
	}
	bool Subscribe::IsTopicExist(UInt32 id)
	{
		if (std::find(m_pubTipicSet.begin(), m_pubTipicSet.end(), id) != m_pubTipicSet.end())
		{
			return true;
		}
		return false;
	}
}

