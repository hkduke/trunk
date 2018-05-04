
#ifndef DYLIBMANAGER_H
#define DYLIBMANAGER_H

#pragma once
#include "SingleTmp.h"
#include <string>
#include <map>
using namespace std;

namespace NetCom
{
	class DyLib;

	class DyLibManager : public Singleton<DyLibManager>
	{
	public:
		explicit DyLibManager(void);
		virtual ~DyLibManager(void);

	public:
		// �������
		DyLib* Load(const string& fileName);
		// ж�����
		void Unload(DyLib* pLib);

	private:
		typedef std::map<string, DyLib*> MapStrLib;
		MapStrLib m_mapStrLib;
	};

}

#endif // DYLIBMANAGER_H
