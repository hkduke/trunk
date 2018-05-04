#pragma once
#include "PackageBase.h"
#include "CoreCommon.h"

namespace NetCom
{
	// 按类型填充包数据
	class PackFactory
	{
	public:
		PackFactory();
		~PackFactory();

		static PackageBase*Construction(EPackType type);

	private:
		/*以下为管理包*/
		// 构造节点加入包
		static PackageBase* ConstructionNodeJoin();
		// 构造节点更新目录
		static PackageBase* ConstructionRefreshNodeDirectoryPack();
		// 构造节点更新包
		static PackageBase* ConstructionGainDirectoryPack();
		// 构造节点退出包
		static PackageBase* ConstructionNodeExitPack();
		// 构造节点目录包
		static PackageBase* ConstructionNodeDirectoryPack();
	};

}

