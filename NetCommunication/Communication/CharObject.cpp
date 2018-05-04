#include "CharObject.h"

#include <stdlib.h>
#include <string.h>
namespace NetCom
{
	CharObject::CharObject()
	{
		value = (char*)malloc(32);
		memset(value, 0, 32);
	}


	CharObject::~CharObject()
	{
	}

	TypeObject* CharObject::GetAttribute(char * convert)
	{
		memset(value, 0, 32);
		memcpy(value, convert, strlen(convert));
		return this;
	}
}