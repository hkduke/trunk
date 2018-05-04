#pragma once
#include <QMap>
#include "element.h"

class CShapeFactory
{
public:
	virtual CElement* create() = 0;
};

template <typename CElement>
class CElementFactory : public CShapeFactory
{
public:
	CElement *create() { return new CElement(); }
};

class CElementFactoryManager
{
public:
	~CElementFactoryManager();
public:
	static CElementFactoryManager *instance();
	CElement* create(const QString &type)
	{
		if (!m_map.contains(type)) return NULL;
		return m_map[type]->create();
	}

	template <typename Type> bool registerType()
	{
		m_map.insert(Type::staticTypeName(), new CElementFactory<Type>);
		return true;
	}
private:
	CElementFactoryManager();
private:
	QMap<QString, CShapeFactory*> m_map;
};

#define REGISTER_SHAPE_FACTORY(type) \
	bool b##type = CElementFactoryManager::instance()->registerType<type>();
