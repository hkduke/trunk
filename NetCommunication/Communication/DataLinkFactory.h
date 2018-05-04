#pragma once
#include "DataLink.h"
#include "Export.h"
namespace NetCom
{
	class NETCOMMUNICATION_EXPORT DataLinkFactory
	{
	public:
		DataLinkFactory();
		~DataLinkFactory();


		virtual  DataLink* ConstructionLink(NodeBase * ptr);
	};
}


