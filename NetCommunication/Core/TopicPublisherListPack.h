#pragma once
#include "../Core/ManagePack.h"
namespace NetCom
{
	class TopicPublisherListPack:public ManagePack
	{
	public:
		TopicPublisherListPack();
		~TopicPublisherListPack();

		virtual int PaserPack();


		virtual int FillData();

	};
}

