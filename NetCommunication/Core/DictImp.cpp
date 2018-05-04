#include "DictImp.h"

#include "TopicRecord.h"

namespace NetCom
{
	DictImp::DictImp()
	{
	}


	DictImp::~DictImp()
	{
	}

	void DictImp::Insert(char * topic, const char *attrName, const char * attrType, int size)
	{
		TopicRecord * tr = new TopicRecord(topic, attrName, attrType, size);
		std::string t(topic);
		m_data.insert(std::pair<std::string, TopicRecord*>(t, tr));
	}

}
