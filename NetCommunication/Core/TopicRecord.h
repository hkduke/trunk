#pragma once
#include "CoreCommon.h"

namespace NetCom
{
	// ���ֵ��װ���� �� ͨ���̳�ʵ���Լ����ڴ沼��
	class TopicRecord
	{
	public:
		TopicRecord(const char * topic, const char *attrName, const char * attrType, int size);
		TopicRecord();
		~TopicRecord(void);



		virtual  void SetAttr(const char * topic, const char *attrName, const char * attrType, int size);

	public:
		char * ptr;	//// ������ʼi��ַ
		BYTE* data;	// ʵ������
		char * mTopicName;		// ��������
		char * m_AttrName;	// ��������
		BYTE   m_AttrSize;	// �ֽ���
		char * m_AttrType;	// ��������


	};
}


