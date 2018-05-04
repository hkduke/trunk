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

		UINT m_NodeNum;	// 节点数	待定
		UINT m_topicNum;	// 主题数 ， 待定
		void* PaserPack(BYTE *data, int lenth);
		virtual int FillData(BYTE *data);
		

		virtual int GetPackageSize() override;

	private:
		std::string m_netStyle;
		std::string m_netIP;
	
	};

}

