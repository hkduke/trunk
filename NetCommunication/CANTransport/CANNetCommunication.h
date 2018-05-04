#pragma once

#include "../Communication/NetCommunication.h"
#include "CANPlugin.h"
namespace NetCom
{
	class CANNetCommunication :
		public NetCommunication
	{
	public:
		CANNetCommunication(void);
		~CANNetCommunication(void);

		virtual void InitNetCom();

		
		CANPlugin m_canPlugin;
	};
	
}

