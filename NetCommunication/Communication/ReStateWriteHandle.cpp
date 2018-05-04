#include "ReStateWriteHandle.h"
#include "../Core/ReStatePack.h"
#include "../Core/Framework.h"
namespace NetCom 
{
	ReStateWriteHandle::ReStateWriteHandle()
	{
	}


	ReStateWriteHandle::~ReStateWriteHandle()
	{
	}

	int ReStateWriteHandle::HandleEnter(void *ptr)
	{
		ReStatePack pack;
		pack.FillData(0);

		//Framework::GetInstance().GetTransportStratagy()->Send(pack.Data(), pack.GetPackageSize());

		return 0;
	}

	int ReStateWriteHandle::Handle(void *ptr)
	{
		return 0;
	}

	int ReStateWriteHandle::HandleClose(void *ptr)
	{
		return 0;
	}

}


