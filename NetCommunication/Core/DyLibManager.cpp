
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
		// ж�����еĶ���
		MapStrLib::iterator itor = m_mapStrLib.begin();
		for (; m_mapStrLib.end() != itor; ++itor)
		{
			itor->second->Unload();
			delete(itor->second);
		}

		m_mapStrLib.clear();
	}

	// �������
	DyLib* DyLibManager::Load(const string& fileName)
	{
		// �жϵ�ǰ�ļ��Ƿ����
// 		boost::filesystem::path pathFile(fileName);
// 		if (!boost::filesystem::exists(pathFile) || \
// 			!boost::filesystem::is_regular_file(pathFile))
// 		{
// 			return (NULL);
// 		}
		NetCom::Path path_str(fileName);
		bool b = NetCom::Path::find(path_str.toString(Path::PATH_WINDOWS), fileName, path_str);

		if (!b)return NULL;


		// ��ѯ�ļ�
		MapStrLib::const_iterator cstItor = m_mapStrLib.find(fileName);
		// �ж��Ƿ����
		if (m_mapStrLib.end() == cstItor)
		{
			DyLib* pLib = new DyLib(fileName.c_str());
			pLib->Load();
			m_mapStrLib[fileName] = pLib;
			return (pLib);
		}

		// ���ڶ���
		return (cstItor->second);
	}

	// ж�����
	void DyLibManager::Unload(DyLib* pLib)
	{
		// ��ѯ��ǰ�Ƿ����
		MapStrLib::iterator itor = m_mapStrLib.find(pLib->GetName());
		// �ж��Ƿ����
		if (m_mapStrLib.end() != itor)
		{
			// �����ڵ�ǰ��ָ�����
			m_mapStrLib.erase(itor);
		}
		
		// ж�����
		pLib->Unload();
		delete(pLib);
	}
}

