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

	//�������ͼ����н��
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
		//������Ĳ���ֽ�
		if (type == EPackType::TopicPublisher || type == EPackType::TopicDiscribe)
		{
			//����ڵ㲻���ڣ���ֱ�Ӳ��ֽ�
			base = ResourceManager::GetInstance().GetNodeFromID(nodeId);
			if (!base)
			{
				return participatorList;
			}
			for (int i = 0; i < participatorNumber; i++)
			{
				//�ṹ���ֽ�				
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
				//����ڵ㲻���ڣ�����
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
		//���ⷢ���������ͱ�ţ�
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
		//�����Լ��������б�
		//�ṹΪ��������������������1��ID��������1������������������1������ID
		//���÷����߸���
		ToolClass::SetFixData<char>(m_data, ToolClass::GetHeaderSize(), publisherList.size());
		//��ȡId��ѭ��������д�����ߵ�ID���������
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
				//д����
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

