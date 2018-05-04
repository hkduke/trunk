unit ControlCAN;

interface

uses
  WinTypes;

const
  DLL_NAME  = 'ControlCAN.dll';//��̬������

type

//�����������ݽṹ

//1.ZLGCANϵ�нӿڿ���Ϣ���������͡�
VCI_BOARD_INFO = Record
		hw_Version : WORD;
		fw_Version : WORD;
		dr_Version : WORD;
		in_Version : WORD;
		irq_Num : WORD;
		can_Num : BYTE;
		str_Serial_Num : array[0..19] of CHAR;
		str_hw_Type : array[0..39] of CHAR;
		Reserved : array[0..3] of WORD;
END;

PVCI_BOARD_INFO=^VCI_BOARD_INFO;

//2.����CAN��Ϣ֡���������͡�
VCI_CAN_OBJ = Record
	ID : UINT;
	TimeStamp : UINT;
	TimeFlag : BYTE;
	SendType : BYTE;
	RemoteFlag : BYTE;//�Ƿ���Զ��֡
	ExternFlag : BYTE;//�Ƿ�����չ֡
	DataLen : BYTE;
	Data : array[0..7] of BYTE;
	Reserved : array[0..2] of BYTE;
END;

PVCI_CAN_OBJ = ^VCI_CAN_OBJ;

//3.����CAN������״̬���������͡�
VCI_CAN_STATUS = Record
	ErrInterrupt : UCHAR;
	regMode : UCHAR;
	regStatus : UCHAR;
	regALCapture : UCHAR;
	regECCapture : UCHAR;
	regEWLimit : UCHAR;
	regRECounter : UCHAR;
	regTECounter : UCHAR;
	Reserved : DWORD;
END;

PVCI_CAN_STATUS = ^VCI_CAN_STATUS;

//4.���������Ϣ���������͡�
VCI_ERR_INFO = Record
		ErrCode : UINT;
		Passive_ErrData : array[0..2] of BYTE;
		ArLost_ErrData : BYTE;
END;

PVCI_ERR_INFO = ^VCI_ERR_INFO;

//5.�����ʼ��CAN����������
VCI_INIT_CONFIG = Record
	AccCode : DWORD;
	AccMask : DWORD;
	Reserved : DWORD;
	Filter : UCHAR;
	Timing0 : UCHAR;
	Timing1 : UCHAR;
	Mode : UCHAR;
END;


CHGDESIPANDPORT = Record
	szpwd : array[0..9] of char;
	szdesip : array[0..19] of char;
	desport: integer;
	blisten : UCHAR;
END;

REMOTE_CLIENT = Record
	iIndex : integer;
	port : integer;
	hClient : DWORD;
	szip : Array[0..31] of char;
END;


PVCI_INIT_CONFIG = ^VCI_INIT_CONFIG;
                    
//���붯̬�⺯��

function VCI_OpenDevice ( DeviceType  : DWORD;
                          DeviceInd : DWORD;
                          Reserved : DWORD) : DWORD;
  stdcall;
  external DLL_NAME;

function VCI_CloseDevice ( DeviceType  : DWORD;
                           DeviceInd : DWORD) : DWORD;
  stdcall;
  external DLL_NAME;

function VCI_InitCAN ( DeviceType  : DWORD;
                       DeviceInd : DWORD;
                       CANInd : DWORD;
                       pInitConfig : PVCI_INIT_CONFIG) : DWORD;
  stdcall;
  external DLL_NAME;

function VCI_ReadBoardInfo ( DeviceType  : DWORD;
                             DeviceInd : DWORD;
                             pInfo : PVCI_BOARD_INFO) : DWORD;
  stdcall;
  external DLL_NAME;

function VCI_ReadErrInfo ( DeviceType  : DWORD;
                           DeviceInd : DWORD;
                           CANInd : DWORD;
                           pErrInfo : PVCI_ERR_INFO) : DWORD;
  stdcall;
  external DLL_NAME;

function VCI_ReadCANStatus ( DeviceType  : DWORD;
                             DeviceInd : DWORD;
                             CANInd : DWORD;
                             pCANStatus : PVCI_CAN_STATUS) : DWORD;
  stdcall;
  external DLL_NAME;

function VCI_GetReference ( DeviceType  : DWORD;
                            DeviceInd : DWORD;
                            CANInd : DWORD;
                            RefType : DWORD;
                            pData : Pointer) : DWORD;
  stdcall;
  external DLL_NAME;

function VCI_SetReference ( DeviceType  : DWORD;
                            DeviceInd : DWORD;
                            CANInd : DWORD;
                            RefType : DWORD;
                            pData : Pointer) : DWORD;
  stdcall;
  external DLL_NAME;

function VCI_GetReceiveNum ( DeviceType  : DWORD;
                             DeviceInd : DWORD;
                             CANInd : DWORD) : ULONG;
  stdcall;
  external DLL_NAME;

function VCI_ClearBuffer ( DeviceType  : DWORD;
                           DeviceInd : DWORD;
                           CANInd : DWORD) : DWORD;
  stdcall;
  external DLL_NAME;

function VCI_StartCAN ( DeviceType  : DWORD;
                        DeviceInd : DWORD;
                        CANInd : DWORD) : DWORD;
  stdcall;
  external DLL_NAME;

function VCI_ResetCAN ( DeviceType  : DWORD;
                        DeviceInd : DWORD;
                        CANInd : DWORD) : DWORD;
  stdcall;
  external DLL_NAME;

function VCI_Transmit ( DeviceType  : DWORD;
                        DeviceInd : DWORD;
                        CANInd : DWORD;
                        pSend : PVCI_CAN_OBJ;
                        Len : ULONG) : ULONG;
  stdcall;
  external DLL_NAME;

function VCI_Receive ( DeviceType  : DWORD;
                        DeviceInd : DWORD;
                        CANInd : DWORD;
                        pReceive : PVCI_CAN_OBJ;
                        Len : ULONG;
                        WaitTime : integer) : ULONG;
  stdcall;
  external DLL_NAME;


implementation

end.
