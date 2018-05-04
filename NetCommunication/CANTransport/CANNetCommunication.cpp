#include "CANNetCommunication.h"
#include "CANTransportSendStrategy.h"

namespace NetCom
{
	CANNetCommunication::CANNetCommunication(void)
	{
		InitNetCom();
	}


	CANNetCommunication::~CANNetCommunication(void)
	{
	}

	void CANNetCommunication::InitNetCom()
	{
		m_canPlugin.m_can.initDevice();

		m_send = new CANTransportSendStrategy;
	}

}


