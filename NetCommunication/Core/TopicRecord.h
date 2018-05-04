#pragma once
#include "CoreCommon.h"

namespace NetCom
{
	// 对字典封装数据 ， 通过继承实现自己的内存布局
	class TopicRecord
	{
	public:
		TopicRecord(const char * topic, const char *attrName, const char * attrType, int size);
		TopicRecord();
		~TopicRecord(void);



		virtual  void SetAttr(const char * topic, const char *attrName, const char * attrType, int size);

	public:
		char * ptr;	//// 数据起始i地址
		BYTE* data;	// 实际数据
		char * mTopicName;		// 主题名称
		char * m_AttrName;	// 属性名称
		BYTE   m_AttrSize;	// 字节数
		char * m_AttrType;	// 属性类型


	};
}


