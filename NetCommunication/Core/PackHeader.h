#pragma once
#include "CoreCommon.h"
namespace NetCom
{
	class PackHeader
	{
	public:
		EPackType m_packType;	// 包类型
		UINT m_packId;	// 包标识
		UINT m_src;	// 包源地址
		UINT  m_dsc;	// 包的目的地
		UINT m_packDataSize;	// 包数据大小

		UINT m_priority;	// 包优先级
	};
}
