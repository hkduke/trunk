#pragma once
#include "../Core/ManagePack.h"
#include "../Core/Any.h"
#include "../PackageTypeManager/BasePackage.h"
#include<map>
namespace NetCom
{
	class ManagePack;
	class  MessageTransePack:public ManagePack
	{
	public:
		MessageTransePack();
		~MessageTransePack();

		virtual int PaserPack(void * data, int lenth, int packId);

		static void Init();

		std::vector<BYTE>  GetData();

		int GetPackLenth();

		virtual int FillData(std::vector<Any> *  data,int packId);

		void FillData(std::vector<BYTE>* vect, int packID);

	public:
		//报文包管理器
		static std::map<int, BasePackage*> m_packageManagers;
	private:
		BasePackage* m_currentPackage;
	};

}

