#include "NetCommunication.h"
#include "TransportSendStrategy.h"

namespace NetCom
{

	void NetCommunication::InitNetCom()
	{
		m_send = new TransportSendStrategy();
	}

	NetCommunication::NetCommunication()
	{
	}

	ITransportSendStrategy * NetCommunication::GetTransortSend()
	{
		return m_send;
	}

	void NetCommunication::RegisterParticipantType(NetType type)
	{
		m_send = new TransportSendStrategy(type);
	}

}