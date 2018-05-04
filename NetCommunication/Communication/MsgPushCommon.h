#pragma  once
#include "DataSampleElementList.h"
#include "Thread.h"

// 
#include "../Core/HashMap.h"

#include "../Communication/FileSendQueue.h"
#include "../Communication/MsgSendQueue.h"

namespace NetCom
{
	class DataLinkMap;
	class Transport;


	class NETCOMMUNICATION_EXPORT MsgPushCommon
	{
	public:
		typedef HashMap<UInt32, DataSampleElement*> ResourceIndexMap;
		MsgPushCommon(DataSampleElementList * ptr = nullptr);
		~MsgPushCommon();

		void Init();
		void ProcessQueue();
		void SetDataLinkMap(DataLinkMap * ptr);
		void SetTransport(Transport * ptr);
		DataLinkMap * GetDataLinkMap();
		DataSampleElementList * GetDataSampleElementList();
		void Push(UInt32 topic ,UInt8 * data , UInt32 len , TransactionType type= TransactionType_Data);
		void Run();
		void SetDataCount(UInt32 count);

	private:
		DataLinkMap * m_pDataLinkMap;
		DataSampleElementList * m_dataList;
		Thread * _thread;
		Thread *_thread_file;
		UInt32 m_dataCount;
		FastMutex m_lock;

		
		ResourceIndexMap m_ResourceTable;
		UInt64 m_Resourceindex;

		MsgSendQueue * m_pMsgSendQueue;
		FileSendQueue * m_pFileSendQueue;
		bool m_ack;
	};
}
