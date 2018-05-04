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

		int Copy(void* data , UINT blockSize);	// ���С��1 ���ʾ
		UINT m_blocksize;	// �ܿ��С

		// ���ý������ �� ���Ϊ�����ʾ����û�б��
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
		UInt32 m_resourceId;	// �����Դ
		UInt32 m_ResouceCount;

	};
}


