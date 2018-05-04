#include "IPNode.h"
namespace NetCom
{
	IPNode::IPNode(void):
NodeBase()
{
	m_Address.SetType(IP_V4_ADDR);
	m_Address.SetAddrSize(4);
}


	IPNode::~IPNode(void)
	{

	}
}


