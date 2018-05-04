#include "Participator.h"
#include "../Core/ResourceManager.h"

namespace NetCom
{
	Participator::Participator()
	{
		
	}


	Participator::Participator(UInt32 id)
	{
		SetParticipatorID(id);
	}

	Participator::~Participator()
	{
	}

	void Participator::Enable()
	{
		m_isEnable = true;
	}

	void Participator::Close()
	{
		m_isEnable = false;
	}

	void Participator::SetListenerType(ParticipatorType type)
	{
		m_listenerType = type;
	}

	UInt32 Participator::GetParticipatorID()
	{
		return m_ID;
	}

	void Participator::SetParticipatorID(UInt32 id)
	{
		m_ID = id;
	}

	void Participator::SetNodeID(UInt32  id)
	{
		m_nodeID = id;
	}

	UInt32  Participator::GetNodeID()
	{
		return m_nodeID;
	}

	ParticipatorType Participator::GetParticipatorType()
	{
		return m_listenerType;
	}

}
