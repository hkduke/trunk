#include "DataLinkMap.h"
#include <assert.h>

namespace NetCom
{
	DataLinkMap::DataLinkMap()
	{
	}


	DataLinkMap::~DataLinkMap()
	{
	}

	void DataLinkMap::Insert(MAPTYPE k, DataLink* v)
	{
		assert(v);
		v->SetSendStrategy(m_sendStrategy);
		m_DataLinkMap.insert(std::pair<int, DataLink*>(k, v));
	}

	bool DataLinkMap::Bind(MAPTYPE  k,DataLink* v)
	{
		assert(v);
		v->SetSendStrategy(m_sendStrategy);
		m_DataLinkMap.insert(std::pair<MAPTYPE, DataLink*>(k, v));
		return true;
	}

	void DataLinkMap::SendStart(DataLinkSet * linkSet)
	{
		assert(linkSet);
		for (DataLinkSet::iterator iterMap = linkSet->begin(); iterMap!= linkSet->end(); linkSet++)
		{
			Bind(iterMap->first , iterMap->second);
			//iterMap->second->SetStart();
			iterMap->second->Send(m_dataList);
		}

	}

	void DataLinkMap::SetDataSampleElementList(DataSampleElementList * ptr)
	{
		m_dataList = ptr;
	}

	NetCom::DataSampleElementList * DataLinkMap::GetDataSampleElementList()
	{
		return m_dataList;
	}

	DataLinkMap::DataLinkSet & DataLinkMap::GetDataLinkSet()
	{
		return m_DataLinkMap;
	}

}


