#pragma once
#include "UserInterface.h"
#include "ResourceManager.h"
#include "../Communication/FileSendQueue.h"
#include "../Core/SingletonHolder.h"

namespace NetCom
{


	UserInterface::UserInterface()
	{

	}

	UserInterface::~UserInterface()
	{

	}

	void UserInterface::Push(UInt8 * data, UInt32 len)
	{
		//m_ResourceManager->GetSendQueue()->Push(data, len);
	}

	void UserInterface::Init()
	{
		m_ResourceManager = &ResourceManager::GetInstance();
	}

	namespace
	{
		static SingletonHolder<UserInterface> m_user;
	}
	UserInterface & UserInterface::GetInstance()
	{
		return *m_user.get();
	}

}

