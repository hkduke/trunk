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

		// ���������ݽ����ύ
		void Commit();	

		template<typename T>
		void SetAttribute(const char * topic, T value)
		{
		}
	};
}




