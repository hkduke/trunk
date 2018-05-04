#pragma once
#include "../Core/ManagePack.h"
namespace NetCom
{

	class DiscribeFailPack:public ManagePack
	{
	public:
		DiscribeFailPack();
		~DiscribeFailPack();

		virtual int PaserPack();


		virtual int FillData() ;

	};
}


