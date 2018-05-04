

#include <stdlib.h>
#include "IntObject.h"

namespace NetCom
{
	IntObject::IntObject()
	{

	}

	IntObject::~IntObject()
	{

	}

	TypeObject* IntObject::GetAttribute(char* convert)
	{
		value = atoi(convert);
		return this;
	}
}


