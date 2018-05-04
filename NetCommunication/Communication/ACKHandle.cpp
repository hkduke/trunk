#include "ACKHandle.h"
#include "../Core/Framework.h"
#include "../Core/LogManager.h"

NetCom::ACKHandle::ACKHandle()
{
	SetEventType(Ack_Read);
}


NetCom::ACKHandle::~ACKHandle()
{
}

int NetCom::ACKHandle::HandleEnter(void *ptr)
{
	Framework::GetInstance().GetAckQueueManager()->Push(ptr, GetDataLen());
	//LogManager::GetInstance().WriteMessage("ACKHandle::HandleEnter 响应包到来 ");
		return 0;
}

int NetCom::ACKHandle::Handle(void *ptr)
{
	return 0;
}

int NetCom::ACKHandle::HandleClose(void *ptr)
{
	return 0;
}
