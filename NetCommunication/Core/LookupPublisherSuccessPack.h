#pragma once
#include "../Core/ManagePack.h"
namespace NetCom
{
	class LookupPublisherSuccessPack:public ManagePack
	{
	public:
		LookupPublisherSuccessPack();
		~LookupPublisherSuccessPack();

		virtual int PaserPack() ;


		virtual int FillData() ;

	};
}


