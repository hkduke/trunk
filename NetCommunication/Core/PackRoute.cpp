#include "PackRoute.h"
#include "../Core/CommonTool.h"
#include <assert.h>
#include "Framework.h"
#include "../Communication/DataReadHandle.h"
#include "../Communication/TopicPublisherReadHandle.h"
#include "../Core/MessageRouteProcess.h"
#include "LogManager.h"
#include "../Communication/FileTranseHandle.h"
#include "../Communication/FileTranseManager.h"
#include "../Core/ResourceManager.h"
#include "../Communication/ACKHandle.h"
namespace NetCom
{
	PackRoute::PackRoute()
	{
	}


	PackRoute::~PackRoute()
	{
	}

	void PackRoute::GenerateHandle(UInt8 * data, UInt32 len)
	{

		int msgType = ToolClass::GetPacketType(data);
		//std::cout << "PackRoute::GenerateHandle msgType::" << msgType << endl;
		EventHandle * handle = nullptr;
		switch (msgType)
		{
		case TopicPublisher:
		{
			handle = new TopicPublisherReadHandle;
			handle->SetDataPtr(data);
			handle->SetDataLen(len);

			break;
		}
		case TopicDiscribe:
		{
			break;
		}
		case TopicPublisherList:
		{
			break;
		}
		case MessageTranse:
		{
			handle = new DataReadHandle;
			handle->SetDataLen(len);
			handle->SetDataPtr(data);
			//LogManager::GetInstance().WriteMessage("PackRoute::GenerateHandle:生成事件处理:数据报文%d", (Int32)len);
			break;
		}
		case FileTranse: // 文件传输
		{
			handle = new FileTranseHandle;
			FileTranseManager * ptr = ResourceManager::GetInstance().GetFileTranseManager();
			handle->SetDataLen(len);
			handle->SetDataPtr(data);

			// 获取节点ID
			UInt8 id = ToolClass::GetFixData<UInt8>(data, 6);
			((FileTranseHandle*)handle)->SetNodeId(id);
			((FileTranseHandle*)handle)->SetFileTranseManager(ptr);
			break;
		}

		case ACK:
		{
			Timestamp timeStamp;
			handle = new ACKHandle;
			handle->SetDataLen(len);
			handle->SetDataPtr(data);
			std::cout << __FUNCTION__ << (int)timeStamp.elapsed() << std::endl;
			break;
		}
		default:
		{
			if (msgType > 10100 && msgType < 11201)
			{
				handle = new DataReadHandle;
				handle->SetDataLen(len);
				handle->SetDataPtr(data);
				//LogManager::GetInstance().WriteMessage("PackRoute::GenerateHandle:生成事件处理:数据报文%d", (Int32)len);
				break;
			}
			break;
		}

		}
		if (handle)
		{
			//Framework::GetInstance().GetMessageRouteProcess()->GetEventManager()->PushEvent(handle);
			//if (manager)
			{
				EventManager::GetInstance().PushEvent(handle);
				//LogManager::GetInstance().WriteMessage("PackRoute::GenerateHandle:压入事件处理:数据报文:地址为:%p", (Int32)handle);
			}

		}



	}

}

