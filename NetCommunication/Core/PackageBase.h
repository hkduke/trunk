#pragma once
#include "PackHeader.h"
#include <string.h>
#include <assert.h>
#include <iostream>
#include "../Communication/CharObject.h"
#include "Message.h"
#include "../Core/Types.h"
#include "../Core/Any.h"
namespace NetCom
{
	
	class NETCOMMUNICATION_EXPORT PackageBase
	{
	public:
		BYTE * m_data;	// ����   
		PackageBase();
		~PackageBase();

		BYTE *Data();
		UINT GetPriority();
		void SetPriority(UINT pri);

		virtual int PaserPack();
		
		void* init();

		virtual int FillData(BYTE *data);	// ��Ҫָ�����ݴ�С���ڰ�ͷ˵��,���ڼ̳�����䵽m_data

		virtual int GetPackageSize();
		
		void SetData(void* data, int lenth);
	
	};

}
