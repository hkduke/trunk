#pragma once
#include "PackageBase.h"
#include "CoreCommon.h"

namespace NetCom
{
	// ��������������
	class PackFactory
	{
	public:
		PackFactory();
		~PackFactory();

		static PackageBase*Construction(EPackType type);

	private:
		/*����Ϊ�����*/
		// ����ڵ�����
		static PackageBase* ConstructionNodeJoin();
		// ����ڵ����Ŀ¼
		static PackageBase* ConstructionRefreshNodeDirectoryPack();
		// ����ڵ���°�
		static PackageBase* ConstructionGainDirectoryPack();
		// ����ڵ��˳���
		static PackageBase* ConstructionNodeExitPack();
		// ����ڵ�Ŀ¼��
		static PackageBase* ConstructionNodeDirectoryPack();
	};

}

