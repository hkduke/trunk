#pragma once
#include "Dict.h"
#include <map>
#include <string>
#include "TopicRecord.h"

namespace NetCom
{
	class DictImp :public Dict
	{
		typedef std::multimap<std::string, TopicRecord*> Dict_Data;	// ×Öµä¼üÓÐÖØ¸´
		typedef std::multimap <std::string, TopicRecord*>::iterator DictIter;
		typedef std::pair<DictIter, DictIter> Range;
	public:
		DictImp();
		~DictImp();
		virtual void Insert(char * topic, const  char *attrName, const char * attrType, int size);

	private:
		Dict_Data m_data;
	};

}

