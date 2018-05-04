#pragma once
#include "ManagePack.h"

namespace NetCom
{
	class NodeExitPack :
		public ManagePack
	{
	public:
		NodeExitPack();
		~NodeExitPack();

		virtual int PaserPack(void *data);

		virtual int FillData(void* data);

	};
}


