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

	bool initDevice();	// 初始化设备
	int  sendFrame(VCI_CAN_OBJ *frameinfo);	// 发送一帧数据长度不能超过64位，使用空格隔开字节数据
	
	bool SendPack(char * data , int size);	// 拆包，使用标识符
private:

	
	bool connect();	// 连接设备
	
	bool startCAN();
	void confparm();	// 配置参数

public:
	int m_connect;
	bool m_bFlag;
	int nFilter_no;	// 过滤通道(0 表示Dual Filter  ， 1 Single Filter)
	int nMode_no;//(0 mormal , 1 readonly)
	int nSendFormat_no;	// 发送模式（0 mormal send , 1 single send , 2 send & recive , 3 single send % recive）
	int nType_no;	// 类型 (0 Extern Frame ,1 Standard Frame)
	int nFormat_no; // (0 Data Frame , 1 remote Frame)
	int m_sendFrameType;// 发送帧类型
	int m_index;
	int m_cannum;
	int m_devtype;

	std::string strAcc;
	std::string strMask;
	std::string szBtr0;
	std::string strBtr0;
	std::string strBtr1;	
	std::string strID;

	HANDLE m_hThread;	// 读取线程
	DWORD m_ThreadID;	// 线程ID
	CANMonitor * m_Monitor;
	UINT m_TransmitFlag;	// 传输标志
	ULONG byteTotal;
	//IpAdapterInfo m_IpInfo;	// 使用IP做节点标识
};

#endif