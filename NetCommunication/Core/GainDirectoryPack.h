#pragma once
#include "ManagePack.h"

namespace NetCom
{
	// ��ȡ�ڵ�Ŀ¼
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

