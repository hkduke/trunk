
#pragma once

#include "../Public/ITransportSendStrategy.h"
#include "../Core/SingleTmp.h"

namespace NetCom
{
	class NETCOMMUNICATION_EXPORT INetCommunication 
	{
	public:
		//************************************
		// Method:    INetCommunication
		// FullName:  NetCom::INetCommunication::INetCommunication
		// Access:    public 
		// Returns:   
		// Qualifier:
		//************************************
		INetCommunication(){}

		//************************************
		// Method:    ~INetCommunication
		// FullName:  NetCom::INetCommunication::~INetCommunication
		// Access:    public 
		// Returns:   
		// Qualifier:
		//************************************


		virtual ~INetCommunication(){}
		//************************************
		// Method:    GetTransortSend
		// FullName:  NetCom::INetCommunication::GetTransortSend
		// Access:    public 
		// Returns:   NetCom::ITransportSendStrategy *
		// Qualifier:
		//************************************
		virtual ITransportSendStrategy * GetTransortSend() = 0;

		//************************************
		// Method:    InitNetCom
		// FullName:  NetCom::INetCommunication::InitNetCom
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void InitNetCom() = 0;

	};
}