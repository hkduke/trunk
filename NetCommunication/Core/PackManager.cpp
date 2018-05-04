#include "PackManager.h"
#include "../Core/Framework.h"
#include "../Core/CommonTool.h"
#include "../Core/ResourceManager.h"
#include "../Core/LogManager.h"
namespace NetCom
{
	const std::string messageID = "�������";

	std::map<std::string, BasePackage> PackManager::xmlManager;

	std::map<int, std::string> PackManager::m_IDMap;

	PackManager::PackManager()
	{
	}
	PackManager::~PackManager()
	{
	}

	void PackManager::Parse(void* ptr,int lenth)
	{
		//��ȡ�������
		UInt16 topicID = ToolClass::GetFixData<UInt16>(ptr,3);//��������
		
		//�������
		std::vector<unsigned char> dataVect((char*)ptr, (char*)ptr + lenth);
		m_currentPackage.setData(dataVect);
		//��ȡ������
		m_currentPackage = xmlManager.at(m_IDMap.at(topicID));
		//��ȡ�����ֶ�
		std::vector<std::string> vecstr = m_currentPackage.getAllFieldName();

		LogManager::GetInstance().WriteMessage("PackManager::Parse ParsePackID:%d\n", (int)m_currentPackage.getID());
		for ( int i = 0 ; i < vecstr.size() ; i++ )
		{
			NetCom::Any value = m_currentPackage.getValue(vecstr[i]);
			LogManager::GetInstance().WriteMessage("PackManager::Parse vecstr[%d]:%d\n",i ,NetCom::AnyCast<UInt16>(value));
		}


	}

	void PackManager::SetFiledValue(std::string filedName, Any value)
	{
			m_currentPackage.setValue(filedName, value);
	}

	Any PackManager::GetFiledValue(std::string filedName)
	{
		return m_currentPackage.getValue(filedName);
	}

	void PackManager::Fill(UInt32 topicID)
	{
		m_currentPackage = xmlManager.at(m_IDMap.at(topicID));
		//m_currentPackage.setPackage("����ָ���");
			std::vector<std::string> vecstr = m_currentPackage.getAllFieldName();

			for (int i = 0; i < vecstr.size(); i++)
			{
				if (m_currentPackage.getType(vecstr[i]) == "int32")
				{
					m_currentPackage.setValue(vecstr[i], rand());
				}
			}
			
			SetFiledValue("������Ϣ��ʶ", (UInt8)EPackType::MessageTranse);
			SetFiledValue("��Դ�豸��ʶ", (UInt32)ResourceManager::GetInstance().
				GetCurrentNode()->GetNodeID());
			SetFiledValue("�������", UInt16(topicID));
			int i =AnyCast<UInt16>( GetFiledValue("�������"));
			std::vector<unsigned char > temp= m_currentPackage.allData();
			
	}


	

	void * PackManager::GetData()
	{
		return m_currentPackage.allData().data();
	}

	void PackManager::Init()
	{
		BasePackage package;
		std::string strType = Framework::GetInstance().ConfigString("XmlFile");
		package.readXml(strType);	
		//package.setPackage("����ָ���");
		//
		//int id = package.getID();
		//m_IDMap[id] = "����ָ���";
		//xmlManager["����ָ���"] = package;

		//����ȫ�����֣��ѱ��İ����Ƽ���xmlManager��;
		std::vector<std::string> allPackageName = package.getAllPackageName();
		for (size_t i = 0; i < allPackageName.size(); i++)
		{
			package.setPackage(allPackageName.at(i));
			int packId = package.getID();
			package.setPackage(allPackageName.at(i));
			m_IDMap[package.getID()] = allPackageName.at(i);
			xmlManager[allPackageName.at(i)] = package;
		}	
		
	}

}

