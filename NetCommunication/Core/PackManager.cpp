#include "PackManager.h"
#include "../Core/Framework.h"
#include "../Core/CommonTool.h"
#include "../Core/ResourceManager.h"
#include "../Core/LogManager.h"
namespace NetCom
{
	const std::string messageID = "报文序号";

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
		//获取报文序号
		UInt16 topicID = ToolClass::GetFixData<UInt16>(ptr,3);//设置数据
		
		//填冲数据
		std::vector<unsigned char> dataVect((char*)ptr, (char*)ptr + lenth);
		m_currentPackage.setData(dataVect);
		//获取包类型
		m_currentPackage = xmlManager.at(m_IDMap.at(topicID));
		//获取所有字段
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
		//m_currentPackage.setPackage("数据指令报文");
			std::vector<std::string> vecstr = m_currentPackage.getAllFieldName();

			for (int i = 0; i < vecstr.size(); i++)
			{
				if (m_currentPackage.getType(vecstr[i]) == "int32")
				{
					m_currentPackage.setValue(vecstr[i], rand());
				}
			}
			
			SetFiledValue("报文信息标识", (UInt8)EPackType::MessageTranse);
			SetFiledValue("信源设备标识", (UInt32)ResourceManager::GetInstance().
				GetCurrentNode()->GetNodeID());
			SetFiledValue("报文序号", UInt16(topicID));
			int i =AnyCast<UInt16>( GetFiledValue("报文序号"));
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
		//package.setPackage("数据指令报文");
		//
		//int id = package.getID();
		//m_IDMap[id] = "数据指令报文";
		//xmlManager["数据指令报文"] = package;

		//遍历全包名字，把报文按名称加入xmlManager中;
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

