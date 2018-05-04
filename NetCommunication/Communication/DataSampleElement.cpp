#include "DataSampleElement.h"
#include <string>
#include <assert.h>


namespace NetCom
{
	DataSampleElement::DataSampleElement():m_blockSize(0), m_ResouceCount(0)
	{
		m_data = nullptr;
		m_endmark = nullptr;
	}


	DataSampleElement::~DataSampleElement()
	{
		FREE(m_data);
		m_data = nullptr;
	}

	int DataSampleElement::Copy(void* data, UINT blockSize)
	{
		// 加上标记大小
		assert(data);
		UINT total = m_nmarksize =blockSize/*= blockSize + m_nmarksize*/;
		m_blockSize = total;
		if (m_data)
		{
			FREE(m_data);
		}

		m_data = MALLOC(total);
		assert(m_data);
		memcpy(m_data, data, blockSize);
		// 添加标签
		//memcpy((BYTE*)m_data + blockSize, m_endmark, m_nmarksize);
		return 1;
	}

	void DataSampleElement::SetEndMark(void * data /*= nullptr*/, UINT size /*= 0*/)
	{
		m_endmark = MALLOC(size);
		assert(m_endmark);

		memcpy(m_endmark, data, size);
	}

	void * DataSampleElement::GetBlockPtr()
	{
		return m_data;
	}

	size_t DataSampleElement::GetBlockSize()
	{
		return m_blockSize;
	}

}
