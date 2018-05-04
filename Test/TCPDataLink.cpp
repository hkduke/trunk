#include "TCPDataLink.h"
#include<assert.h>

namespace NetCom
{


	TCPDataLink::~TCPDataLink()
	{
	}

	void TCPDataLink::Send(DataSampleElement* element, bool relink /*= true*/)
	{
		//m_sendStreamSocket.sendBytes()
		assert(element);
		m_sendStreamSocket.sendBytes(element->GetBlockPtr(), element->GetBlockSize());
// 		DataSampleElementList::DataSampleQueque &dq = element->GetDataSampleQueque();
// 		DataSampleElementList::DataSampleQueque tdq(dq);
// 		while (!tdq.empty())
// 		{
// 			DataSampleElement * de = tdq.front();
// 			m_sendStreamSocket.sendBytes(de->GetBlockPtr(), de->GetBlockSize());
// 			tdq.pop();
// 		}
	}

// 	void TCPDataLink::Send(DataSampleElementList * element, bool relink)
// 	{
// 		assert(element);
// 		for (int i = 0 ; i< element->Size();i++)
// 		{
// 			DataSampleElement * ele = element->Front();
// 			m_tcpTransport->Send((UInt8*)(ele->GetBlockPtr()), ele->GetBlockSize());
// 		}
// 	}

// 	void TCPDataLink::SetSendStrategy(TransportSendStrategy * strategy)
// 	{
// 
// 	}


	void TCPDataLink::MakeConnect()
	{

	}

	void TCPDataLink::Bind()
	{
		m_tcpTransport = new TCPTransport;
		m_tcpTransport->Init();

	}

}

