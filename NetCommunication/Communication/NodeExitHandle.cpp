#include "NodeExitHandle.h"
#include"../Core/NodeExitPack.h"
#include "../Core/NodeBase.h"
#include "../Core/ResourceManager.h"
namespace NetCom
{
	NodeExitHandle::NodeExitHandle()
	{
	}


	NodeExitHandle::~NodeExitHandle()
	{
	}

	int NodeExitHandle::HandleEnter(void * ptr)
	{

		return -1;
	}


	int NodeExitHandle::Handle(void *ptr)
	{
		return -1;
	}

	int NodeExitHandle::HandleClose(void * ptr)
	{
		return -1;
	}
}

