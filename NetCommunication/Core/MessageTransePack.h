#pragma once
#include "../Core/ManagePack.h"
#include "../Core/Any.h"
#include <vector>
#include<map>
namespace NetCom
{
	class ManagePack;
	class  NETCOMMUNICATION_EXPORT MessageTransePack:public ManagePack
	{
	public:
		MessageTransePack();
		~MessageTransePack();

		virtual int PaserPack(void * data, int lenth, int packId);

		virtual int FillData(std::vector<Any> *  data,int packId);

		void FillData(std::vector<BYTE>* vect, int packID);

	};

}

