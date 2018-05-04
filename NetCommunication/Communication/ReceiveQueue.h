#pragma  once
#include "DataSampleElementList.h"
#include "Thread.h"
namespace NetCom
{
	class DataLinkMap;
	class Transport;
	class PackRoute;

	class NETCOMMUNICATION_EXPORT ReceiveQueue
	{
	public:
		ReceiveQueue(DataSampleElementList * ptr =nullptr);
		~ReceiveQueue();
		void ProcessQueue();
		void SetDataLinkMap(DataLinkMap * ptr);
		void SetTransport(Transport * ptr);
		DataLinkMap * GetDataLinkMap();
		void Push(void * buffer,UInt32 len);
		void Run();
		void SetDebug(bool is);
	private:
		DataLinkMap * m_pDataLinkMap;
		DataSampleElementList * m_dataList;
		Transport * m_pTransport;
		PackRoute * m_pPackRoute;
		Thread * _thread;
		FastMutex m_Mutex;
		FastMutex m_pushMutex;
		bool is_Debug;
	};
}
