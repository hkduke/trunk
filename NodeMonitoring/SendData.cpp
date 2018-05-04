#include "SendData.h"

#include "../Sockets/StreamSocket.h"
#include "../Core/ResourceManager.h"
#include "../Communication/Participator.h"
#include "../Core/Any.h"
#include "../Communication/BlendModeNet.h"
#include "../Core/Framework.h"

namespace NetCom
{
	SendData::SendData(std::vector<Any>* data) :m_isStop(true), vector(data), m_ipset(nullptr)
	{
	}
	SendData::~SendData()
	{
	}

	void NetCom::SendData::run()
	{
		//MessageTransePack pack;

		while (1)
		{
			Thread::trySleep(20);
			while (!m_isStop)
			{
				//pack.FillData(vector,"");
				//如果检查到监视的
				if (!m_ipset)continue;
				for (TCPTransport::IpaddressSet::iterator iter = m_ipset->begin(); iter != m_ipset->end(); iter++)
				{
					std::vector<Participator*> partLidt = ResourceManager::GetInstance().m_localRelateSubscrib;
					for (auto it = partLidt.begin(); it != partLidt.end(); ++it)
					{
						if ((*it)->GetNode()->GetNodeIpString() == iter->first
							&&ResourceManager::GetInstance().IsLocalRelateSubscribTopicExist
							((*it)->GetParticipatorID(), AnyCast<int>(vector->at(0))))
						{
							//iter->second.stream->sendBytes(pack.Data(), 1024);
							//std::cout << "发送完成" << std::endl;
						}

					}

				}

			}
			if (m_isStop)
			{
				BlendModeNet * ptr = Framework::GetInstance().GetBlendModeNet();
				if (ptr)
				{
					//ptr->Send(pack.Data(), 1024);
				}
			}

			m_isStop = true;

		}
	}
}


