#include "TransportSendStrategy.h"
#include <string>
#include <iostream>
#include <assert.h>
#include "../Communication/FileSendQueue.h"


namespace NetCom
{
	TransportSendStrategy::TransportSendStrategy():m_pTransport(nullptr)
	{
		InitStrategy();
		
	}


	TransportSendStrategy::TransportSendStrategy(NetType type)
	{
		InitStrategy(type);
	}

	TransportSendStrategy::~TransportSendStrategy()
	{
	}

	void TransportSendStrategy::InitStrategy()
	{
		m_pTransport = new Transport;
		m_pTransport->Init();
	}

	void TransportSendStrategy::InitStrategy(NetType type)
	{
		
		if(type == EPublisher)
		{

		}
		else
		{

		}

	}

	int TransportSendStrategy::Send(UInt32 topic, UInt8 * data, UInt32 size, TransactionType type)
	{

		//Timestamp currentTime;
		m_pTransport->Send(topic,data, size, type);

		//std::cout << __FUNCTION__ << "::::" << (int)currentTime.elapsed() << std::endl;
		return 1;
	}

	int TransportSendStrategy::StartSend()
	{
		//m_pTransport->run();
// 		Thread _thread;
// 		//SendQueue sq;
// 		RunnableAdapter<SendQueue> runnable(*m_pSendQueue, &SendQueue::ProcessQueue);
//		_thread.start(runnable);
//		_thread.join();
		return 1;
	}


	std::string TransportSendStrategy::name() const
	{
		return "";
	}

	void TransportSendStrategy::Run()
	{

	}

	NetCom::DataLinkMap * TransportSendStrategy::GetDataLinkMap()
	{
		return m_pTransport->GetDataLinkMap();
	}

	NetCom::Transport **TransportSendStrategy::GetTransport()
	{
		return &m_pTransport;
	}

}

