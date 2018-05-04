#pragma once
#include "PackageBase.h"

namespace NetCom
{
	class DataPack :
		public PackageBase
	{
	public:
		DataPack();
		~DataPack();

		virtual int PaserPack();

		virtual int FillData();
	};
}


