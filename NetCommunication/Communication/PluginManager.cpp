#include "PluginManager.h"
#include <algorithm>
//#include <boost/foreach.hpp>

namespace NetCom
{
	void PluginManager::LoadPlugin(const string &strPath)
	{
		// ������
		DyLib* pLib = DyLibManager::GetInstance().Load(strPath);
		if (NULL == pLib)
		{
			CoreComponent::GetInstance().WriteLogMsg("����ⲻ����" + strPath, ERROR_NOT_FIND);
			return;
		}
		// ��ѯ�Ƿ���ڵ�ǰ���
		PluginLibList::const_iterator cstItor = std::find(m_pluginLibs.begin(), m_pluginLibs.end(), pLib);
		if (m_pluginLibs.end() != cstItor)
		{
			// ��ǰ����Ѿ�����
			return;
		}

		//����ע�ắ��
		DLL_INSTANLL_PLUGIN pFunc = (DLL_INSTANLL_PLUGIN)pLib->GetSymbol("Initialise");
		if (NULL == pFunc)
		{
			CoreComponent::GetInstance().WriteLogMsg(strPath + "�޷��ҵ�����ӿں���Initialise", ERROR_NOT_FIND);
			DyLibManager::GetInstance().Unload(pLib);

			return;
		}

		// ��δ���أ� ���
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
// 		// �ж�·���Ƿ����
// 		if (!boost::filesystem::exists(dir))
// 		{
// 			ILogManager::GetInstance().SetLogMessage(strPath + "�� ·��������", ERROR_NOT_FIND);
// 			return;
// 		}
// 
// 		// �ж��Ƿ�Ϊһ��Ŀ¼
// 		if (!boost::filesystem::is_directory(dir))
// 		{
// 			CoreComponent::GetInstance().WriteLogMsg(strPath + " ������һ��Ŀ¼", ERROR_NOT_FIND);
// 			return;
// 		}
// 
// 		// ������ǰĿ¼�����к�׺�ļ�
// 		namespace FileSystem = boost::filesystem;
// 		FileSystem::directory_iterator endItor;
// 		for (FileSystem::directory_iterator itor(dir); itor != endItor; ++itor)
// 		{
// 			const FileSystem::path& filePath = itor->path();
// 			if (FileSystem::is_regular_file(itor->status())
// 				&& 0 == filePath.extension().string().compare(strEx))  
// 			{  
// 				// ����ļ�
// 				files.push_back(filePath.filename().string());
// 			} 
// 		}
	}

	void PluginManager::GetAllPlugins()
	{
		const string strPath = "./Plugin/";
		// ��ȡ��ǰĿ¼�����е��ļ�
		
		Files files;
		GetFilesInPath(strPath, ".dll", files);

		// ���ȼ��������ļ��еĲ��
		//const string strOrderPath = IComManager::GetInstance().GetComManagerConfig()->GetCurPath() + "/Config/ComManager/order.cfg";

		typedef std::vector<string> ListFileNames;
		ListFileNames listFileNames;

// 		FileUtil fileUtil(strOrderPath);
// 		while (!fileUtil.Eof())
// 		{
// 			VRString str = fileUtil.GetLine();
// 			listFileNames.push_back(str);
// 		}

		// ���������
		// ���������ļ�
		for (ListFileNames::const_iterator cstItor = listFileNames.begin(); listFileNames.end() != cstItor; ++cstItor)
		{
			LoadPlugin(strPath + (*cstItor));

			// ����������б����Ƴ�
			Files::iterator itor = std::find(files.begin(), files.end(), *cstItor);
			if (files.end() != itor)
			{
				files.erase(itor);
			}

		}

		// ���������ļ�
		for (Files::const_iterator cstItor = files.begin(); files.end() != cstItor; ++cstItor)
		{
			LoadPlugin(strPath + (*cstItor));
		}
	}

}

