#pragma once
#include "TypeObject.h"

namespace NetCom
{
	class IntObject :
		public TypeObject
	{
	public:
		IntObject();
		~IntObject();

		virtual TypeObject* GetAttribute(char* convert);
		int value;
	};

}

