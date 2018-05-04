#pragma once

#include <string>
using namespace std;
#include "ClassLoader.h"

#include <vector>
namespace NetCom
{
	
	class ITransportSendStrategy;
	class PluginManager
	{
	public:
		typedef ClassLoader<ITransportSendStrategy> PluginLoader;
		typedef Manifest<ITransportSendStrategy> PluginManifest;
	public:
		typedef std::vector<string> Files;
		 PluginManager();
		 ~PluginManager(){};

		 void LoadPlugin(const string &strName);
		  
		 void LoadAllPlugins(const string & dir);

		 
	private:
		ITransportSendStrategy * m_transport;
		PluginLoader m_netLoader;
	};
}
