#pragma once
#include "../Core/CoreCommon.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT ITransportStrategy
	{
	public:
		virtual ~ITransportStrategy();

		virtual int Start() = 0;
		virtual void Stop() = 0;
	};
}
