#include "DataWriterListener.h"


namespace NetCom
{
	DataWriterListener::DataWriterListener()
	{
		SetListenerType(DataWriter);
	}


	DataWriterListener::~DataWriterListener()
	{
	}

	void DataWriterListener::Commit()
	{
	}
}

