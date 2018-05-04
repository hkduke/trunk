#include "HeartBeatPack.h"
#include "../Core/CommonTool.h"

namespace NetCom
{
	HeartBeatPack::HeartBeatPack()
	{
	}


	HeartBeatPack::~HeartBeatPack()
	{
	}

	int HeartBeatPack::PaserPack()
	{
		return 0;
	}

	int HeartBeatPack::FillData(BYTE *data)
	{
		ManagePack::FillData(data);
		ToolClass::SetPacketType(m_data, HEARTBEAT);
		return 0;
	}



}
