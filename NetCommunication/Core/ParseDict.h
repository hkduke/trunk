#pragma once
#include "DictDirectory.h"
#include <string>

namespace NetCom
{
	class ParseDict
	{
	public:
		ParseDict();
		~ParseDict();

		ParseDict(DictDirectory * ptr);
		void SetDict(DictDirectory *ptr);
		virtual bool ParseFile(const std::string &file);

		DictDirectory * m_pDict;
	};

}

