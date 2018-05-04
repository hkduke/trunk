#include "ACKWriteHandle.h"
#include "../Core/ACKPack.h"
#include "../Core/Framework.h"
namespace NetCom
{
	ACKWriteHandle::ACKWriteHandle(EPackType packType,UINT packageID )
		:m_packageID(packageID),m_packType(packType)
	{
	}
	ACKWriteHandle::ACKWriteHandle()
	{
	}


	ACKWriteHandle::~ACKWriteHandle()
	{
	}

	int ACKWriteHandle::HandleEnter(void *ptr)
	{
		//根据包的类型名确定写包的类型
		ACKPack pack(m_packType, m_packageID);
		pack.FillData(0);
		Framework::GetInstance().GetTransportStratagy()->Send(111,pack.Data(),
			1024);
		return 0;
	}

	int ACKWriteHandle::Handle(void *ptr)
	{
		return 0;
	}

	int ACKWriteHandle::HandleClose(void *ptr)
	{
		return 0;
	}

}

