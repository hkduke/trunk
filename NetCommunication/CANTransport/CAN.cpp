#include "CAN.h"
#include <stdio.h>
#include <Windows.h>
#include "CANFlag.h"

#include<assert.h>
#include "Utilities.h"
//extern CANAPP m_app;
#include "../Core/CoreComponent.h"


using namespace NetCom;
CAN::CAN(void)
{
}


CAN::~CAN(void)
{
}


bool CAN::initDevice()
{
	confparm();
	connect();
	return startCAN();
	//ReceiveThread();
}

bool CAN::connect()
{
	if( m_bFlag )
	{
		m_bFlag = false;
		//获取变量值
		CoreComponent::GetInstance().WriteLogMsg("index_no =%d"+ m_index );
		CoreComponent::GetInstance().WriteLogMsg("CAN_no =%d"+m_cannum );
		CoreComponent::GetInstance().WriteLogMsg("Filter_no =%d"+nFilter_no );
		CoreComponent::GetInstance().WriteLogMsg("Mode_no =%d"+nMode_no );
		CoreComponent::GetInstance().WriteLogMsg("SendFormat_no =%d"+nSendFormat_no );
		CoreComponent::GetInstance().WriteLogMsg("Type_no =%d"+nType_no );
		CoreComponent::GetInstance().WriteLogMsg("Format_no =%d",nFormat_no );
		CoreComponent::GetInstance().WriteLogMsg("Acc =%s"+strAcc);
		CoreComponent::GetInstance().WriteLogMsg("Mask =%s\n"+strMask );
		CoreComponent::GetInstance().WriteLogMsg("Btr0 =%s\n"+strBtr0 );
		CoreComponent::GetInstance().WriteLogMsg("Btr1 =%s\n"+strBtr1 );
		CoreComponent::GetInstance().WriteLogMsg("ID =%s\n"+strID);
		//printf("Data =%s\n",data.data() );
		// 初始化配置

		VCI_INIT_CONFIG init_config;
		int index, filtertype,mode,cannum;
		char szAcc[20],szMask[20],szBtr0[20],szBtr1[20];
		unsigned char sztmp[4];
		DWORD Acc,Mask,Timing0,Timing1;
		std::string str;

		sprintf( szAcc, "%s", strAcc.data() );
		sprintf( szMask, "%s", strMask.data() );
		sprintf( szBtr0, "%s", strBtr0.data() );
		sprintf( szBtr1, "%s", strBtr1.data() );

		if(Utilities::strtodata((unsigned char*)szAcc,sztmp,4,0)!=0)
		{
			CoreComponent::GetInstance().WriteLogMsg("szAcc is error");
		}

		Acc=(((DWORD)sztmp[0])<<24)+(((DWORD)sztmp[1])<<16)+(((DWORD)sztmp[2])<<8)+
			((DWORD)sztmp[3]);

		if(Utilities::strtodata((unsigned char*)szMask,sztmp,4,0)!=0)
		{
			// MessageBox("屏蔽码数据格式不对!","警告",MB_OK|MB_ICONQUESTION);
			// return;
			CoreComponent::GetInstance().WriteLogMsg("szMask is error");
		}
		Mask=(((DWORD)sztmp[0])<<24)+(((DWORD)sztmp[1])<<16)+(((DWORD)sztmp[2])<<8)+
			((DWORD)sztmp[3]);

		if(Utilities::strtodata((unsigned char*)szBtr0,sztmp,1,0)!=0)
		{
			// MessageBox("定时器0数据格式不对!","警告",MB_OK|MB_ICONQUESTION);
			// return;
			CoreComponent::GetInstance().WriteLogMsg("szstrBtr0 is error");
		}
		Timing0=((DWORD)sztmp[0]);

		if(Utilities::strtodata((unsigned char*)szBtr1,sztmp,1,0)!=0)
		{
			// MessageBox("定时器1数据格式不对!","警告",MB_OK|MB_ICONQUESTION);
			// return;
			CoreComponent::GetInstance().WriteLogMsg("szstrBtr1 is error");
		}
		Timing1=((DWORD)sztmp[0]);

		Timing0 = 0x03;
		Timing1 = 0x1C;
		init_config.AccCode = Acc;
		init_config.AccMask = Mask;
		init_config.Timing0= Timing0;
		init_config.Timing1= Timing1;
		init_config.Filter=nFilter_no;
		init_config.Mode=nMode_no;
		CoreComponent::GetInstance().WriteLogMsg("init_config.AccCode=%d",init_config.AccCode); 
		CoreComponent::GetInstance().WriteLogMsg("init_config.AccMask=%d",init_config.AccMask);
		CoreComponent::GetInstance().WriteLogMsg("init_config.Timing0=%d",init_config.Timing0);
		CoreComponent::GetInstance().WriteLogMsg("init_config.Timing1=%d",init_config.Timing1);

		if(VCI_OpenDevice(m_devtype,m_index,0)!=STATUS_OK)
		{
			// MessageBox("打开设备失败!","警告",MB_OK|MB_ICONQUESTION);
			// return;
			CoreComponent::GetInstance().WriteLogMsg("打开设备失败!");
		}

		if(VCI_InitCAN(m_devtype,m_index,m_cannum,&init_config)!=STATUS_OK)
		{
			// MessageBox("初始化CAN失败!","警告",MB_OK|MB_ICONQUESTION);

			CoreComponent::GetInstance().WriteLogMsg("初始化CAN失败!");
			VCI_CloseDevice(m_devtype,m_index);
			return false;
		}

		m_connect=1;
		// m_index =index;
		//   m_cannum=cannum;
		//    GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText("断开");
		//AfxBeginThread(ReceiveThread,this);
	}
	else
	{
		//ui.BtnConnect->setText(tr("Connect"));	
		m_bFlag = true;
		VCI_CloseDevice( m_devtype, m_index);
	}
	return true;
}



