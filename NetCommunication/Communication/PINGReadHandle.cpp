#include "PINGReadHandle.h"
#include "../Core/PingPack.h"

namespace NetCom
{
	PINGReadHandle::PINGReadHandle()
	{
	}


	PINGReadHandle::~PINGReadHandle()
	{
	}

	int PINGReadHandle::HandleEnter(void *ptr)
	{
		PingPack pack;
		pack.PaserPack();

		//ȡ��pingpack��ʱ��

		return 0;
	}

	int PINGReadHandle::Handle(void *ptr)
	{
		return 0;
	}

	int PINGReadHandle::HandleClose(void *ptr)
	{
		return 0;
	}

}
