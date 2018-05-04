#pragma once
#include "../Core/PackageBase.h"
#include "../Core/CoreCommon.h"
#include "../Core/ManagePack.h"
namespace NetCom
{
	const int FILEACKTPOINUMBERLENTH = 2;
	const int ACKSTATELENTH = 1;
	const int FILEFRAMIDLENTH = 4;
	class ACKPack:public ManagePack
	{
	public:
		ACKPack(EPackType packType,UINT packageID);
		ACKPack();
		~ACKPack();

		virtual int PaserPack(void * buff , UInt32 len) ;

		UInt32 GetSrcNodeId();
		virtual int FillData(BYTE *data) override;//应答包根据传入的类型，确认收到包后的处理措施

		UInt32 GetAckFlag(); //0 应答失败，1成功
		UInt32 GetFrameSerial();

		void SetFramID(UInt16 framId);

		void SetFileSourceID(UInt16 nodeID);

		virtual int GetPackageSize();

	private:

		EPackType m_type;

		UINT m_packageID;

		UINT m_sourceID;

		int m_ackFlag;
	};

}

