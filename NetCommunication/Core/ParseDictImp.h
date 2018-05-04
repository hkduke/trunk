#pragma once
#include "ParseDict.h"

namespace NetCom
{
	class ParseDictImp :public ParseDict
	{
	public:
		ParseDictImp();
		~ParseDictImp();

		bool Init();
		virtual bool ParseFile(const std::string &file);
	};
}


