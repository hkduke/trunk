#pragma once

#include "../Core/CoreCommon.h"
#include <string.h>
#include "../Core/Types.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT DataSampleElement
	{
	public:
		DataSampleElement();
		~DataSampleElement();

		int Copy(void* data , UINT blockSize);	// 如果小于1 则表示
		UINT m_blocksize;	// 总块大小

		// 设置结束标记 ， 如果为空则表示连续没有标记
		void SetEndMark(void * data = nullptr, UINT size = 0);

		void *GetBlockPtr();
		size_t GetBlockSize();

		inline void  SetResourceId(UInt32 id)
		{
			m_resourceId = id;
		}

		inline UInt32  GetResourceId()
		{
			return m_resourceId ;
		}

		inline UInt32 & GetResouceCount()
		{
			return m_ResouceCount;
		}
		void *m_data;
		void *m_endmark;
		size_t m_blockSize;
		UINT m_nmarksize;
		UInt32 m_resourceId;	// 标记资源
		UInt32 m_ResouceCount;

	};
}


