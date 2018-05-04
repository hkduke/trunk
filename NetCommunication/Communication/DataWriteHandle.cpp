#include "DataWriteHandle.h"
#include "../PackageTypeManager/PackManager.h"
#include "../Core/Framework.h"
namespace NetCom
{
	DataWriteHandle::DataWriteHandle()
	{
	}


	DataWriteHandle::~DataWriteHandle()
	{
	}

	int DataWriteHandle::HandleEnter(void *ptr)
	{
 		PackManager* pack= (PackManager*)ptr;
 		void* data = pack->GetData();
 		Framework::GetInstance().GetTransportStratagy()->Send(111,(UInt8*)pack->GetData(),1024);
		delete pack;
		return 0;
	}

	int DataWriteHandle::Handle(void *ptr)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

	int DataWriteHandle::HandleClose(void *ptr)
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

}


