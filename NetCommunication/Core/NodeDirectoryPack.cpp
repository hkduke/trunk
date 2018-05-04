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
			//在内存中的分布顺序为：
			//节点ID四个，节点网络类型1，节点IP6个，
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

	//填充数据，把链表所有内容加入data
	int NodeDirectoryPack::FillData()
	{
		//节点ID四个，节点网络类型1，节点IP6个，
		ManagePack::FillData(0);
		auto tempList=ResourceManager::GetInstance().GetNodeList();
		int size = 8 * tempList.size();
		std::vector<BYTE> tempByte(size);
		int packheadSize = ToolClass::GetHeaderSize();
		int begin = packheadSize + 2+8;
		ToolClass::SetFixData<UInt16>(m_data, packheadSize + 8, UInt16(tempList.size()));
		ToolClass::SetPacketType(m_data,NodeDirectory);
		ToolClass::SetPacketSize(m_data,GetPackTotalSize());
	
		//检测发送时，节点的存活时间，保存为最小结点时间，只有最小结点做此操作，方便比较后来的包的时间
		//包头以下布局：发送生存时间，发送的节点数量，发送的第一个节点ID，节点类型，节点的IP
		Timestamp::TimeDiff elape = NodeDiscover::GetInstance().m_createTime.elapsed();
		ResourceManager::GetInstance().m_smallestAliveTime = elape;
		ResourceManager::GetInstance().lastSendDirTime = elape;
		ResourceManager::GetInstance().m_smallestLastSend = Timestamp();
		//设置生存时间
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
					std::cout << "第" << i << "个字段为：" << vectors.at(i)
						<< "，类型：" << tempVar.type().name() << ",值：" << AnyCast<int>(tempVar) << std::endl;
				}
				else if (varType == "double")
				{
					std::cout << "第" << i << "个字段为：" << vectors.at(i)
						<< "，类型：" << tempVar.type().name() << ",值：" << AnyCast<double>(tempVar) << std::endl;
				}
				else if (varType == "float")
				{
					std::cout << "第" << i << "个字段为：" << vectors.at(i)
						<< "，类型：" << tempVar.type().name() << ",值：" << AnyCast<float>(tempVar) << std::endl;
				}
				else
				{
					continue;
				}
			}

	}*/

}


