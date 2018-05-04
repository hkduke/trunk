#pragma once
#include "DictDirectory.h"

namespace NetCom
{
	class DictDirectoryImp :
		public DictDirectory
	{
	public:
		DictDirectoryImp();
		~DictDirectoryImp();

		virtual int Init();

		// 	template <typename T>
		// 	virtual void SetAttribute(char * topic, char * attrName, T value)
		// 	{
		// 
		// 	}

		virtual TypeObject* GetAttribute(const char * topic, const char* attr)
		{
			return nullptr;
		}

	};
}


