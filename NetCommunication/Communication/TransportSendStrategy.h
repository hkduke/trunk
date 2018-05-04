#pragma once
#include "../Core/CoreCommon.h"
#include "../Public/ITransportSendStrategy.h"
#include "Transport.h"
#include "DataLinkMap.h"
#include "../Core/Runnable.h"



namespace NetCom
{
	class DataLinkMap;
	class Transport;
	class FileSendQueue;

	enum TransportDir
	{
		LEFT,	// sub -> Pub
		RIGHT,	// Pub -> Sub
		LEFTANDRIGHT // Pub<->Sub  double dir
	};
	class NETCOMMUNICATION_EXPORT TransportSendStrategy :public ITransportSendStrategy 
	{
	public:
		TransportSendStrategy();

		TransportSendStrategy(NetType type);
		~TransportSendStrategy();
		virtual void InitStrategy()  ;
		virtual void InitStrategy(NetType type)  ;
		virtual int Send(UInt32 topic , UInt8* data, UInt32 size, TransactionType type = TransactionType_Data) ;
		virtual int StartSend();

		virtual std::string name()const;
		virtual void Run();
		DataLinkMap * GetDataLinkMap();
		Transport ** GetTransport();
	private:
		// 数据链路集合
		DataLinkMap * m_pDataLinkMap;
		Transport * m_pTransport;
		NetType m_eNetType;
	};

}

