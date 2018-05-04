#pragma once
#include "ManagePack.h"

namespace NetCom
{
	// 更新目录包
	class RefreshNodeDirectoryPack :
		public ManagePack
	{
	public:
		RefreshNodeDirectoryPack();
		~RefreshNodeDirectoryPack();

		virtual int PaserPack();
		virtual int FillData();


	};

}

