#pragma once
#include "../Core/ManagePack.h"
#include "../Core/Export.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT  HeartBeatPack:public ManagePack
	{
	public:
		HeartBeatPack();
		~HeartBeatPack();

		virtual int PaserPack() override;


		virtual int FillData(BYTE *data) override;

	};
}


