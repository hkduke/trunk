#include "TopicRecordImp.h"

namespace NetCom
{
	TopicRecordImp::TopicRecordImp()
	{

	}


	TopicRecordImp::TopicRecordImp(const char * topic, const char *attrName, const char * attrType, int size)
	{
		// 一次性分配
		int len = 12 * 3;
		ptr = (char*)MALLOC(len * sizeof(char));
		data = (BYTE*)MALLOC(8 * sizeof(BYTE));

		memset(data, 0, 8);
		memset(ptr, 0, len);

		mTopicName = ptr;
		m_AttrName = ptr + 12;
		m_AttrType = ptr + 24;

		memset(data, 0, 8);
		SetAttr(topic, attrName, attrType, size);
	}

	TopicRecordImp::~TopicRecordImp()
	{
		if (ptr)
			FREE(ptr);
		if (data)
			FREE(data);
	}

}

