#pragma once
#include "../Communication/TransportSendStrategy.h"
#include "../Core/Export.h"
#include "TCPTransport.h"
#include "../Core/Types.h"
#include "../Core/ClassLibrary.h"
namespace NetCom
{
	class DataLinkMap;
	class  NETCOMMUNICATION_EXPORT TCPTransportSendStrategy :public ITransportSendStrategy
	{
	public:
		TCPTransportSendStrategy();
		~TCPTransportSendStrategy();

		virtual int Send(UInt32 topic ,UInt8 * data, UInt32 size, TransactionType type = TransactionType_Data);
		virtual void InitStrategy();
		virtual std::string name()const;
		virtual DataLinkMap* GetDataLinkMap();
		void pocoUninitializeLibrary();
		void pocoInitializeLibrary();
	private:
		// 数据链路集合
		DataLinkMap * m_pDataLinkMap;
	};

 }

