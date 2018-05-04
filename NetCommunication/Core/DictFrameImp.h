#pragma once
#include "DictFrame.h"

namespace NetCom
{
	class DictFrameImp :
		public DictFrame
	{
	public:
		DictFrameImp();
		~DictFrameImp();


		BYTE *ToBuffer(char * attr, BYTE *data, int &size);

		bool ParseData(const BYTE * buf, int bufSize, int &attrLen, int &dataLen, char *attr, char * data);
		BYTE *GetBuffer();

		char* m_nameLen;	// �涨4λ
		char* m_dataLen;

		BYTE *m_buffer;
		char * m_attrName;
		BYTE* m_data;
		int BuffSize;

	};
}