bool CAN::startCAN()
{
	if(m_connect==0)
		return false;
	if(VCI_StartCAN(m_devtype, m_index,m_cannum)==1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int CAN::sendFrame(VCI_CAN_OBJ *frameinfo)
{
	int ret = VCI_Transmit(m_devtype,m_index,m_cannum,frameinfo,1);
	//printf("发送帧数据:%s\n",frameinfo->Data);
	if( 0 < ret )
	{
		m_TransmitFlag =  CANFlag::SUCCEED;
	}
	else
	{
		DWORD err = ::GetLastError();
		VCI_ReadErrInfo( m_devtype, m_index, m_cannum, &CANFlag::instace()->getErrorInfo() );
	}
	VCI_GetReceiveNum(m_devtype,m_index,m_cannum);
	return m_TransmitFlag;
}


void CAN::confparm()
{
	// 配置设备参数
	strAcc = "00000000";
	strMask = "ffffffff";
	nFilter_no = 0;
	strBtr0 = "00";
	strBtr1 = "14";
	nMode_no = 0;
	nSendFormat_no = 0;

	nType_no = 0;
	nFormat_no = 0;
	strID = "00000080";
	m_cannum = 0;
	m_index =0;
	m_devtype = (VCI_USBCAN1);

// 	m_app.m_devtype = m_devtype;
// 	m_app.m_cannum = m_cannum;
// 	m_app.m_index = m_index;
}


bool CAN::SendPack(char * data , int size)
{
	byteTotal = 0;
	ULONG frameserial = 0u;
	ULONG nFrameSize = size%8==0?(size/8):(size/8)+1;	//拆包的大小
	VCI_CAN_OBJ frameinfo;
	assert(data);
	char szFrameID[9];
	NetCom::BYTE szData[8];
	unsigned char FrameID[4]={0,0,0,0};
	memset(szFrameID,'0',9);
	char Data[8];
	//char szData[25];
	NetCom::BYTE datalen=0;
	memset( (void*)&frameinfo, 0, sizeof(frameinfo) );
	
	//strtodata((unsigned char*)szFrameID,FrameID,4,0);
	//datalen=(data.length()+1)/3;
	//frameinfo.DataLen=datalen;
	frameinfo.DataLen = 8;
	frameinfo.RemoteFlag=nFormat_no;
	frameinfo.ExternFlag=nType_no;
	// 默认为扩展帧
	//if(frameinfo.ExternFlag==1)
	//{
	//frameinfo.ID=((DWORD)FrameID[0]<<24)+((DWORD)FrameID[1]<<16)+((DWORD)FrameID[2]<<8)+
	//	((DWORD)FrameID[3]);
	//}

	frameinfo.SendType=nSendFormat_no;

	// 发送起始帧告诉对面开始发送帧数据
	frameinfo.DataLen =4;
	const char* STA = "FSTA";
	memcpy(frameinfo.Data,STA,4);
	sendFrame(&frameinfo);
	//byteTotal+=frameinfo.DataLen;
	for (NetCom::UINT i = 0 ; i<nFrameSize;i++)
	{
		//Utilities::ConvertStrToUChar(data+(i*8),frameinfo.Data);

		//Utilities::ConvertUCharToStr(Data,frameinfo.Data);
		//printf("发送帧数据:%s\n",Data);
		memcpy(frameinfo.Data , data+(i*8),8);
		frameinfo.DataLen = 8;
		// 最后一帧
		if(nFrameSize-1== i)
		{
			frameinfo.DataLen = strlen(data+(i*8));
		}
		//strtodata(data+(i*8),szData,8,0);
		frameinfo.ID =i;

		byteTotal+=frameinfo.DataLen;

		sendFrame(&frameinfo);
		//Sleep(100);
	}

	// 发送结束帧
	frameinfo.DataLen =4;
	const char* ACK = "FEND";
	memcpy(frameinfo.Data,ACK,4);
	sendFrame(&frameinfo);
	//byteTotal+=frameinfo.DataLen;
	return true;
}
