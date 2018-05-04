#pragma once
#include "../Core/EventHandle.h"
#include "../Core/TimerHandle.h"

//����̳���TimerHandle�¼�������ʱ���ڴ������
namespace NetCom
{
	class NodeJoinWriteHandle;
	class NodeDirectoryReadHandle;
	class Timer;
	class NETCOMMUNICATION_EXPORT WaitDicHand:public TimerHandle
	{
	public:
		WaitDicHand(double m_timeCount);

		~WaitDicHand();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

		void CheckTimeOutState(Timer& timer);

	public:

		double m_timeCount;//��ʱʱ��

		Timer* m_timer;//��ʱʱ��
	};


}


