#include "DictFrameImp.h"

#include <assert.h>

namespace NetCom
{
	DictFrameImp::DictFrameImp()
	{
		BuffSize = 128;
		m_buffer = (BYTE*)MALLOC(BuffSize);
	}


	DictFrameImp::~DictFrameImp()
	{
		if (m_buffer) {
			FREE(m_buffer);
		}
	}

	BYTE * DictFrameImp::ToBuffer(char * attr, BYTE *data, int &size)
	{
		char databuf[32] = { 0 };
		int natt = strlen(attr);
		int ndata = strlen((char*)data);

		int byteCount = natt + ndata + sizeof(int) * 2/*+sizeof(char*)*3+8*/;
		size = byteCount;
		memset(m_buffer, 0, BuffSize);

		m_nameLen = (char*)m_buffer;
		_itoa(natt, databuf, 10);
		memcpy(m_buffer, databuf, 4);	// 属性长度
		memset(databuf, 0, 32);
		_itoa(ndata, databuf, 10);
		memcpy(m_buffer + 4, databuf, 4);	// 数据长度

		memcpy(m_buffer + 4 + 4, attr, natt);

		memcpy(m_buffer + 4 + 4 + natt, data, ndata);
		return m_buffer;
	}

	bool DictFrameImp::ParseData(const BYTE * buf, int bufSize, int & attrLen, int & dataLen, char * attr, char * data)
	{
		assert(buf);
		char lenBuf[4];
		memset(lenBuf, 0, 4);
		memcpy(lenBuf, buf, 4);

		attrLen = atoi(lenBuf);
		memset(lenBuf, 0, 4);
		memcpy(lenBuf, buf + 4, 4);
		dataLen = atoi(lenBuf);

		memcpy(attr, buf + 8, attrLen);

		memcpy(data, buf + 8 + attrLen, dataLen);
		return true;
	}

	BYTE * DictFrameImp::GetBuffer()
	{
		return m_buffer;
	}

}
