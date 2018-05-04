#pragma once
#include "TypeObject.h"
#include "Export.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT CharObject :public TypeObject
	{
	public:
		CharObject();
		~CharObject();

		virtual TypeObject* GetAttribute(char* convert);

		char * value;
	};
}


