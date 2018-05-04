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

		//取得pingpack的时间

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
