#pragma once
#include "ManagePack.h"
#include <list>
namespace NetCom
{
	class NodeBase;
	class NETCOMMUNICATION_EXPORT NodeDirectoryPack :
		public ManagePack
	{
	public:
		NodeDirectoryPack();
		~NodeDirectoryPack();

		virtual std::list<NodeBase*> PaserPack(BYTE* data,int lenth);
		
		UINT GetPackTotalSize();

		//UINT GetHeaderTotalSize();

		virtual int FillData();

		//void PrintData();
	protected:

		
	};
}
//节点目录包


