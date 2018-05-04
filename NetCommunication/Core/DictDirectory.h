#pragma once

#include "CoreCommon.h"

#include "Dict.h"
class TypeObject;
class DictFrame;

namespace NetCom
{
	class DictDirectory
	{
	public:
		DictDirectory() ;
		~DictDirectory() ;
		virtual int Init();
		Dict * GetDict();
		template <typename T>
		void SetAttribute(char * topic, char * attrName, T value)
		{

		}

		virtual TypeObject* GetAttribute(const char * topic, const char* attr)
		{
			return 0;
		}
		Dict* m_Dict;
		//DictIterator<Dict, std::string, TopicRecord*>* m_DictItor;
		char * bufValuel;
		DictFrame*  m_df;
		BYTE * m_senddatabuf;
		BYTE * m_receivedatabuf;
		TypeObject * doubleObject;
		TypeObject * intObject;
		TypeObject * charPointerObject;
	};

}

