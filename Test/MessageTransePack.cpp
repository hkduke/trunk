#include "MessageTransePack.h"
#include "ResourceManager.h"
#include "../Core/Any.h"
#include "../Core/LogManager.h"
#include "../Core/CommonTool.h"
#include "../Core/LogManager.h"
#include <iostream>
#include <vector>
#include "../Core/CommonTool.h"
#include <string>
namespace NetCom
{
	
	MessageTransePack::MessageTransePack()
	{

		
	}


	MessageTransePack::~MessageTransePack()
	{

	}

	int MessageTransePack::PaserPack(void * data,int lenth,int packId)
	{
		LogManager::GetInstance().WriteMessage("MessageTransePack::PaserPack:收到解析数据:%d", lenth);
		this->SetData(data, lenth);
		ManagePack::PrintData();
		int number = ToolClass::GetFixData<char>(m_data, ToolClass::GetHeaderSize());
		for (int i = 0; i < number; i++)
		{
			LogManager::GetInstance().WriteMessage("%d\n", ToolClass::GetFixData<char>(m_data, ToolClass::GetHeaderSize() + 1 + 4 * i));
		}
		return 0;
	}



	int MessageTransePack::FillData(std::vector<Any> * vectorData, int packID)
	{
		LogManager::GetInstance().WriteMessage("MessageTransePack::FillData: 开始封包");
		ManagePack::FillData(0);

		ToolClass::SetFixData<char>(m_data,ToolClass::GetHeaderSize() ,(char)(vectorData->size()));

		for (int i = 1; i < vectorData->size()-1; ++i)
		{
			ToolClass::SetFixData<int>(m_data, ToolClass::GetHeaderSize()+1+4*i, AnyCast<int>(vectorData->at(i)));
		}


		ToolClass::SetPacketType(m_data, MessageTranse);
		LogManager::GetInstance().WriteMessage("MessageTransePack::FillData:封包完成：size:%d\n",(int)ToolClass::GetPacketSize(m_data));

		return 0;
	}
}


