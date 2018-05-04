#pragma once
#include "../Core/Export.h"
#include "../Core/Types.h"
#include "../Core/CoreCommon.h"
#include "../Communication/DataSampleElementList.h"
#include "../Core/Runnable.h"
#include "../Core/Mutex.h"

namespace NetCom
{
	class DataLinkMap;
	class Publisher;
	class Subscribe;
	class MsgPushCommon;
	class NETCOMMUNICATION_EXPORT Transport /*:public Runnable*/
	{
	public:
		Transport();
		~Transport();

		virtual void SetDataLinkMap(DataLinkMap * ptr);
		virtual bool Init();
		//virtual void run();
		virtual void Stop();
		virtual void Send(UInt32 tocpic ,const UInt8 * data, UInt32 len, TransactionType type = TransactionType_Data);
		virtual void Start();

		virtual bool JudgeType();
		virtual NetType GetNetType();

// 		virtual Publisher* GetPublisher();
// 		virtual Subscribe *GetSubscribe();

		virtual DataLinkMap* GetDataLinkMap();
		virtual DataSampleElementList* GetDataSampleElementList();
		bool GetReactorEstablish();
		void SetReactorEstablishFlag(bool es);
		virtual void SendAll(UInt8 * data  , UInt32 len);
	private:
		DataLinkMap * m_datamap;
		NetType m_ParticipatorType;
		// 自身信息
		//Publisher* m_Publisher;
		//Subscribe * m_Subscribe;
		DataSampleElementList * m_DataSampleElementList;
		MsgPushCommon * m_pSendQueue;
		bool m_Establishreactor;
		FastMutex fm;
	};

}

