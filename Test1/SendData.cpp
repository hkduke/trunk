#include "SendData.h"

#include "../Sockets/StreamSocket.h"
#include "../Core/ResourceManager.h"
#include "../Communication/Participator.h"
#include "../Core/Any.h"
#include "../Communication/BlendModeNet.h"
#include "../Core/Framework.h"
#include "MessageTransePack.h"
#include "../Core/LogManager.h"
#include "../Core/FilePack.h"
#include "../Communication/FileTranseManager.h"

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
		MessageTransePack pack;

		while (1)
		{
			Thread::trySleep(100);
			while (!m_isStop)
			{
				std::ifstream infile;
				infile.open(m_file, ifstream::in|ifstream::binary);
				infile.seekg(0, ifstream::end);
				int size = infile.tellg();
				if (size == -1)return;
				infile.seekg(0);
				char *buf = new char[size];
				infile.read(buf, size);

				if (m_file.empty()) {
					LogManager::GetInstance().WriteMessage("没有给文件");
					return;
				}

				m_isStop = true;
				Thread::trySleep(200);
				//pack.FillData(vector,0);
				//if (!m_ipset)continue;

				/////////////////////////////
				std::vector<FilePack*> vecpack = FilePack::GetFilePackages(buf, size, "test.dat", 0);
				/*FileTranseManager* file= ResourceManager::GetInstance().GetFileTranseManager();
				file->SetFileNodeId(1);


				MapOfstream &map = file->GetMapOfstream(1);*/
				
				int stdi = 0;
 				for (int i = 0; i < vecpack.size(); i++)
 				{
 					//Thread::trySleep(200);
 					FilePack* pack = vecpack[i];
 					void  * data = pack->GetData();
 					//std::cout << data << std::endl;
 					int len = pack->GetLenth();
 					//std::cout << ToolClass::GetPacketSize(data) << std::endl;
					
 					Framework::GetInstance().GetTransportStratagy()->Send((UINT8*)data, len, TransactionType_File);
					//FilePack pack1;
					//pack1.ParseFile(data);
					//file->PushFrameObj(pack1.GetData(), pack1.GetLenth(), pack1.GetFileSerial(data), map);
					//stdi += pack1.GetLenth();
					//LogManager::GetInstance().WriteMessage("SendData::run 发送的包序号为%d",(int)pack->GetFileSerial(data));
 				}

				//file->WirteFile(1);
				//std::string msg("helloworld");
				//for (int i = 0 ;i <20;i++)
				//{
				//	Framework::GetInstance().GetTransportStratagy()->Send(pack.Data(), 1024);
				//}
				///////////////////////////////////////////////////////////////
				//如果检查到监视的

				/*
				for (TCPTransport::IpaddressSet::iterator iter = m_ipset->begin(); iter != m_ipset->end(); iter++)
				{
					std::vector<Participator*> partLidt = ResourceManager::GetInstance().m_localRelateSubscrib;
					for (auto it = partLidt.begin(); it != partLidt.end(); ++it)
					{
						if (ResourceManager::GetInstance().IsNodeExit((*it)->GetNodeID()))
						{
							if (ResourceManager::GetInstance().GetNodeFromID((*it)->GetNodeID())->GetNodeIpString() == iter->first
								&&ResourceManager::GetInstance().IsLocalRelateSubscribTopicExist
								((*it)->GetParticipatorID(), AnyCast<int>(vector->at(0))))
							{

								//iter->second.stream->sendBytes(pack.Data(), 1024);
								for (int i = 0 ; i < vecpack.size();i++)
								{
									Thread::trySleep(200);
									FilePack* pack = vecpack[i];
									void  * data = pack->GetData();
									std::cout << data << std::endl;
									int len = pack->GetLenth();
									std::cout << ToolClass::GetPacketSize(data) << std::endl;
									iter->second.stream->sendBytes(data, len);

									//Framework::GetInstance().GetTransportStratagy()->Send((UINT8*)data, len);
								}
								LogManager::GetInstance().WriteMessage("发送数据完成");
							}
						}


					}

				}
				*/

			}
			if (m_isStop)
			{
				BlendModeNet * ptr = Framework::GetInstance().GetBlendModeNet();
				if (ptr)
				{
					ptr->Send(pack.Data(), 1024);
				}
			}


		}
	}
}


