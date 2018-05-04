#ifndef _H_CAN_H
#define _H_CAN_H

// #include <intsafe.h>
// #include <winnt.h>
#include "defDataTypes.h"
#include "ControlCAN.h"
#include <string>
#include <list>
#include <vector>

class CANMonitor;
class CAN
{
public:
	CAN(void);
	~CAN(void);

	bool initDevice();	// ��ʼ���豸
	int  sendFrame(VCI_CAN_OBJ *frameinfo);	// ����һ֡���ݳ��Ȳ��ܳ���64λ��ʹ�ÿո�����ֽ�����
	
	bool SendPack(char * data , int size);	// �����ʹ�ñ�ʶ��
private:

	
	bool connect();	// �����豸
	
	bool startCAN();
	void confparm();	// ���ò���

public:
	int m_connect;
	bool m_bFlag;
	int nFilter_no;	// ����ͨ��(0 ��ʾDual Filter  �� 1 Single Filter)
	int nMode_no;//(0 mormal , 1 readonly)
	int nSendFormat_no;	// ����ģʽ��0 mormal send , 1 single send , 2 send & recive , 3 single send % recive��
	int nType_no;	// ���� (0 Extern Frame ,1 Standard Frame)
	int nFormat_no; // (0 Data Frame , 1 remote Frame)
	int m_sendFrameType;// ����֡����
	int m_index;
	int m_cannum;
	int m_devtype;

	std::string strAcc;
	std::string strMask;
	std::string szBtr0;
	std::string strBtr0;
	std::string strBtr1;	
	std::string strID;

	HANDLE m_hThread;	// ��ȡ�߳�
	DWORD m_ThreadID;	// �߳�ID
	CANMonitor * m_Monitor;
	UINT m_TransmitFlag;	// �����־
	ULONG byteTotal;
	//IpAdapterInfo m_IpInfo;	// ʹ��IP���ڵ��ʶ
};

#endif