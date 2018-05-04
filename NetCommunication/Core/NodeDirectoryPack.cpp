#include "NodeDirectoryPack.h"
#include "../core/NodeBase.h"
#include "../Core/ResourceManager.h"
#include "../Core/Types.h"
#include "../NodeDiscover/NodeDiscover.h"
#include "../Core/Any.h"
#include "../Core/CommonTool.h"
#include "../Core/CommonTool.h"
namespace NetCom
{
	NodeDirectoryPack::NodeDirectoryPack()
	{
	}


	NodeDirectoryPack::~NodeDirectoryPack()
	{
	}

	std::list<NodeBase*>  NodeDirectoryPack::PaserPack(BYTE* data,int lenth)
	{
		this->SetData(data, lenth);
		std::list<NodeBase*> nodeList;
	
		int nodeNumber = ToolClass::GetFixData<UInt16>(data, ToolClass::GetHeaderSize() +8);
		int begin = ToolClass::GetHeaderSize()+8+2;
		for (int i = 0; i < nodeNumber; i++)
		{
			//���ڴ��еķֲ�˳��Ϊ��
			//�ڵ�ID�ĸ����ڵ���������1���ڵ�IP6����
			NodeBase* base = new NodeBase;
			base->SetNodeID(ToolClass::GetFixData<UInt32>(data,begin));
			begin += 4;
			base->SetNetStyle((DeviceAddressType)ToolClass::GetFixData<char>(data, begin));
			begin += 1;
			base->SetNodeAddrIP(ToolClass::GetFixData<UInt32>(data, begin));
			begin += 4;
			nodeList.push_back(base);
		}
		return nodeList;
	}

	UINT NodeDirectoryPack::GetPackTotalSize()
	{
		return ToolClass::GetHeaderSize()+2+8+ ResourceManager::GetInstance().GetNodeList().size()*9;
	}

	//������ݣ��������������ݼ���data
	int NodeDirectoryPack::FillData()
	{
		//�ڵ�ID�ĸ����ڵ���������1���ڵ�IP6����
		ManagePack::FillData(0);
		auto tempList=ResourceManager::GetInstance().GetNodeList();
		int size = 8 * tempList.size();
		std::vector<BYTE> tempByte(size);
		int packheadSize = ToolClass::GetHeaderSize();
		int begin = packheadSize + 2+8;
		ToolClass::SetFixData<UInt16>(m_data, packheadSize + 8, UInt16(tempList.size()));
		ToolClass::SetPacketType(m_data,NodeDirectory);
		ToolClass::SetPacketSize(m_data,GetPackTotalSize());
	
		//��ⷢ��ʱ���ڵ�Ĵ��ʱ�䣬����Ϊ��С���ʱ�䣬ֻ����С������˲���������ȽϺ����İ���ʱ��
		//��ͷ���²��֣���������ʱ�䣬���͵Ľڵ����������͵ĵ�һ���ڵ�ID���ڵ����ͣ��ڵ��IP
		Timestamp::TimeDiff elape = NodeDiscover::GetInstance().m_createTime.elapsed();
		ResourceManager::GetInstance().m_smallestAliveTime = elape;
		ResourceManager::GetInstance().lastSendDirTime = elape;
		ResourceManager::GetInstance().m_smallestLastSend = Timestamp();
		//��������ʱ��
		ToolClass::SetFixData<UInt64>(m_data, ToolClass::GetHeaderSize(), UInt64(elape));

		for (auto it = tempList.begin(); it != tempList.end(); it++)
		{
			UInt32 nodeId = (*it)->GetNodeID();
			ToolClass::SetFixData<UInt32>(m_data, begin, UInt32(nodeId));
			begin += 4;
			UInt32 nodeStyle = (UInt32)(*it)->GetNetStyle();
			ToolClass::SetFixData<char>(m_data, begin, char(nodeStyle));
			begin += 1;
			UInt32 nodeIP = (UInt32)(*it)->GetNodeAddrIP();
			ToolClass::SetFixData<UInt32>(m_data, begin, UInt32(nodeIP));
			begin += 4;
		}
		ToolClass::SetPacketSize(m_data, begin);
		return 0;
	}

	/*void NodeDirectoryPack::PrintData()
	{
			std::vector<std::string> vectors = this->m_p.GetFieldList();
			for (int i = 0; i < vectors.size(); i++)
			{
				Any tempVar = GetPropValue(vectors.at(i));
				const char* varType1 = tempVar.type().name();
				std::string varType = varType1;
				if (varType == "int")
				{
					std::cout << "��" << i << "���ֶ�Ϊ��" << vectors.at(i)
						<< "�����ͣ�" << tempVar.type().name() << ",ֵ��" << AnyCast<int>(tempVar) << std::endl;
				}
				else if (varType == "double")
				{
					std::cout << "��" << i << "���ֶ�Ϊ��" << vectors.at(i)
						<< "�����ͣ�" << tempVar.type().name() << ",ֵ��" << AnyCast<double>(tempVar) << std::endl;
				}
				else if (varType == "float")
				{
					std::cout << "��" << i << "���ֶ�Ϊ��" << vectors.at(i)
						<< "�����ͣ�" << tempVar.type().name() << ",ֵ��" << AnyCast<float>(tempVar) << std::endl;
				}
				else
				{
					continue;
				}
			}

	}*/

}


