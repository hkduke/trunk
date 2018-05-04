
#include "DyLibManager.h"
#include "DyLib.h"
//#include <boost/filesystem.hpp>
#include "Path.h"
namespace NetCom
{
	DyLibManager::DyLibManager(void)
	{
	}

	DyLibManager::~DyLibManager(void)
	{
		// 卸载所有的对象
		MapStrLib::iterator itor = m_mapStrLib.begin();
		for (; m_mapStrLib.end() != itor; ++itor)
		{
			itor->second->Unload();
			delete(itor->second);
		}

		m_mapStrLib.clear();
	}

	// 加载组件
	DyLib* DyLibManager::Load(const string& fileName)
	{
		// 判断当前文件是否存在
// 		boost::filesystem::path pathFile(fileName);
// 		if (!boost::filesystem::exists(pathFile) || \
// 			!boost::filesystem::is_regular_file(pathFile))
// 		{
// 			return (NULL);
// 		}
		NetCom::Path path_str(fileName);
		bool b = NetCom::Path::find(path_str.toString(Path::PATH_WINDOWS), fileName, path_str);

		if (!b)return NULL;


		// 查询文件
		MapStrLib::const_iterator cstItor = m_mapStrLib.find(fileName);
		// 判断是否存在
		if (m_mapStrLib.end() == cstItor)
		{
			DyLib* pLib = new DyLib(fileName.c_str());
			pLib->Load();
			m_mapStrLib[fileName] = pLib;
			return (pLib);
		}

		// 存在对象
		return (cstItor->second);
	}

	// 卸载组件
	void DyLibManager::Unload(DyLib* pLib)
	{
		// 查询当前是否存在
		MapStrLib::iterator itor = m_mapStrLib.find(pLib->GetName());
		// 判断是否存在
		if (m_mapStrLib.end() != itor)
		{
			// 不存在当前的指针对象
			m_mapStrLib.erase(itor);
		}
		
		// 卸载组件
		pLib->Unload();
		delete(pLib);
	}
}

