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


		// 添加插件
		virtual void InstallPlugin(IPlugin* pPlugin);
		// 卸载插件
		virtual void UnInstallPlugin(IPlugin* pPlugin);
		// 导入插件
		virtual void LoadPlugin(const std::string& strPluginName);
	};
}