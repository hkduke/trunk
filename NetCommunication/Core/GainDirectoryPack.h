#pragma once
#include "ManagePack.h"

namespace NetCom
{
	// 获取节点目录
	class GainDirectoryPack :
		public ManagePack
	{
	public:
		GainDirectoryPack();
		~GainDirectoryPack();

		virtual int PaserPack();
		virtual int FillData();
	};

}

