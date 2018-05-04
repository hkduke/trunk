#pragma  once
#include "DataSampleElementList.h"
#include "Thread.h"

// 
#include "../Core/HashMap.h"
namespace NetCom
{
	class DataLinkMap;
	class DataLink;


	class NETCOMMUNICATION_EXPORT MsgSendTocpicQueue
	{
	public:

		typedef HashMap<UInt32, DataSampleElement*> ResourceIndexMap;
		typedef std::queue<DataSampleElement*> DataSampleElementQueue;
		typedef std::vector<DataLink*> DataLinkList;

		MsgSendTocpicQueue(DataSampleElementQueue * ptr = nullptr);
		~MsgSendTocpicQueue();

		void Init();
		void ProcessQueue();
		void SetDataLinkMap(DataLinkMap * ptr);
		void SetTransport(Transport * ptr);
		DataLinkMap * GetDataLinkMap();
		DataSampleElementQueue * GetDataSampleElementList();
		void Push(UInt8 * data , UInt32 len , TransactionType type= TransactionType_Data);
		void Run();
		void SetDataCount(UInt32 count);

	private:
		DataLinkMap * m_pDataLinkMap;
		//DataSampleElementList * m_dataList;
		Thread * _thread;
		UInt32 m_dataCount;
		FastMutex m_lock;

		DataSampleElementQueue* m_dataList;
		ResourceIndexMap m_ResourceTable;
		UInt32 m_Resourceindex;
		bool m_ack;
		DataLinkList m_vecDataLink;
		UInt32 m_topicId;	// Ö÷Ìâ
		UInt32 m_currentResId;
	};
}
