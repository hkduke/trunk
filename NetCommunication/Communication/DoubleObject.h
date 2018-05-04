#pragma once
#include "TypeObject.h"
namespace NetCom
{
	class DoubleObject :
		public TypeObject
	{
	public:
		DoubleObject();
		~DoubleObject();

		virtual TypeObject*  GetAttribute(char* convert);


		double value;
	};
}


