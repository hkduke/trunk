#include "ManagePack.h"
#include <iostream>
#include "../Core/DateTime.h"
#include "ResourceManager.h"
#include "../Core/CommonTool.h"
#include <string>
#include <time.h>
#include<stdlib.h>
namespace NetCom
{
	ManagePack::ManagePack()
	{
	}


	ManagePack::~ManagePack()
	{
	}

	int ManagePack::PaserPack()
	{
		return 0;
	}

	int ManagePack::FillData(BYTE *data)
	{
		ToolClass::SetPackFramType(m_data, 0);
		ToolClass::SetPackFlag(m_data, 0);
		ToolClass::SetPackProperity(m_data, 0);
		ToolClass::SetPacketSize(m_data, 21);
		ToolClass::SetPackGeneralTime(m_data, (long)time(NULL));
		ToolClass::SetSourceDevID(m_data,(int)ResourceManager::GetInstance().GetCurrentNode()->GetNodeID());
		return 0;		   
	}

	void ManagePack::PrintData()
	{
	}

}
