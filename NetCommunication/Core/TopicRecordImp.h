#pragma once
#include "TopicRecord.h"

namespace NetCom
{
	class TopicRecordImp :
		public TopicRecord
	{
	public:
		TopicRecordImp();
		TopicRecordImp(const char * topic, const char *attrName, const char * attrType, int size);
		~TopicRecordImp();

	};
}


