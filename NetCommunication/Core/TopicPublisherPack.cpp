#include "TopicPublisherPack.h"
#include "../Core/ResourceManager.h"
#include "../Core/Framework.h"
#include "../Core/Publisher.h"
#include "../Core/Types.h"
#include "../Core/CoreCommon.h"
#include "../Core/Any.h"
#include "../Communication/Participator.h"
#include "../Core/Subscribe.h"
#include "../Core/Publisher.h"
#include "../Core/CommonTool.h"
namespace NetCom
{
	TopicPublisherPack::TopicPublisherPack()
	{
	}


	TopicPublisherPack::~TopicPublisherPack()
	{
	}

	//进行类型检查进行解包
	std::list<Participator*>  TopicPublisherPack::PaserPack(BYTE* data, int lenth)
	{
		this->SetData(data, lenth);
		std::list<Participator*> participatorList;
		int nodeId = ToolClass::GetSourceDevID(data);
		NodeBase* base = nullptr;
		if (!ResourceManager::GetInstance().GetNodeFromID(nodeId))
		{
			return participatorList;
		}
		ParticipatorType partType;
		EPackType type = (EPackType)ToolClass::GetPacketType(data);
		int participatorNumber = ToolClass::GetFixData<char>(m_data, ToolClass::GetHeaderSize());
		int begin = ToolClass::GetHeaderSize() + 1;
		if (type == TopicPublisher)
		{
			partType = DataWriter;
		}
		else if(type==TopicDiscribe)
		{
			partType = DataReader;
		}
		//按封包的步骤分解
		if (type == EPackType::TopicPublisher || type == EPackType::TopicDiscribe)
		{
			//如果节点不存在，则直接不分解
			base = ResourceManager::GetInstance().GetNodeFromID(nodeId);
			if (!base)
			{
				return participatorList;
			}
			for (int i = 0; i < participatorNumber; i++)
			{
				//结构化分解				
				unsigned short partID= ToolClass::GetFixData<UInt16>(m_data, begin);
				Participator* participator = NULL;
				if (type == EPackType::TopicPublisherList)
				{
					participator = new Publisher(partID);
				}
				else
				{
					participator = new Subscribe(partID);
				}
				participator->SetNodeID(nodeId);;
				participator->SetListenerType(partType);
				begin += 2;
				char topicNumber = ToolClass::GetFixData<char>(m_data, begin);
				begin += 1;
				for (int i = 0; i < topicNumber; ++i)
				{
					unsigned short topicID = ToolClass::GetFixData<UInt16>(m_data, begin);
					participator->GetTopicList().push_back(topicID);
					begin += 2;
				}
				//如果节点不存在，抛弃
				if (base)
				{
					participatorList.push_back(participator);
				}
				else
				{
					delete participator;
				}
				
			}
		}
		return participatorList;
	}

	int TopicPublisherPack::FillData(EPackType type)
	{
		//主题发布的数量和编号，
		ManagePack::FillData(0);
		std::vector<Participator*> publisherList;

		int begin = ToolClass::GetHeaderSize() + 1;
		 if (type == TopicPublisher)
		{
			publisherList = ResourceManager::GetInstance().GetLocalPublisherList();
		}
		else if(type == TopicDiscribe)
		{
			publisherList = ResourceManager::GetInstance().GetLocalSubscribList();
		}
		 ToolClass::SetPacketType(m_data,type);
		//遍历自己发布者列表
		//结构为：发布者数量，发布者1的ID，发布者1的主题数量，发布者1的主题ID
		//设置发布者个数
		ToolClass::SetFixData<char>(m_data, ToolClass::GetHeaderSize(), publisherList.size());
		//读取Id，循环遍历，写发布者的ID和主题个数
		if (type == TopicPublisher || type == EPackType::TopicDiscribe)
		{
			for (auto it = publisherList.begin(); it != publisherList.end(); ++it)
			{
				unsigned short participatorID = (*it)->GetParticipatorID();
				ToolClass::SetFixData<UInt16>(m_data, begin, participatorID);
				begin += 2;
				std::vector<UInt32> topics = (*it)->GetTopicList();
				char participatorTopicSize = topics.size();
				ToolClass::SetFixData<char>(m_data, begin, participatorTopicSize);
				begin += 1;
				//写主题
				for (int i = 0; i < participatorTopicSize; ++i)
				{
					unsigned short topicID = (*it)->GetTopicList().at(i);
					ToolClass::SetFixData<UInt16>(m_data, begin, topicID);
					begin += 2;
				}
			}
		}
		m_packageSize = begin;
		ToolClass::SetPacketSize(m_data, begin);
		return 0;
	}

	int TopicPublisherPack::GetPackageSize()
	{
		return m_packageSize;
	}

}

