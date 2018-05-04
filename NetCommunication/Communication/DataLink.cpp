#include "DataLink.h"
#include <assert.h>
#include "../Communication/TransportSendStrategy.h"
#include "Framework.h"
namespace NetCom
{
	DataLink::DataLink():m_linkInfo(None), m_isAckSend(false)
	{
		m_currentres.SetResId(1);
	}


	DataLink::~DataLink()
	{
	}

	void DataLink::SetStart()
	{

	}

	void DataLink::Send(DataSampleElementList * element, bool relink)
	{
		assert(element);
		while(!element->Empty())
		{
			DataSampleElement * ele = element->Front();
			size_t blocksize = ele->GetBlockSize();
			UInt8 * data = static_cast<BYTE*>(ele->GetBlockPtr());
			element->Pop();
			Timestamp currentTime;
			
		
			Framework::GetInstance().GetTransportStratagy()->Send(111,data, blocksize);
			
			std::cout << __FUNCTION__ << "::::" << (int)currentTime.elapsed() << std::endl;


			Framework::GetInstance().GetTransportStratagy()->Send(111,data, blocksize);
// 			delete ele;
// 			ele = nullptr;
			//int sendflag = m_sendStrategy->Send(data, blocksize);
			if (element->Size() <= 0)
			{
				std::cout << "消费完成" << std::endl;
			}
		}
	}

	void DataLink::Send(DataSampleElement* element, bool relink /*= false*/)
	{

	}

	void DataLink::SetSendStrategy(TransportSendStrategy * strategy)
	{
		m_sendStrategy = strategy;
	}

	void DataLink::SetDataSampleElementList(DataSampleElementList* ptr)
	{
		m_dataSampleList = ptr;
	}

	void DataLink::SetTransport(Transport * ptr)
	{
		m_pTransport = ptr;
	}

	void DataLink::SetDataControlInfo(DataControlInfo info)
	{
		m_linkInfo = info;
	}

	DataLink::DataControlInfo DataLink::GetDataControlInfo()
	{
		return m_linkInfo;
	}

	void DataLink::SetDscNodeId(UInt32 id)
	{
		m_dscNodeId = id;
	}

	bool DataLink::DecideTransport()
	{
		return false;
	}

	void DataLink::SetAckSendFlag(bool isSend)
	{
		m_isAckSend = isSend;
	}

	void DataLink::Bind()
	{

	}

}

