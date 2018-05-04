#include "PackageBase.h"

#include<iostream>
#include<fstream>
#include <bitset>
#include "../Core/LogManager.h"
#include "../Core/CommonTool.h"

namespace NetCom
{
	PackageBase::PackageBase()
	{
		m_data = nullptr;
		init();
	}


	PackageBase::~PackageBase()
	{
		if(m_data)
		delete[]m_data;
	}


	BYTE * PackageBase::Data()
	{
		return m_data;
	}

	UINT PackageBase::GetPriority()
	{
		//return m_header->m_priority;
		return 0;
	}

	void PackageBase::SetPriority(UINT pri)
	{
		//m_header->m_priority = pri;
	}


	int PackageBase::FillData(BYTE *data)
	{
		m_data = (BYTE *)malloc(strlen((char*)data) + 1);
		for (int i = 0; *data != '\0'; m_data++, data++) {
			*m_data = *data;
		}
		*m_data = '\0';
		return 0;
	}

	 int PackageBase::GetPackageSize()
	{
		return ToolClass::GetHeaderSize();
	}

	int PackageBase::PaserPack()
	{
		return -1;
	}

	void* PackageBase::init()
	{
		m_data = new BYTE[1024];
		memset(m_data, 0, 1024);
		assert(m_data);
		return m_data;
	}

	void PackageBase::SetData(void * data, int lenth)
	{
		memcpy(m_data, data, lenth);
	}
}

	

