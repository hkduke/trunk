#include "ACKReadHandle.h"
#include "../Core/ACKPack.h"
namespace NetCom
{
	ACKReadHandle::ACKReadHandle()
	{
	}


	ACKReadHandle::~ACKReadHandle()
	{
	}

	int ACKReadHandle::HandleEnter(void *ptr)
	{
		//读取响应包，并分解包中内容ptr
		ACKPack pack;
		pack.FillData(0);

		//根据包的类型选择确认包中是否是重发，响应等
		/*
			读包后，要求重发，调用缓冲区的包重发该包;
			读包后，要求回应，确认正确或错误回应
			读包后，要求对方回应，去一级。
		
		*/

		if (1)
		{

		}

		return 0;
	}

	
	int ACKReadHandle::Handle(void *ptr)
	{
		return 0;
	}

	int ACKReadHandle::HandleClose(void *ptr)
	{
		return 0;
	}

}

