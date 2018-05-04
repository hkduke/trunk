#include "FileTranseHandle.h"
#include <utility>
#include <map>

#include "../Core/FilePack.h"
#include "../Core/LogManager.h"
#include "../Core/ResourceManager.h"
#include "../Communication/FileTranseManager.h"
#include "../Core/ACKPack.h"
#include "../Core/Framework.h"

namespace NetCom
{
	FileTranseHandle::FileTranseHandle()
	{
		SetEventType(File_Read);
		
	}


	FileTranseHandle::~FileTranseHandle()
	{
	}

	int FileTranseHandle::HandleEnter(void * ptr)
	{
		//Timestamp currettime;
		m_nodeid = ToolClass::GetFixData<char>(ptr, 5);
		int fileNumber= FilePack::GetFileSerial(ptr);
		m_pFileTranseManager->SetFileNodeId(m_nodeid);
		MapOfstream &map = m_pFileTranseManager->GetMapOfstream(m_nodeid);
		FilePack pack;
		pack.ParseFile(ptr);
		//bool checksum = pack.GetCheckSumIsOk();
		UInt32 packType = ToolClass::GetPackFlag(ptr);
		UInt32 len = pack.GetLenth();
		void * data = pack.GetData();
		UInt32 ser = pack.GetFileSerial(ptr);	
		m_pFileTranseManager->PushFrameObj(data, len, ser, map);
		//LogManager::GetInstance().WriteMessage("FileTranseHandle::HandleEnter接收到文件包:类型:packType:%d:len:%d:serial:%d", (int)packType, (int)len,(int)ser);
		if (packType == 1)
		{
			LogManager::GetInstance().WriteMessage("FileTranseHandle::HandleEnter接收到文件包");
		}

		if (packType==3)
		{
			LogManager::GetInstance().WriteMessage("FileTranseHandle::HandleEnter文件收完");
			FileSerial fs(m_nodeid, ser);
			MapNodeFile & nodeFile = m_pFileTranseManager->GetMapNodeFile();
			MapNodeFile::iterator iterMap = (nodeFile.find(fs));
			if (iterMap != nodeFile.end())
			{
				//FileSerial t =((iterMap)->first);
				MapOfstream * ms = iterMap->second;
				//(iterMap)->first.SetMaxLength(ser);
				nodeFile[(iterMap)->first] = ms;
			}
			else
			{
				LogManager::GetInstance().WriteMessage("FileTranseHandle::HandleEnter文件没有找到");
			}
			bool b = m_pFileTranseManager->CheckSumFileSerid(m_nodeid);
			if (b)
			{
				m_pFileTranseManager->WirteFile(m_nodeid,pack.GetFileName());
			}
			else
			{
				LogManager::GetInstance().WriteMessage("FileTranseHandle::HandleEnter校验出问题");
			}
		}
		
		ACKPack ack;
		ack.SetFramID(ser);
		ack.FillData(0);
		//if (checksum)
		{
			Framework::GetInstance().GetTransportStratagy()->Send(111,ack.Data(), ack.GetPackageSize());
		}
		//std::cout << __FUNCTION__ << "*********************RHandleEnter::ACKPack:::::" << currettime.elapsed() << std::endl;

		return -1;
	}

	int FileTranseHandle::Handle(void *ptr)
	{
		return -1;
	}

	int FileTranseHandle::HandleClose(void * ptr)
	{
		return -1;
	}

	void FileTranseHandle::SetNodeId(UInt32 id)
	{
		m_nodeid = id;
	}
}

