#pragma once
#include "CoreCommon.h"
namespace NetCom
{
	class PackHeader
	{
	public:
		EPackType m_packType;	// ������
		UINT m_packId;	// ����ʶ
		UINT m_src;	// ��Դ��ַ
		UINT  m_dsc;	// ����Ŀ�ĵ�
		UINT m_packDataSize;	// �����ݴ�С

		UINT m_priority;	// �����ȼ�
	};
}
