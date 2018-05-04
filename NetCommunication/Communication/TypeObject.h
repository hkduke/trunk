#pragma once
#include "../Core/Export.h"
namespace NetCom
{
class NETCOMMUNICATION_EXPORT TypeObject
{
public:
	TypeObject();
	~TypeObject();

	//virtual void SetAttribute(char* convert);

	virtual TypeObject *GetAttribute(char * convert);
	char * m_value;
};
}


