#pragma once
#include "../Core/ManagePack.h"
namespace NetCom
{
	class LookupPublisherFailPack:public ManagePack
	{
	public:
		LookupPublisherFailPack();
		~LookupPublisherFailPack();

		virtual int PaserPack() ;


		virtual int FillData() ;

	};
}


