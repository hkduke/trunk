#pragma once
#include "../Public/INetCommunication.h"
#include "../Core/SingleTmp.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT NetCommunication : public Singleton<NetCommunication> ,public INetCommunication
	{

	public:
		NetCommunication();
		~NetCommunication(){}

		virtual void InitNetCom();

		virtual ITransportSendStrategy * GetTransortSend();

		void RegisterParticipantType(NetType type);

	public:
		ITransportSendStrategy * m_send;
	};
}