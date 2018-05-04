#pragma once
#pragma once
#include "../Communication/TransportSendStrategy.h"
#include "../Core/Export.h"
#include "CANPlugin.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT CANTransportSendStrategy :
		public TransportSendStrategy
	{
	public:
		CANTransportSendStrategy(void);
		~CANTransportSendStrategy(void);
		void InitStrategy();

		virtual int Send(BYTE * data, UINT size);
	};
}


