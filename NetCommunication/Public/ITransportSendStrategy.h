#pragma once
#include "../Core/CoreCommon.h"
#include "../Core/Types.h"



namespace NetCom
{
	class DataLinkMap;


	class NETCOMMUNICATION_EXPORT ITransportSendStrategy 
	{
	public:
		//virtual void InitStrategy() = 0 ;
		// ‚÷Ý”°lËÍ½Ó¿Ú
		virtual int Send(UInt32 topic ,UInt8 * data, UInt32 size , TransactionType type = TransactionType_Data) = 0;
		//virtual int StartSend() = 0;
		virtual DataLinkMap* GetDataLinkMap() = 0;
		virtual std::string name() const = 0;

	};

}
