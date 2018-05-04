#include "ReStateReadHandle.h"

namespace NetCom
{
	ReStateReadHandle::ReStateReadHandle()
	{
	}

	ReStateReadHandle::~ReStateReadHandle()
	{
	}

	int ReStateReadHandle::HandleEnter(void *ptr)
	{
		//解除所有事件，清空所有列表，发送加入节点信息

		return 0;
	}

	int ReStateReadHandle::Handle(void *ptr)
	{
		return 0;
	}

	int ReStateReadHandle::HandleClose(void *ptr)
	{
		return 0;
	}

}

