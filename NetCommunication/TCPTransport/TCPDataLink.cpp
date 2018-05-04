#include "TCPDataLink.h"
#include<assert.h>
#include "../Core/CommonTool.h"
#include "../Core/ResourceManager.h"
#include "../Communication/Participator.h"
#include "../Core/Timestamp.h"
namespace NetCom
{


	TCPDataLink::~TCPDataLink()
	{
	}

	void TCPDataLink::Send(DataSampleElement* element, bool relink /*= true*/)
	{
		//m_sendStreamSocket.sendBytes()
		//Timestamp chageNow;
		//static Timestamp lastTime;
		//std::cout << "TCPDataLink::Send::"<<int(chageNow- lastTime ) << std::endl;
		//Timestamp timeRoll;
		if (!element)
			return;
		assert(element);
		//void* da = element->GetBlockPtr();
		int paceType =ToolClass::GetPacketType(element->GetBlockPtr()); 
		int targetID = ToolClass::GetSourceDevID(element->GetBlockPtr());
		
		if (paceType > 10100 && paceType < 11201)
		{
			std::vector<Participator*>partList= ResourceManager::GetInstance().GetRelateSubscrib();
			for (auto it = partList.begin(); it != partList.end(); ++it)
			{
				//发送的结点号目标节点号，并且主题号也存在，则发送
				if (targetID == (*it)->GetNodeID()||
					ResourceManager::GetInstance().IsLocalRelateSubscribTopicExist((*it)->GetParticipatorID(), paceType))
				{
					m_sendStreamSocket.sendBytes(element->GetBlockPtr(), element->GetBlockSize());
					break;
				}
			}
		}
		else
		{
						
			m_sendStreamSocket.sendBytes(element->GetBlockPtr(), element->GetBlockSize());
	//std::cout <<__FUNCTION__<<"::::" <<(int)timeRoll.elapsed() << std::endl;
		}

		//lastTime = Timestamp();

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

