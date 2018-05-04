#include "DictDirectory.h"
#include "DictImp.h"
#include <map>

namespace NetCom
{
	DictDirectory::DictDirectory()
	{
		Init();
	}


	DictDirectory::~DictDirectory()
	{
	}

	int DictDirectory::Init()
	{
		m_Dict = new DictImp;
		//m_DictItor = new DictIterator<DictImp<std::string, TopicRecord*> >(m_Dict);
		return 1;
	}

	Dict * DictDirectory::GetDict()
	{
		return m_Dict;
	}

}
