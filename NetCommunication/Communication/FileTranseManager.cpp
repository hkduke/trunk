#include "FileTranseManager.h"
#include "../Core/LogManager.h"
#include <fstream>
#include "Framework.h"

namespace NetCom
{
	FileTranseManager::FileTranseManager():m_isRecEndPack(false), m_bIsEnableAck(false)
	{
		Init();
	}

	FileTranseManager::~FileTranseManager()
	{

	}

	void FileTranseManager::Init()
	{
		//m_bIsEnableAck = Framework::GetInstance().ConfigBool("FileACK");
	}

	

	bool FileTranseManager::WirteFile(UInt8 id,std::string fileName)
	{
		if (!HasId(id))
		{
			return false;
		}
		MapOfstream & stream = GetMapOfstream(id);
		MapOfstream::iterator iterMap = stream.begin();
		std::ofstream out(fileName, std::ofstream::binary);
		int i = 0;
		for (; iterMap!= stream.end(); iterMap++)
		{
			
			out.write((char*)iterMap->second._data, iterMap->second._len);
			i += iterMap->second._len;
		}
		out.close();
	}

	bool FileTranseManager::CheckSumFileSerid(UInt32 id /*= 0*/)
	{
		//if (id == 0) // 拿出第一个
		{
//			LogManager::GetInstance().WriteMessage("FileTranseManager::CheckSumFileSerid校验文件序号id:%d", id);
			FileSerial fs(id, 0);
			auto iterMap = m_fileData.find(fs);
			if (iterMap == m_fileData.end())
			{
				return false;
			}
			else
			{
				std::vector<UInt32>  ser;
				return Check(ser, (iterMap)->first._maxLength, *iterMap->second);
			}
		}
	}

	bool FileTranseManager::Check(std::vector<UInt32> & ser , UInt32 maxId,const MapOfstream &stream)
	{
		int serindex = 0;
		//if (maxId != stream.size())return false;
		for (auto iterMap = stream.begin() ; iterMap!= stream.end(); iterMap++)
		{
			if (iterMap->first != ++serindex)
			{
				ser.push_back(serindex);
			}
		}
		//LogManager::GetInstance().WriteMessage("FileTranseManager::Check:缺少的文件帧size:%d", ser.size());
		return ser.size() == 0;
	}


	void FileTranseManager::Check(UInt32 id)
	{

	}

}
