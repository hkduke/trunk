#pragma once
#include "../Core/ManagePack.h"
//#include "../PackageTypeManager/BasePackage.h"
#include <vector>
#include<iostream>
#include"../Core/Export.h"
#include<string.h>
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT PackManager :public ManagePack
	{
	public:
		PackManager();
		~PackManager();
		void Parse(void* ptr,int lenth);

		void SetFiledValue(std::string filedName, Any value);
	
		Any GetFiledValue(std::string filedName);

		void Fill(UInt32 topicID);

		//BasePackage m_currentPackage;

		void* GetData();

		static void Init();
		//static std::map<std::string, BasePackage> xmlManager;
		static std::map<int, std::string> m_IDMap;
	};
}


