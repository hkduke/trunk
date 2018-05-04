#pragma  once
#include "DataSampleElementList.h"
#include "Thread.h"

// 
#include "../Core/HashMap.h"
#include "../Communication/BlendModeNet.h"
namespace NetCom
{
	class DataLinkMap;
	class Transport;


	class NETCOMMUNICATION_EXPORT FileSendQueue
	{
	public:
		typedef HashMap<UInt32, DataSampleElement*> ResourceIndexMap;
		FileSendQueue(DataSampleElementList * ptr = nullptr);
		~FileSendQueue();

		void Init();
		void ProcessQueue();
		void SetDataLinkMap(DataLinkMap * ptr);
		void SetTransport(Transport * ptr);
		DataLinkMap * GetDataLinkMap();
		DataSampleElementList * GetDataSampleElementList();
		void Push(UInt8 * data , UInt32 len , TransactionType type= TransactionType_Data);
		void Run();
		void SetDataCount(UInt32 count);

	private:
		DataLinkMap * m_pDataLinkMap;
		DataSampleElementList * m_dataList;
		Thread * _thread;
		UInt32 m_dataCount;
		FastMutex m_lock;

		
		ResourceIndexMap m_ResourceTable;
		UInt32 m_Resourceindex;
		bool m_ack;
		BlendModeNet *  m_FileBlend;
	};
}
