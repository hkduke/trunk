#pragma once
#include "Export.h"
#include "../Public/INetCommunication.h"
#include "../Core/CoreCommon.h"
namespace NetCom
{
	class  NETCOMMUNICATION_EXPORT CoreComponent
	{
	public:
		static CoreComponent GetInstance();

		void Run(NetType type);

	private:
		void InitComponent(NetType type);

	private:
		NetCom::INetCommunication* m_NetCom;
		static CoreComponent * m_instace;
		CoreComponent();
	};



}
