#pragma once

#include "DataSampleElement.h"
#include <queue>
#include "../Core/Mutex.h"
#include <list>
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT DataSampleElementList
	{
	public:
		typedef std::list<DataSampleElement*> DataSampleList;
	public:
		DataSampleElementList();
		~DataSampleElementList();

		void Pop();

		DataSampleElement* Front();

		void Push(DataSampleElement* ele);
		
		inline size_t Size() { return m_dataList.size(); }

		inline bool Empty()
		{
			return m_dataList.empty();
		}


		inline DataSampleList & GetDataSampleQueque()
		{
			return m_dataList;
		}

		// 使用标准队列与内存分配（待定）
		DataSampleList m_dataList;
		FastMutex m_lock;
		UInt32 m_Id;
	};

}

