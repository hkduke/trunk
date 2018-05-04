#pragma once
#include "../Core/PackageBase.h"
namespace NetCom
{
	class PingPack:public PackageBase
	{
	public:
		PingPack();
		~PingPack();

		virtual int PaserPack() override;


		virtual int FillData(BYTE *data) override;

	};

}

