#pragma once
//#include <thread>
// �¼�����ӿ�
#include "CoreCommon.h"
#include "../Core/Types.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT EventHandle
	{
	public:
		EventHandle(EventTypeHandle type);
		EventHandle();
		~EventHandle();
		// �¼����� ������ʵ��(ִ�г�ʼ������ , ����ִ��һ��)
		virtual int  HandleEnter(void *ptr);

		// �¼����� ������ʵ��
		virtual int Handle(void *ptr);

		// �¼��ر� ������ʵ��
		virtual int HandleClose(void *ptr);
		void SetEventType(EventTypeHandle type);
		EventTypeHandle GetEventType();
		void Activate();
		void Death();
		bool isActivate();
		void SetExecuteCount(UInt64 count);
		UInt64 GetExecuteCount();
		void SetDataLen(UInt32 len);
		UInt32 GetDataLen();
		void SetDataPtr(void * data);
		UInt64 & ModifyExecuteCount();
		// �����¼����ȼ�
		void SetPriority(int priority);
		virtual int Priority(void) const;
		void * GetAppendData();
		bool Copy(void * data, UInt32 len);
		bool m_MessageActive;

		EventTypeHandle m_eventType;
		int m_nPriority;	// �¼����ȼ�
		void * m_data;
		UInt32 m_packLen;
		UInt64 m_executeCount;
	};
}

