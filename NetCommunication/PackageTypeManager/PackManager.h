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
		//�ֽ��
		void Parse(void* ptr,int lenth);

		void SetFiledValue(std::string filedName, Any value);
	
		Any GetFiledValue(std::string filedName);

		void Fill(UInt32 topicID);

		BasePackage & GetCurrentBasePackage();
		BasePackage m_currentPackage;
		//ע���ⲿ���ú�����������ʾ���û�����
		static void RegisterFunction(RecvFunc func , UInt32 topicId);
		//��ʼ����ȡ����
		static void Init();
		//��ȡ�ڴ�����
		void* GetData();

		int GetPackLenth();
	private:
		
		//static RecvFunc m_func;
		static MapRecvMap m_FunMap;
		
		static std::map<std::string, BasePackage> xmlManager;
		static std::map<int, std::string> m_IDMap;
	};
}


