#pragma once

#include "CoreCommon.h"

namespace NetCom
{
	// �Զ���ÿһ�������������ݽӿ�
	class DictFrame
	{
	public:
		DictFrame();
		~DictFrame();

		virtual BYTE *ToBuffer(char * attr, BYTE *data, int &size);

		virtual bool ParseData(const BYTE * buf, int bufSize, int &attrLen, int &dataLen, char *attr, char * data);
		virtual BYTE *GetBuffer();

	};
}


