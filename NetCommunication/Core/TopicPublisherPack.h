#pragma once

#include "../Core/ManagePack.h"
#include <iostream>
#include <list>

namespace NetCom
{
	class ManagePack;
	class Participator;
	class NETCOMMUNICATION_EXPORT TopicPublisherPack:public ManagePack
	{
	public:
		TopicPublisherPack();
		~TopicPublisherPack();

		std::list<Participator*>  PaserPack(BYTE* data,int lenth);

		virtual int FillData(EPackType type) ;


		virtual int GetPackageSize() override;

	public:
		unsigned int m_topicID;
		std::string m_topicNumber;
		int m_packageSize;
	};


}

