#include "PluginManager.h"
#include <algorithm>
#include <iostream>
#include "../Public/ITransportSendStrategy.h"
//#include <boost/foreach.hpp>

namespace NetCom
{

	PluginManager::PluginManager():m_transport(nullptr)
	{

	}

	void PluginManager::LoadPlugin(const string &strName)
	{
		std::string libName(strName);
		libName += SharedLibrary::suffix();
		m_netLoader.loadLibrary(libName);
// 		PluginLoader::Iterator it(m_netLoader.begin());
// 		PluginLoader::Iterator end(m_netLoader.end());
// 		for (; it != end; ++it)
// 		{
// 			std::cout << "lib path: " << it->first << std::endl;
// 			PluginManifest::Iterator itMan(it->second->begin());
// 			PluginManifest::Iterator endMan(it->second->end());
// 			for (; itMan != endMan; ++itMan)
// 				std::cout << itMan->name() << std::endl;
// 		}
		m_transport = m_netLoader.create("NetCom::TCPTransportSendStrategy");
		std::string msg("test,data");
		m_transport->Send(111,(UInt8*)msg.data(), msg.length());
	}

	void PluginManager::LoadAllPlugins(const string & dir)
	{

	}

}

