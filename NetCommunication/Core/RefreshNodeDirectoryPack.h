#pragma once
#include "ManagePack.h"

namespace NetCom
{
	// ����Ŀ¼��
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

