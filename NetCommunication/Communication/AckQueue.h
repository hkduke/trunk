#pragma  once
#include "DataSampleElementList.h"
#include "Thread.h"
#include <map>
#include "../Communication/DataLink.h"
namespace NetCom
{
	class DataLinkMap;
	class Transport;
	class PackRoute;

	typedef struct _AckObj
	{
		UInt32 srcNode;
		UInt32 ackFlag;
		UInt32 frameSerial;
		_AckObj(UInt32 _srcNode, UInt32 _ackFlag, UInt32 _frameSerial) :srcNode(_srcNode), ackFlag(_ackFlag), frameSerial(_frameSerial) 
		{
		}

		inline bool operator==(const _AckObj &rhs)const
		{
			return rhs.srcNode == srcNode;
		}

	}AckObj;

	typedef void(*AckSendFun)(AckObj*);
	typedef std::map<DataLink* ,AckSendFun> AckDataLinkSendFunMap;

	class NETCOMMUNICATION_EXPORT AckQueueManager
	{
	public:
		typedef std::queue<AckObj> AckList;
		AckQueueManager(DataSampleElementList * ptr =nullptr);
		~AckQueueManager();
		void ProcessQueue();
		void SetDataLinkMap(DataLinkMap * ptr);
		void SetTransport(Transport * ptr);
		DataLinkMap * GetDataLinkMap();
		void Push(void * buffer,UInt32 len);
		void Run();
		void SetDebug(bool is);

		void RegsiterDataLinkFun(DataLink* dl , AckSendFun fun);

		AckDataLinkSendFunMap & GetAckDataLinkSendFunMap()
		{
			return m_ackMapFun;
		}
	private:
		DataLinkMap * m_pDataLinkMap;
		DataSampleElementList * m_dataList;
		Transport * m_pTransport;
		PackRoute * m_pPackRoute;
		Thread * _thread;
		FastMutex m_Mutex;
		FastMutex m_pushMutex;
		AckList m_ackList;
		AckDataLinkSendFunMap  m_ackMapFun;



		bool is_Debug;
	};
}
