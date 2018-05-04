#include "DictFrame.h"
#include <assert.h>

namespace NetCom
{
	DictFrame::DictFrame()
	{

	}


	DictFrame::~DictFrame()
	{
	}

	BYTE * DictFrame::ToBuffer(char * attr, BYTE *data, int &size)
	{
		return nullptr;
	}

	bool DictFrame::ParseData(const BYTE * buf, int bufSize, int &attrLen, int &dataLen, char *attr, char * data)
	{
		return -1;
	}

	BYTE * DictFrame::GetBuffer()
	{
		return nullptr;
	}
}


