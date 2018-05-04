#pragma once
#include "Participator.h"

namespace NetCom
{
	class DataWriterListener :
		public Participator
	{
	public:
		DataWriterListener();
		~DataWriterListener();

		// 设置完数据进行提交
		void Commit();	

		template<typename T>
		void SetAttribute(const char * topic, T value)
		{
		}
	};
}




