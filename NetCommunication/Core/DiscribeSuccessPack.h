#pragma once
#include "../Core/ManagePack.h"
namespace NetCom
{

	class DiscribeSuccessPack:public ManagePack
	{
	public:
		DiscribeSuccessPack();
		~DiscribeSuccessPack();

		virtual int PaserPack() ;


		virtual int FillData() ;

	};
}


