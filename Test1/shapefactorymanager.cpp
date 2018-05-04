#include "shapefactorymanager.h"

CElementFactoryManager::CElementFactoryManager()
{
}

CElementFactoryManager::~CElementFactoryManager()
{
}

CElementFactoryManager *CElementFactoryManager::instance()
{
	static CElementFactoryManager *_instance = NULL;
	if (_instance == NULL)
		_instance = new CElementFactoryManager();
	return _instance;
}
