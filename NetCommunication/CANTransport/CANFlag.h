
#ifndef _H_CANFLAG_
#define _H_CANFLAG_
#include "defDataTypes.h"
#include "ControlCAN.h"
class CANFlag
{
private:
	CANFlag(void);
	
public:
	~CANFlag(void);
	static CANFlag * instace();
	enum eSendFlag
	{
		SUCCEED,// ���ͳɹ�
		FIALD	// ����ʧ��
	};
	static CANFlag *m_instace;
	VCI_ERR_INFO & getErrorInfo();

	VCI_ERR_INFO m_errorInfo;
};

#endif