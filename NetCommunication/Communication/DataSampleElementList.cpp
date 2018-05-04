#include "DataSampleElementList.h"
#include"../Core/Timestamp.h"
#include <iostream>
namespace NetCom
{
	DataSampleElementList::DataSampleElementList():m_Id(0)
	{
	}


	DataSampleElementList::~DataSampleElementList()
	{
	}

	void DataSampleElementList::Pop()
	{
		m_lock.lock();
		//m_dataList.pop();
		if (!m_dataList.empty())
		{
			m_dataList.erase(m_dataList.begin());
		}
		m_lock.unlock();
	}

	DataSampleElement * DataSampleElementList::Front()
	{
		return m_dataList.front();
	}

	void DataSampleElementList::Push(DataSampleElement* ele)
	{
		//Timestamp currentTime;

		m_lock.lock();
		ele->SetResourceId(++m_Id);
		m_dataList.push_back(ele);
		m_lock.unlock();		
		//std::cout << __FUNCTION__ << "::::" << (int)currentTime.elapsed() << std::endl;
	}

}


