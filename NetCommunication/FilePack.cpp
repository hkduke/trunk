#include "FilePack.h"
#include "../Core/CommonTool.h"
#include "../Core/ResourceManager.h"
namespace NetCom
{
	FilePack::FilePack()
	{
	}


	FilePack::~FilePack()
	{
	}

	void FilePack::ParseFile()
	{
	}

	
	std::vector<FilePack> FilePack::GetFilePackages(void * data, int lenth, std::string fileName, int checkedLenth)
	{
		std::vector<FilePack> packList;
		if (!data)
		{
			return packList;
		}
		int n = lenth;
		int begin = 0;//记录文件打包的位置
		int packFlag = 0;//记录包的类型
		int packSize = 0;//记录包的大小
		int packNumber = 1;
		FilePack pack;
		int reserveNumber =pack.GetReserveNumber(fileName, checkedLenth);//计算的包的可用数据字节
		//总长度-可用长度-帧尾-帧尾校验和
		begin = 1024 - reserveNumber - 3;//首次开始写位置
		//如果总长度小于保留长度，则单包发送
		if (n < reserveNumber)
		{
			pack.FillHeader(0, lenth);
			pack.FillFilePack(data,15+checkedLenth+1+fileName.size(), lenth);
			packList.push_back(pack);
		}
		else
		{
			while (n > 0)
			{
				FilePack pack;
				if (begin == 0)
				{
					packFlag = 1;
					packSize = 1024 - 11 - 2;
				}
				else if (n < reserveNumber)
				{
					packFlag = 3;
					packSize = n;
				}
				else
				{
					packFlag = 2;
					packSize = 1024 - 11 - 2;
				}
				pack.FillHeader(packFlag, packSize);
				pack.FillFilePack(data, 15 + checkedLenth + 1 + fileName.size(), packSize);
			//	pack.FillFilePack(data,)
				packList.push_back(pack);
				begin -= reserveNumber;
				packNumber += 1;
			}
		}
		return packList;
	}

	void FilePack::FillHeader(int i, int packLenth)
	{
		//根据帧格式 创建文件报头
		int begin = 0;
		ToolClass::SetPackFramType(m_data, 0);
		ToolClass::SetPackFlag(m_data, i);
		ToolClass::SetPackProperity(m_data, 2);
		//设置包的长度
		begin = +1;
		ToolClass::SetFixData<UInt16>(m_data, begin, UInt16(packLenth));
		begin += 2;
		//设置包的主题号
		ToolClass::SetFixData<UInt16>(m_data, begin, EPackType::FileTranse);
		begin += 2;
		ToolClass::SetFixData<char>(m_data, begin, (char)ResourceManager::GetInstance().GetCurrentNode()->GetNodeID());
		begin += 1;
		ToolClass::SetFixData<char>(m_data, begin, (char)255);
		begin += 1;
		ToolClass::SetFixData<UInt32>(m_data, begin, (UInt32)time(0));
		begin += 4;
	}

	void FilePack::SetString(void* data, int begin, std::string str)
	{
		memcpy(((char*)data) + begin, str.c_str(),str.size());
	}

	int FilePack::GetReserveNumber(std::string fileName, int checkedleth)
	{
		int reserveNuber = 1024;
		//包的大小减于包头11，文件帧头3,文件校验码长度占的一个字节
		reserveNuber -= 15;
		int nameSize = fileName.size();
		//根据校验方法减于校验码
		reserveNuber -= checkedleth;
		ToolClass::SetFixData<char>(m_data, 14, (char)checkedleth);
		//设置校验码

		//包的大小减于文件长度的字节1
		reserveNuber -= 1;		
		//设置文件名长度
		ToolClass::SetFixData<char>(m_data, 14 + 1 + checkedleth, (char)fileName.size() - 1);
		////包的大小减于文件名占位
		reserveNuber -= (nameSize - 1);
		//设置文件名
		SetString(m_data, 14 + 1 + checkedleth + 1, fileName);
	}

	void FilePack::SetFrameID(int framID)
	{
		char heightchar = framID >> 16;
		UInt16 lowData = (UInt16)(framID && 65535);

		ToolClass::SetFixData<UInt16>(m_data, 11, lowData);
		ToolClass::SetFixData<char>(m_data, 13, heightchar);
	}

	void FilePack::FillFilePack(void * data, int begin, int lenth)
	{
		memcpy(((char*)m_data)+begin, data, lenth);
	}


}

