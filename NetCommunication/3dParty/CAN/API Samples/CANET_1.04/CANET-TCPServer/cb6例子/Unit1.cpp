//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;


/*
�����Ǿ���ĵ��ö�̬������������õ��Ƕ�̬���صķ�������Ҫ�����ڳ����ʼ����
ʱ��Ӷ�̬����ȡ�ø��������ĵ�ַ������������Ȼ������Ҫ��ʱ����þͿ����ˣ������
�����˳���ʱ���ͷŵ��򿪵Ķ�̬�������С�
*/

//���ȶ�����Ҫ�õ������ݽṹ
//1.ZLGCANϵ�нӿڿ���Ϣ���������͡�
typedef  struct  _VCI_BOARD_INFO{
		USHORT	hw_Version;
		USHORT	fw_Version;
		USHORT	dr_Version;
		USHORT	in_Version;
		USHORT	irq_Num;
		BYTE	can_Num;
		CHAR	str_Serial_Num[20];
		CHAR	str_hw_Type[40];
		USHORT	Reserved[4];
} VCI_BOARD_INFO,*PVCI_BOARD_INFO;

//2.����CAN��Ϣ֡���������͡�
typedef  struct  _VCI_CAN_OBJ{
	UINT	ID;
	UINT	TimeStamp;
	BYTE	TimeFlag;
	BYTE	SendType;
	BYTE	RemoteFlag;//�Ƿ���Զ��֡
	BYTE	ExternFlag;//�Ƿ�����չ֡
	BYTE	DataLen;
	BYTE	Data[8];
	BYTE	Reserved[3];
}VCI_CAN_OBJ,*PVCI_CAN_OBJ;

//3.����CAN������״̬���������͡�
typedef struct _VCI_CAN_STATUS{
	UCHAR	ErrInterrupt;
	UCHAR	regMode;
	UCHAR	regStatus;
	UCHAR	regALCapture;
	UCHAR	regECCapture; 
	UCHAR	regEWLimit;
	UCHAR	regRECounter; 
	UCHAR	regTECounter;
	DWORD	Reserved;
}VCI_CAN_STATUS,*PVCI_CAN_STATUS;

//4.���������Ϣ���������͡�
typedef struct _ERR_INFO{
		UINT	ErrCode;
		BYTE	Passive_ErrData[3];
		BYTE	ArLost_ErrData;
} VCI_ERR_INFO,*PVCI_ERR_INFO;

//5.�����ʼ��CAN����������
typedef struct _INIT_CONFIG{
	DWORD	AccCode;
	DWORD	AccMask;
	DWORD	Reserved;
	UCHAR	Filter;
	UCHAR	Timing0;
	UCHAR	Timing1;
	UCHAR	Mode;
}VCI_INIT_CONFIG,*PVCI_INIT_CONFIG;

typedef struct _tagChgDesIPAndPort
{
	char szpwd[10];
	char szdesip[20];
	int desport;
	BYTE blistenonly;
}CHGDESIPANDPORT;


#define CMD_DESPORT  		1
#define CMD_SRCPORT  		2
#define CMD_TCP_TYPE		4//tcp ������ʽ��������:1 ���ǿͻ���:0
#define TCP_CLIENT   		0
#define TCP_SERVER   		1
//��������ʽ����Ч
#define CMD_CLIENT_COUNT        5//�����ϵĿͻ��˼���
#define CMD_CLIENT		6//�����ϵĿͻ���
#define CMD_DISCONN_CLINET      7//�Ͽ�һ������

typedef struct tagRemoteClient{
	int iIndex;
	DWORD port;
	HANDLE hClient;
	char szip[32];
}REMOTE_CLIENT;

//����������Ҫ����ĺ�������
//����ControlCAN.h�еĺ����������庯��ָ������
//////////////////////////////////////////////////////////////////////////
typedef DWORD (CALLBACK*  LPVCI_OpenDevice)(DWORD,DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_CloseDevice)(DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_InitCan)(DWORD,DWORD,DWORD,PVCI_INIT_CONFIG);

typedef DWORD (CALLBACK*  LPVCI_ReadBoardInfo)(DWORD,DWORD,PVCI_BOARD_INFO);
typedef DWORD (CALLBACK*  LPVCI_ReadErrInfo)(DWORD,DWORD,DWORD,PVCI_ERR_INFO);
typedef DWORD (CALLBACK*  LPVCI_ReadCanStatus)(DWORD,DWORD,DWORD,PVCI_CAN_STATUS);

typedef DWORD (CALLBACK*  LPVCI_GetReference)(DWORD,DWORD,DWORD,DWORD,PVOID);
typedef DWORD (CALLBACK*  LPVCI_SetReference)(DWORD,DWORD,DWORD,DWORD,PVOID);

typedef ULONG (CALLBACK*  LPVCI_GetReceiveNum)(DWORD,DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_ClearBuffer)(DWORD,DWORD,DWORD);

typedef DWORD (CALLBACK*  LPVCI_StartCAN)(DWORD,DWORD,DWORD);
typedef DWORD (CALLBACK*  LPVCI_ResetCAN)(DWORD,DWORD,DWORD);

