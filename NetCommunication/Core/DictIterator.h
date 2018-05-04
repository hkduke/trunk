#pragma once
#include "Dict.h"
#include <string>
#include <map>
#include <assert.h>

class TopicRecord;

template <typename T >
class DictIterator
{

	//typedef std::pair<DictIter, DictIter> Range;
public:
	DictIterator(T *data):m_data(data){}
	~DictIterator() {};


// 	virtual Range equal_range(const char * topic)
// 	{
// 		return m_data->m_data.equal_range(topic);
// 	}

	bool Insert(T::_K key, T::_V value)
	{
 		assert(m_data);
 		m_data->m_data.insert(std::pair<T::_K,T::_V>(key, value));
		return false;
	}

	T* m_data;

};

