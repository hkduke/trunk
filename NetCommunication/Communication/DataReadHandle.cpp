#include "DataReadHandle.h"
#include "../Core/CommonTool.h"
#include "../Core/LogManager.h"
#include "../Core/ResourceManager.h"
#include "../PackageTypeManager/PackManager.h"

namespace NetCom
{
	DataReadHandle::DataReadHandle()
	{
		m_eventType = DataPacket_Read;
	}


	DataReadHandle::~DataReadHandle()
	{
	}

	int DataReadHandle::HandleEnter(void *ptr)
	{

 		if (ToolClass::GetFixData<UInt8>(ptr,5) == ResourceManager::GetInstance().GetCurrentNode()->GetNodeID())
 		{
 			LogManager::GetInstance().WriteMessage("接收到本主机的消息，退出;");
 			return 0;
 		}
 
		PackManager m_pack;
 		m_pack.Parse(ptr, 256);

		return 0;
	}

	int DataReadHandle::Handle(void * ptr)
	{
		return 0;
	}

	int DataReadHandle::HandleClose(void * ptr)
	{
		return 0;
	}

// 	PackManager DataReadHandle::GetPackage()
// 	{
// 		return m_pack;
// 	}

}

