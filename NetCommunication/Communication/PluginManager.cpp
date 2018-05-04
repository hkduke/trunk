#include "PluginManager.h"
#include <algorithm>
//#include <boost/foreach.hpp>

namespace NetCom
{
	void PluginManager::LoadPlugin(const string &strPath)
	{
		// 载入插件
		DyLib* pLib = DyLibManager::GetInstance().Load(strPath);
		if (NULL == pLib)
		{
			CoreComponent::GetInstance().WriteLogMsg("插件库不存在" + strPath, ERROR_NOT_FIND);
			return;
		}
		// 查询是否存在当前插件
		PluginLibList::const_iterator cstItor = std::find(m_pluginLibs.begin(), m_pluginLibs.end(), pLib);
		if (m_pluginLibs.end() != cstItor)
		{
			// 当前插件已经存在
			return;
		}

		//调用注册函数
		DLL_INSTANLL_PLUGIN pFunc = (DLL_INSTANLL_PLUGIN)pLib->GetSymbol("Initialise");
		if (NULL == pFunc)
		{
			CoreComponent::GetInstance().WriteLogMsg(strPath + "无法找到插件接口函数Initialise", ERROR_NOT_FIND);
			DyLibManager::GetInstance().Unload(pLib);

			return;
		}

		// 还未加载， 插件
		m_pluginLibs.push_back(pLib);

		pFunc();
	}

	void PluginManager::LoadAllPlugins(const string & dir)
	{

	}

	void PluginManager::GetFilesInPath(const string& strPath,const string& strEx, Files& files)
	{
		// _chdir(strPath.c_str());
// 		boost::filesystem::path dir(strPath);
// 		// 判断路径是否存在
// 		if (!boost::filesystem::exists(dir))
// 		{
// 			ILogManager::GetInstance().SetLogMessage(strPath + "： 路径不存在", ERROR_NOT_FIND);
// 			return;
// 		}
// 
// 		// 判断是否为一个目录
// 		if (!boost::filesystem::is_directory(dir))
// 		{
// 			CoreComponent::GetInstance().WriteLogMsg(strPath + " ：不是一个目录", ERROR_NOT_FIND);
// 			return;
// 		}
// 
// 		// 遍历当前目录下所有后缀文件
// 		namespace FileSystem = boost::filesystem;
// 		FileSystem::directory_iterator endItor;
// 		for (FileSystem::directory_iterator itor(dir); itor != endItor; ++itor)
// 		{
// 			const FileSystem::path& filePath = itor->path();
// 			if (FileSystem::is_regular_file(itor->status())
// 				&& 0 == filePath.extension().string().compare(strEx))  
// 			{  
// 				// 获得文件
// 				files.push_back(filePath.filename().string());
// 			} 
// 		}
	}

	void PluginManager::GetAllPlugins()
	{
		const string strPath = "./Plugin/";
		// 获取当前目录下所有的文件
		
		Files files;
		GetFilesInPath(strPath, ".dll", files);

		// 优先加载配置文件中的插件
		//const string strOrderPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Config/ComManager/order.cfg";

		typedef std::vector<string> ListFileNames;
		ListFileNames listFileNames;

// 		FileUtil fileUtil(strOrderPath);
// 		while (!fileUtil.Eof())
// 		{
// 			VRString str = fileUtil.GetLine();
// 			listFileNames.push_back(str);
// 		}

		// 首先添加项
		// 遍历所有文件
		for (ListFileNames::const_iterator cstItor = listFileNames.begin(); listFileNames.end() != cstItor; ++cstItor)
		{
			LoadPlugin(strPath + (*cstItor));

			// 从其他添加列表中移除
			Files::iterator itor = std::find(files.begin(), files.end(), *cstItor);
			if (files.end() != itor)
			{
				files.erase(itor);
			}

		}

		// 遍历所有文件
		for (Files::const_iterator cstItor = files.begin(); files.end() != cstItor; ++cstItor)
		{
			LoadPlugin(strPath + (*cstItor));
		}
	}

}

