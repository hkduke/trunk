#pragma once
#include "../Core/EventHandle.h"
//#include "../Core/PackManager.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT DataReadHandle :public EventHandle
	{
	public:
		DataReadHandle();
		~DataReadHandle();
		virtual int  HandleEnter(void *ptr);

		// �¼����� ������ʵ��
		virtual int Handle(void *ptr);

		// �¼��ر� ������ʵ��
		virtual int HandleClose(void *ptr);
		
	};
}


