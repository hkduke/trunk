#pragma once

#include <map>
#include "../Core/Export.h"
#include "DataLink.h"
#include "CoreCommon.h"
#include <string.h>
#include "DataSampleElementList.h"

#include "Types.h"

class DataLink;

// 生成链路数据集合
namespace NetCom
{
	class TransportSendStrategy;
	
	class NETCOMMUNICATION_EXPORT DataLinkMap
	{
	public:
		typedef UInt32 MAPTYPE;
		typedef std::map<MAPTYPE, DataLink*> DataLinkSet;
	public:
		DataLinkMap();
		~DataLinkMap();
		void Insert(MAPTYPE k, DataLink* v);
		bool Bind(MAPTYPE k, DataLink* v);
		void SendStart(DataLinkSet * linkSet);
		void SetDataSampleElementList(DataSampleElementList * ptr);

		DataSampleElementList  * GetDataSampleElementList();
		DataLinkSet & GetDataLinkSet();
	private:

		DataLinkSet m_DataLinkMap;
		DataSampleElementList * m_dataList;
		TransportSendStrategy * m_sendStrategy;
	};

}

