#pragma  once
#include "DataSampleElementList.h"
#include "Thread.h"

// 
#include "../Core/HashMap.h"
#include "../Communication/MsgSendTocpicQueue.h"
namespace NetCom
{
	class DataLinkMap;
	class Transport;


	class NETCOMMUNICATION_EXPORT MsgSendQueue
	{
	public:
		typedef HashMap<UInt32, DataSampleElement*> ResourceIndexMap;
		typedef std::queue<DataSampleElement*> DataSampleElementQueue;
		typedef std::map<UInt32, MsgSendTocpicQueue*> MsgSendTocpicQueueMap;
		MsgSendQueue(DataSampleElementQueue * ptr = nullptr);
		~MsgSendQueue();

		void Init();
		void ProcessQueue();
		void SetDataLinkMap(DataLinkMap * ptr);
		void SetTransport(Transport * ptr);
		DataLinkMap * GetDataLinkMap();
		DataSampleElementQueue * GetDataSampleElementList();
		void Push(UInt32 topcic, UInt8 * data , UInt32 len , TransactionType type= TransactionType_Data);
		void Run();
		void SetDataCount(UInt32 count);

	private:
		DataLinkMap * m_pDataLinkMap;
		//DataSampleElementList * m_dataList;
		Thread * _thread;
		UInt32 m_dataCount;
		FastMutex m_lock;

		DataSampleElementQueue* m_dataList;
		//ResourceIndexMap m_ResourceTable;
		UInt32 m_Resourceindex;
		MsgSendTocpicQueueMap m_mapMsgQueue;
		bool m_ack;
	};
}
