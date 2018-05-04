#pragma once

//#include "DictIterator.h"
// #include <map>
// class TopicRecord;

class Dict
{
public:
	Dict() ;
	~Dict() ;
	virtual void Insert(char * topic, const  char *attrName, const char * attrType, int size);

};

