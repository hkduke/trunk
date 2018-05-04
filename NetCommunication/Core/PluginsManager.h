#pragma  once

#include "../Public/IPlugin.h"
#include "SingleTmp.h"
#include <string>
namespace NetCom
{
	class PluginsManager :public Singleton<PluginsManager>
	{
	public:
		PluginsManager();
		~PluginsManager();


		// ��Ӳ��
		virtual void InstallPlugin(IPlugin* pPlugin);
		// ж�ز��
		virtual void UnInstallPlugin(IPlugin* pPlugin);
		// ������
		virtual void LoadPlugin(const std::string& strPluginName);
	};
}