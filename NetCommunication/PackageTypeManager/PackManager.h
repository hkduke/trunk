#pragma once
#include "../Core/ManagePack.h"
#include "BasePackage.h"
#include <vector>
#include<iostream>
#include<string.h>
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT PackManager :public ManagePack
	{
	public:
		typedef void(*RecvFunc)(BasePackage* parement,UInt32 topicid);
		typedef std::map<UInt32, RecvFunc>MapRecvMap;
		PackManager();
		~PackManager();
		//分解包
		void Parse(void* ptr,int lenth);

		void SetFiledValue(std::string filedName, Any value);
	
		Any GetFiledValue(std::string filedName);

		void Fill(UInt32 topicID);

		BasePackage & GetCurrentBasePackage();
		BasePackage m_currentPackage;
		//注册外部调用函数，用来显示给用户数据
		static void RegisterFunction(RecvFunc func , UInt32 topicId);
		//初始化读取数据
		static void Init();
		//获取内存数据
		void* GetData();

		int GetPackLenth();
	private:
		
		//static RecvFunc m_func;
		static MapRecvMap m_FunMap;
		
		static std::map<std::string, BasePackage> xmlManager;
		static std::map<int, std::string> m_IDMap;
	};
}


