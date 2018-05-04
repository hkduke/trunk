#pragma once
#include "ACKHandle.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT ACKWriteHandle:public ACKHandle
	{
	public:
		ACKWriteHandle(EPackType packType,UINT m_packageID);
		ACKWriteHandle();
		~ACKWriteHandle();

		virtual int HandleEnter(void *ptr) override;


		virtual int Handle(void *ptr) override;


		virtual int HandleClose(void *ptr) override;

	private:
		UINT m_packageID;
		EPackType m_packType;
	};

}

