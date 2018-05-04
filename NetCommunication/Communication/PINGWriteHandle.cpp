#include "PINGWriteHandle.h"
#include "../Core/PingPack.h"
#include "../Core/Framework.h"
namespace NetCom
{
	PINGWriteHandle::PINGWriteHandle()
	{
	}


	PINGWriteHandle::~PINGWriteHandle()
	{
	}

	int PINGWriteHandle::HandleEnter(void *ptr)
	{
		PingPack pack;
		pack.FillData(0);

		Framework::GetInstance().GetTransportStratagy()->Send(111,pack.Data(), pack.GetPackageSize());

		return 0;
	}

	int PINGWriteHandle::Handle(void *ptr)
	{
		return 0;
	}

	int PINGWriteHandle::HandleClose(void *ptr)
	{
		return 0;
	}

}
