#include "DoubleObject.h"

#include <stdlib.h>
namespace NetCom
{
	DoubleObject::DoubleObject()
	{
	}


	DoubleObject::~DoubleObject()
	{
	}

	TypeObject* DoubleObject::GetAttribute(char* convert)
	{
		value = atof(convert);
		return this;
	}
}

