#pragma once
#include "CoreCommon.h"
#include "EventHandle.h"

namespace NetCom
{
	class NETCOMMUNICATION_EXPORT  PackRoute
	{
	public:
		PackRoute();
		~PackRoute();

		void GenerateHandle( UInt8 * data , UInt32 len);

	};

}

