#pragma once
#include "../Core/PackageBase.h"
namespace NetCom
{
	class ReStatePack:public PackageBase
	{
	public:
		ReStatePack();
		~ReStatePack();

		virtual int PaserPack() override;


		virtual int FillData(BYTE *data) override;

	};
}