typedef ULONG (CALLBACK*  LPVCI_Transmit)(DWORD,DWORD,DWORD,PVCI_CAN_OBJ,ULONG);
typedef ULONG (CALLBACK*  LPVCI_Receive)(DWORD,DWORD,DWORD,PVCI_CAN_OBJ,ULONG,INT);
//////////////////////////////////////////////////////////////////////////

HANDLE m_hDLL;//��������򿪵Ķ�̬����

//�ӿں���ָ��
LPVCI_OpenDevice VCI_OpenDevice;
LPVCI_CloseDevice VCI_CloseDevice;
LPVCI_InitCan VCI_InitCAN;
LPVCI_ReadBoardInfo VCI_ReadBoardInfo;
LPVCI_ReadErrInfo VCI_ReadErrInfo;
LPVCI_ReadCanStatus VCI_ReadCanStatus;
LPVCI_GetReference VCI_GetReference;
LPVCI_SetReference VCI_SetReference;
LPVCI_GetReceiveNum VCI_GetReceiveNum;
LPVCI_ClearBuffer VCI_ClearBuffer;
LPVCI_StartCAN VCI_StartCAN;
LPVCI_ResetCAN VCI_ResetCAN;
LPVCI_Transmit VCI_Transmit;
LPVCI_Receive VCI_Receive;


////////////////////////////////////////////////////////////////////////////
DWORD m_devtype=17;//CANET-TCP���ͺ�
DWORD m_devind=0;
DWORD m_cannum=0;
int m_bStarted=0;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        m_hDLL = LoadLibrary("ControlCAN.dll");//�򿪶�̬��

        //ȡ�ú�����ַ
        VCI_OpenDevice=(LPVCI_OpenDevice)GetProcAddress(m_hDLL,"VCI_OpenDevice");
 	VCI_CloseDevice=(LPVCI_CloseDevice)GetProcAddress(m_hDLL,"VCI_CloseDevice");
   	VCI_InitCAN=(LPVCI_InitCan)GetProcAddress(m_hDLL,"VCI_InitCAN");
   	VCI_ReadBoardInfo=(LPVCI_ReadBoardInfo)GetProcAddress(m_hDLL,"VCI_ReadBoardInfo");
    	VCI_ReadErrInfo=(LPVCI_ReadErrInfo)GetProcAddress(m_hDLL,"VCI_ReadErrInfo");
    	VCI_ReadCanStatus=(LPVCI_ReadCanStatus)GetProcAddress(m_hDLL,"VCI_ReadCANStatus");
  	VCI_GetReference=(LPVCI_GetReference)GetProcAddress(m_hDLL,"VCI_GetReference");
    	VCI_SetReference=(LPVCI_SetReference)GetProcAddress(m_hDLL,"VCI_SetReference");
  	VCI_GetReceiveNum=(LPVCI_GetReceiveNum)GetProcAddress(m_hDLL,"VCI_GetReceiveNum");
 	VCI_ClearBuffer=(LPVCI_ClearBuffer)GetProcAddress(m_hDLL,"VCI_ClearBuffer");
 	VCI_StartCAN=(LPVCI_StartCAN)GetProcAddress(m_hDLL,"VCI_StartCAN");
  	VCI_ResetCAN=(LPVCI_ResetCAN)GetProcAddress(m_hDLL,"VCI_ResetCAN");
    	VCI_Transmit=(LPVCI_Transmit)GetProcAddress(m_hDLL,"VCI_Transmit");
    	VCI_Receive=(LPVCI_Receive)GetProcAddress(m_hDLL,"VCI_Receive");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        if(m_bStarted==1)
        {
                m_bStarted=0;
                WaitForSingleObject(m_readhandle,2000);
                m_readhandle=NULL;
                VCI_CloseDevice(m_devtype,m_devind);
        }

        FreeLibrary(m_hDLL);//�ͷŶ�̬����
}
//---------------------------------------------------------------------------




void ReceiveThread(void *param)
{
   TListBox *box=(TListBox*)param;
   VCI_CAN_OBJ receivedata[50];
   VCI_ERR_INFO errinfo;
   int len,i;
   AnsiString str,tmpstr;
   while(1)
   {
        if(m_bStarted==0)
                break;
        Sleep(1);
        len=VCI_Receive(m_devtype,m_devind,m_cannum,receivedata,50,200);
        if(len<=0)
        {
                //ע�⣺���û�ж��������������ô˺�������ȡ����ǰ�Ĵ����룬
                //ǧ����ʡ����һ������ʹ����ܲ���֪����������ʲô��
                VCI_ReadErrInfo(m_devtype,m_devind,m_cannum,&errinfo);
        }
        else
        {
	        for(i=0;i<len;i++)
		{
			str="���յ�����֡:  ";
			if(receivedata[i].TimeFlag==0)
				tmpstr="ʱ���ʶ:��  ";
			else
				tmpstr="ʱ���ʶ:0x"+IntToHex((int)receivedata[i].TimeStamp,8)+" ";
			str+=tmpstr;
			tmpstr="֡ID:0x"+IntToHex((int)receivedata[i].ID,8)+" ";
			str+=tmpstr;
			str+="֡��ʽ:";
			if(receivedata[i].RemoteFlag==0)
				tmpstr="����֡ ";
			else
				tmpstr="Զ��֡ ";
			str+=tmpstr;
			str+="֡����:";
			if(receivedata[i].ExternFlag==0)
				tmpstr="��׼֡ ";
			else
				tmpstr="��չ֡ ";
			str+=tmpstr;
			box->Items->Add(str);
			if(receivedata[i].RemoteFlag==0)
			{
				str="����:";
                                if(receivedata[i].DataLen>8)
                                        receivedata[i].DataLen=8;
				for(int j=0;j<receivedata[i].DataLen;j++)
				{
					tmpstr=IntToHex((int)receivedata[i].Data[j],2)+" ";
					str+=tmpstr;
				}
				box->Items->Add(str);
			}
		}
		box->ItemIndex=box->Items->Count-1;
        }
   }

   _endthread();
}


