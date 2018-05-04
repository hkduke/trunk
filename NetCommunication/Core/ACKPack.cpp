#include "ACKPack.h"
#include "../Core/CommonTool.h"
#include "../Core/LogManager.h"
//#include "../Core/Checksum.h"
namespace NetCom
{
	ACKPack::ACKPack(EPackType packType, UINT packageID)
		:m_type(packType),m_packageID(packageID)
	{
		m_ackFlag = 0;
	}

	ACKPack::ACKPack()
	{
	}


	ACKPack::~ACKPack()
	{
	}

	int ACKPack::PaserPack(void * buff, UInt32 len)
	{
		m_sourceID = ToolClass::GetSourceDevID(buff);
		m_packageID = ToolClass::GetFixData<UInt32>(buff, 24);
		m_ackFlag = ToolClass::GetFixData<char>(buff, 23);
		/*LogManager::GetInstance().WriteMessage("ACKPack::PaserPack sourceID:%d,m_packageID:%d,m_ackFlag:%d\n"
			, (int)m_sourceID, (int)m_packageID, (int)m_ackFlag);*/
		return 0;
	}

	UInt32 ACKPack::GetSrcNodeId()
	{
		return m_sourceID;
	}

	int ACKPack::FillData(BYTE *data)
	{
		ManagePack::FillData(data);
		ToolClass::SetPacketType(m_data, EPackType::ACK);
		ToolClass::SetFixData<UInt16>(m_data, 21, (int)EPackType::ACK);
		ToolClass::SetFixData<char>(m_data,23, m_ackFlag);
		ToolClass::SetFixData<UInt32>(m_data, 24,(UInt32)m_packageID);
	

		return 0;
	}

	UInt32 ACKPack::GetAckFlag()
	{
		return m_ackFlag;
	}

	UInt32 ACKPack::GetFrameSerial()
	{
		return m_packageID;
	}

	void ACKPack::SetFramID(UInt16 framId)
	{
		m_packageID = framId;
	}

	void ACKPack::SetFileSourceID(UInt16 nodeID)
	{
		
	}

	int ACKPack::GetPackageSize()
	{
		return ManagePack::GetPackageSize() + FILEACKTPOINUMBERLENTH+ ACKSTATELENTH+ FILEFRAMIDLENTH;
	}

}
