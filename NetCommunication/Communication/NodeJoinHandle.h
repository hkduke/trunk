#pragma once
#include "../Core/eventhandle.h"

#include "../Core/ResourceManager.h"
// #include "Poco/Thread.h"
// #include "Poco/Runnable.h"
// �ڵ���뱨�Ĵ����¼�
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
		//�Լ�Ϊ�½ڵ㣬׼������ϵͳ
		virtual int HandleEnter(void *ptr);

		// ���нڵ���м��� (�Ƿ�ͨ���ڵ㷽ʽĬ�Ϲ����� �� Ҳ����һ���ڵ�����ж�������� ���Ƕ����� �������ǣ�)
		virtual int Handle(void *ptr);

		virtual int HandleClose(void *ptr);


	protected:

		virtual void run();

	private:

	

	};
}