void __fastcall TForm1::Button1Click(TObject *Sender)
{
        if(m_bStarted ==1)
        {
                Button1->Caption ="����";
                m_bStarted=0;
                WaitForSingleObject(m_readhandle,2000);
                m_readhandle=NULL;
                VCI_CloseDevice(m_devtype,m_devind);
                return;
        }
        int index = ComboBox1->ItemIndex;
        int cannum =0;
        int iTcpType = 1;//tcp server
        char szcaneteip[50];
        int srcport=StrToInt(Edit3->Text);

        if(index>=0)
        {
                if(VCI_OpenDevice(m_devtype,index,srcport)==1)
                {
                       VCI_SetReference(m_devtype,index, 0, CMD_TCP_TYPE,(void*)&iTcpType);
                         if(VCI_StartCAN(m_devtype,index,0)==0)
                         {
                           ShowMessage("�򿪶˿ڴ���");
                           return;
                         }

                       Button1->Caption ="�Ͽ�";
                       iTcpType=1;
                       m_devind=index;
                       m_cannum=cannum;
                       m_bStarted = 1;
                       Timer1->Enabled = 1;
                       m_readhandle=(HANDLE)_beginthread(ReceiveThread,0,(void*)ListBox1);
                }
                else
                {
                        ShowMessage("�򿪶˿ڴ���");
                }

        }
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
      ComboBox1->ItemIndex = 0;
      ComboBox6->ItemIndex =0;
      ComboBox7->ItemIndex =0;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


void __fastcall TForm1::Button4Click(TObject *Sender)
{
        if(m_bStarted==0)
        {
                ShowMessage("���ȴ򿪶˿�");
                return;
        }

        BYTE frametype,frameformat;
        DWORD id;
        BYTE data[8];

        frametype=ComboBox6->ItemIndex;
        frameformat=ComboBox7->ItemIndex;
        id=StrToInt("0x"+Edit1->Text);

        AnsiString str=Edit4->Text;
        AnsiString strdata;
        int i,kkk;
        for(i=0;i<8;i++)
        {
                strdata=str.SubString(3*i+1,2);
                strdata=strdata.Trim();
                kkk=strdata.Length();
                if(kkk==0)
                {
                        goto exit;
                }
                data[i]=StrToInt(strdata);
                //sscanf(strdata.c_str(),"%x",data+i);
        }

exit:
        VCI_CAN_OBJ senddata;
        senddata.ExternFlag=frametype;
        senddata.RemoteFlag=frameformat;
        senddata.ID=id;
        senddata.DataLen=i;
        memcpy(senddata.Data,data,i);

        if(VCI_Transmit(m_devtype,m_devind,m_cannum,&senddata,1)==1)
        {
                ListBox1->Items->Add("���ͳɹ�");
        }
        else
        {
                ListBox1->Items->Add("����ʧ��");
        }

}


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        int iClientCount = 0;
        REMOTE_CLIENT cli;
        int iSelcted = 0;

        if (m_bStarted == 0)
                return ;

        iSelcted = ListBox2->ItemIndex;
        ListBox2->Clear();
        VCI_GetReference(m_devtype, m_devind, 0, CMD_CLIENT_COUNT, (void*)&iClientCount);
        for (int i=0; i<iClientCount; ++i)
        {
          cli.iIndex = i;
          VCI_GetReference(m_devtype,m_devind,0,CMD_CLIENT,(void*)&cli);
          AnsiString str;
          str = cli.szip;
          str = "IP:" + str + "   PORT:" + IntToStr(cli.port);
          ListBox2->Items->Add(str);
        }

        if (iSelcted < iClientCount )
          ListBox2->ItemIndex = iSelcted;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
        int iSelcted = 0;
        REMOTE_CLIENT cli;
        iSelcted = ListBox2->ItemIndex;
        cli.iIndex = iSelcted;
        VCI_SetReference(m_devtype, m_devind, 0, CMD_DISCONN_CLINET, (void*)&cli);

}
//---------------------------------------------------------------------------

