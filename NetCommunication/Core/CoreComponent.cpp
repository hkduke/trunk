#include "CoreComponent.h"
#include "../Communication/NetCommunication.h"
namespace NetCom
{
	CoreComponent * CoreComponent::m_instace = NULL;

	CoreComponent::CoreComponent()
	{
		
	}

	void CoreComponent::Run(NetType type)
	{

		InitComponent(type);
	}

	void CoreComponent::InitComponent(NetType type)
	{
		m_NetCom = new NetCom::NetCommunication;
		((NetCom::NetCommunication*)m_NetCom)->RegisterParticipantType(type);
	}


	NetCom::CoreComponent CoreComponent::GetInstance()
	{
		if(m_instace==NULL)
			m_instace =  new CoreComponent();
		return *m_instace;
	}

}

