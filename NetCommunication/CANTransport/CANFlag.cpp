#include "CANFlag.h"

CANFlag *CANFlag::m_instace = 0;
CANFlag::CANFlag(void)
{
}


CANFlag::~CANFlag(void)
{
}

VCI_ERR_INFO & CANFlag::getErrorInfo()
{
	return m_errorInfo;
}

CANFlag * CANFlag::instace()
{
	if(!m_instace)
	{
		m_instace = new CANFlag;
	}
	return m_instace;
}
