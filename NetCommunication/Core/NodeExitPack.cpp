#include "NodeExitPack.h"
#include "../Core/CommonTool.h"
#include "../Core/Any.h"
namespace NetCom
{
	NodeExitPack::NodeExitPack()
	{
	}


	NodeExitPack::~NodeExitPack()
	{
	}

	int NodeExitPack::PaserPack(void *data)
	{
		SetData(data, ToolClass::GetPacketSize(data));
		UINT32 nodeID = ToolClass::GetSourceDevID(data);
		return nodeID;
	}

	int NodeExitPack::FillData(void *data)
	{
		ManagePack::FillData((BYTE*)data);
		ToolClass::SetPacketType(m_data, NodeExit);
		return 0;
	}

}


