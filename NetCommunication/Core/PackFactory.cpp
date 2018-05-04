#include "PackFactory.h"

namespace NetCom
{
	PackFactory::PackFactory()
	{
	}


	PackFactory::~PackFactory()
	{
	}

	PackageBase* PackFactory::Construction(EPackType type)
	{
		return nullptr;
	}

	PackageBase * PackFactory::ConstructionNodeJoin()
	{
		return nullptr;
	}

	PackageBase * PackFactory::ConstructionRefreshNodeDirectoryPack()
	{
		return nullptr;
	}

	PackageBase * PackFactory::ConstructionGainDirectoryPack()
	{
		return nullptr;
	}

	PackageBase * PackFactory::ConstructionNodeExitPack()
	{
		return nullptr;
	}

	PackageBase * PackFactory::ConstructionNodeDirectoryPack()
	{
		return nullptr;
	}
}


