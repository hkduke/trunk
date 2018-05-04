#pragma once
#include "PackageBase.h"
#include "NodeBase.h"

namespace NetCom
{
	class NETCOMMUNICATION_EXPORT ManagePack :
		public PackageBase
	{
	public:
		ManagePack();
		~ManagePack();

		NodeBase* m_Node;

		virtual int PaserPack();
		virtual int FillData(BYTE *data);
		virtual void PrintData();

	};
}


