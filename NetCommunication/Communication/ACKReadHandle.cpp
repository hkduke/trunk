#include "ACKReadHandle.h"
#include "../Core/ACKPack.h"
namespace NetCom
{
	ACKReadHandle::ACKReadHandle()
	{
	}


	ACKReadHandle::~ACKReadHandle()
	{
	}

	int ACKReadHandle::HandleEnter(void *ptr)
	{
		//��ȡ��Ӧ�������ֽ��������ptr
		ACKPack pack;
		pack.FillData(0);

		//���ݰ�������ѡ��ȷ�ϰ����Ƿ����ط�����Ӧ��
		/*
			������Ҫ���ط������û������İ��ط��ð�;
			������Ҫ���Ӧ��ȷ����ȷ������Ӧ
			������Ҫ��Է���Ӧ��ȥһ����
		
		*/

		if (1)
		{

		}

		return 0;
	}

	
	int ACKReadHandle::Handle(void *ptr)
	{
		return 0;
	}

	int ACKReadHandle::HandleClose(void *ptr)
	{
		return 0;
	}

}

