#pragma once
#include "ManagePack.h"

namespace NetCom
{
	class NETCOMMUNICATION_EXPORT NodeJoinPack :
		public ManagePack
	{
	public:
		NodeJoinPack();
		~NodeJoinPack();

		UINT m_NodeNum;	// �ڵ���	����
		UINT m_topicNum;	// ������ �� ����
		void* PaserPack(BYTE *data, int lenth);
		virtual int FillData(BYTE *data);
		

		virtual int GetPackageSize() override;

	private:
		std::string m_netStyle;
		std::string m_netIP;
	
	};

}

