#pragma once
#include "../Core/eventhandle.h"

#include "../Core/ResourceManager.h"
// #include "Poco/Thread.h"
// #include "Poco/Runnable.h"
// 节点加入报文处理事件
#include <iostream>
#include <vector>
namespace NetCom
{
	class NodeBase;
	class NodeJoinHandle :
		public EventHandle /*,public Poco::Runnable*/
	{
	public:
		NodeJoinHandle();
		~NodeJoinHandle();
		//自己为新节点，准备加入系统
		virtual int HandleEnter(void *ptr);

		// 当有节点进行加入 (是否不通过节点方式默认公布者 ， 也就是一个节点可以有多个发布者 或是订阅者 （待考虑）)
		virtual int Handle(void *ptr);

		virtual int HandleClose(void *ptr);


	protected:

		virtual void run();

	private:

	

	};
}


