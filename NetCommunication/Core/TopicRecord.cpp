#include "TopicRecord.h"
#include "CoreCommon.h"

namespace NetCom
{
	TopicRecord::TopicRecord(const char * topic, const char *attrName, const char * attrType, int size)
	{
		// 一次性分配
		int len = 12 * 3;
		ptr = new char[len];
		data = new BYTE[8];

		memset(data, 0, 8);
		memset(ptr, 0, len);

		mTopicName = ptr;
		m_AttrName = ptr + 12;
		m_AttrType = ptr + 24;

		memset(data, 0, 8);
		SetAttr(topic, attrName, attrType, size);
	}


	TopicRecord::TopicRecord()
	{
		// 一次性分配
		int len = 12 * 3;
		ptr = new char[len];
		data = new BYTE[8];
		memset(data, 0, 8);
		memset(ptr, 0, len);
		mTopicName = ptr;
		m_AttrName = ptr + 12;
		m_AttrType = ptr + 24;
	}

	void TopicRecord::SetAttr(const char * topic, const char * attrName, const char * attrType, int size)
	{
		strcpy(mTopicName, topic);
		strcpy(m_AttrName, attrName);
		strcpy(m_AttrType, attrType);
		m_AttrSize = size;
	}

	TopicRecord::~TopicRecord()
	{
	}
}

