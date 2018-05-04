#include "ParseDict.h"

namespace NetCom
{
	ParseDict::ParseDict()
	{
	}


	ParseDict::ParseDict(DictDirectory * ptr /*= NULL*/)
	{

	}

	void ParseDict::SetDict(DictDirectory * ptr)
	{
		m_pDict = ptr;
	}

	bool ParseDict::ParseFile(const std::string &file)
	{
		return true;
	}

	ParseDict::~ParseDict()
	{
	}

}

