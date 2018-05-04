// testDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "ControlCAN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
	m_EditSendData = _T("");
	m_EditSendFrmID = _T("");
	m_iEditDesPort = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_connect=0;
	m_cannum=0;
	m_devtype=VCI_CANETTCP;
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Control(pDX, IDC_IPADDRESS_DESIP, m_ctlIPAddrDesIP);
	DDX_Control(pDX, IDC_COMBO_INDEX, m_ComboIndex);
	DDX_Control(pDX, IDC_LIST_INFO, m_ListInfo);
	DDX_Control(pDX, IDC_COMBO_SENDFRAMETYPE, m_ComboSendFrmType);
	DDX_Control(pDX, IDC_COMBO_SENDFRAMEFORMAT, m_ComboSendFrmFmt);
	DDX_Text(pDX, IDC_EDIT_SENDDATA, m_EditSendData);
	DDX_Text(pDX, IDC_EDIT_SENDFRAMEID, m_EditSendFrmID);
	DDX_Text(pDX, IDC_EDIT_DESPORT, m_iEditDesPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_COMMAND(ID_MENU_REFRESH, OnMenuRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_ComboSendFrmType.SetCurSel(1);
	m_ComboSendFrmFmt.SetCurSel(0);
	
	m_EditSendFrmID="00000080";
	m_EditSendData="01 02 03 04 05 06 07 08 ";
	
	CString str;
	
	for(int i=0;i<8;i++)
	{
		str.Format("%d",i);
		m_ComboIndex.AddString(str);
	}
	
	m_ComboIndex.SetCurSel(0);
	
	UpdateData(false);
	InitializeCriticalSection(&m_Section);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	int connect=m_connect;
	m_connect=0;
	if(connect)
	{
		Sleep(500);		
		VCI_CloseDevice(m_devtype,m_devind);
	}
	DeleteCriticalSection(&m_Section);
	CDialog::OnCancel();
}

void CTestDlg::OnOK() 
{
	// TODO: Add extra validation here
	int connect=m_connect;
	m_connect=0;
	Sleep(100);
	if(connect)
		VCI_CloseDevice(m_devtype,m_devind);
	
	DeleteCriticalSection(&m_Section);
	CDialog::OnOK();
}

void CTestDlg::OnButtonConnect() 
{
	// TODO: Add your control notification handler code here
	if(m_connect==1)
	{
		m_connect=0;
		Sleep(500);
		GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText("连接");
		VCI_CloseDevice(m_devtype,m_devind);
		return;
	}

	int index;	
	index=m_ComboIndex.GetCurSel();
	UpdateData(TRUE);
	int srcport=0;
	int desport=m_iEditDesPort;
	BYTE desaddr[4];
	m_ctlIPAddrDesIP.GetAddress(desaddr[0],desaddr[1],desaddr[2],desaddr[3]);
	char szdesip[20];
	sprintf(szdesip,"%d.%d.%d.%d",desaddr[0],desaddr[1],desaddr[2],desaddr[3]);
	UpdateData(FALSE);
		
	if(VCI_OpenDevice(m_devtype,index,0)!=STATUS_OK)
	{
		MessageBox("打开设备失败!","警告",MB_OK|MB_ICONQUESTION);
		return;
	}
	VCI_SetReference(m_devtype,index,0,CMD_DESIP,(PVOID)szdesip);
	VCI_SetReference(m_devtype,index,0,CMD_DESPORT,(PVOID)&desport);

	if(VCI_StartCAN(m_devtype,index,0)!=STATUS_OK)
	{
		MessageBox("打开设备失败!","警告",MB_OK|MB_ICONQUESTION);
		return;
	}

	m_connect=1;
	m_devind=index;
	m_cannum=0;
	GetDlgItem(IDC_BUTTON_CONNECT)->SetWindowText("断开");
	AfxBeginThread(ReceiveThread,this);
}

void CTestDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	if(m_connect==0)
		return;
	VCI_CAN_OBJ frameinfo;
	char szFrameID[9];
	unsigned char FrameID[4]={0,0,0,0};
	memset(szFrameID,'0',9);
	unsigned char Data[8];
	char szData[25];
	BYTE datalen=0;
	
	UpdateData(true);
	if(m_EditSendFrmID.GetLength()==0||
		(m_EditSendData.GetLength()==0&&m_ComboSendFrmType.GetCurSel()==0))
	{
		ShowInfo("请输入数据",1);
		return;
	}
	
	if(m_EditSendFrmID.GetLength()>8)
	{
		ShowInfo("ID值超过范围",1);
		return;
	}
	if(m_EditSendData.GetLength()>24)
	{
		ShowInfo("数据长度超过范围,最大为8个字节",1);
		return;
	}
	if(m_ComboSendFrmType.GetCurSel()==0)
	{
		if(m_EditSendData.GetLength()%3==1)
		{
			ShowInfo("数据格式不对,请重新输入",1);
			return;		
		}		
	}
	memcpy(&szFrameID[8-m_EditSendFrmID.GetLength()],(LPCTSTR)m_EditSendFrmID,m_EditSendFrmID.GetLength());
	strtodata((unsigned char*)szFrameID,FrameID,4,0);

	datalen=(m_EditSendData.GetLength()+1)/3;
	strcpy(szData,(LPCTSTR)m_EditSendData);
	strtodata((unsigned char*)szData,Data,datalen,1);


	UpdateData(false);
	
	frameinfo.DataLen=datalen;
	memcpy(&frameinfo.Data,Data,datalen);

	frameinfo.RemoteFlag=m_ComboSendFrmFmt.GetCurSel();
	frameinfo.ExternFlag=m_ComboSendFrmType.GetCurSel();
	if(frameinfo.ExternFlag==1)
	{
		frameinfo.ID=((DWORD)FrameID[0]<<24)+((DWORD)FrameID[1]<<16)+((DWORD)FrameID[2]<<8)+
			((DWORD)FrameID[3]);
	}
	else
	{
		frameinfo.ID=((DWORD)FrameID[2]<<8)+((DWORD)FrameID[3]);		
	}

	if(VCI_Transmit(m_devtype,m_devind,m_cannum,&frameinfo,1)==1)
	{
		ShowInfo("写入成功",0);		
	}
	else
	{
		ShowInfo("写入失败",2);		
	}
	
}

void CTestDlg::ShowInfo(CString str, int code)
{
	m_ListInfo.InsertString(m_ListInfo.GetCount(),str);
	m_ListInfo.SetCurSel(m_ListInfo.GetCount()-1);
}

//-----------------------------------------------------
//参数：
//str：要转换的字符串
//data：储存转换过来的数据串
//len:数据长度
//函数功能：字符串转换为数据串
//-----------------------------------------------------
int CTestDlg::strtodata(unsigned char *str, unsigned char *data,int len,int flag)
{
	unsigned char cTmp=0;
	int i=0;
	for(int j=0;j<len;j++)
	{
		if(chartoint(str[i++],&cTmp))
			return 1;
		data[j]=cTmp;
		if(chartoint(str[i++],&cTmp))
			return 1;
		data[j]=(data[j]<<4)+cTmp;
		if(flag==1)
			i++;
	}
	return 0;
}

//-----------------------------------------------------
//参数：
//chr：要转换的字符
//cint：储存转换过来的数据
//函数功能：字符转换为数据
//-----------------------------------------------------
int CTestDlg::chartoint(unsigned char chr, unsigned char *cint)
{
	unsigned char cTmp;
	cTmp=chr-48;
	if(cTmp>=0&&cTmp<=9)
	{
		*cint=cTmp;
		return 0;
	}
	cTmp=chr-65;
	if(cTmp>=0&&cTmp<=5)
	{
		*cint=(cTmp+10);
		return 0;
	}
	cTmp=chr-97;
	if(cTmp>=0&&cTmp<=5)
	{
		*cint=(cTmp+10);
		return 0;
	}
	return 1;
}

UINT CTestDlg::ReceiveThread(void *param)
{
	CTestDlg *dlg=(CTestDlg*)param;
	CListBox *box=(CListBox *)dlg->GetDlgItem(IDC_LIST_INFO);
	VCI_CAN_OBJ frameinfo[50];
	VCI_ERR_INFO errinfo;
	int len=1;
	int i=0;
	CString str,tmpstr;
	while(1)
	{
		if(dlg->m_connect==0)
			break;
		len=VCI_Receive(dlg->m_devtype,dlg->m_devind,dlg->m_cannum,frameinfo,50,200);
		if(len<=0)
		{
			//注意：如果没有读到数据则必须调用此函数来读取出当前的错误码，
			//千万不能省略这一步（即使你可能不想知道错误码是什么）
			VCI_ReadErrInfo(dlg->m_devtype,dlg->m_devind,dlg->m_cannum,&errinfo);
		}
		else
		{
			for(i=0;i<len;i++)
			{
				str="接收到数据帧:  ";
				if(frameinfo[i].TimeFlag==0)
					tmpstr="时间标识:无  ";
				else
					tmpstr.Format("时间标识:%08x ",frameinfo[i].TimeStamp);
				str+=tmpstr;
				tmpstr.Format("帧ID:%08x ",frameinfo[i].ID);
				str+=tmpstr;
				str+="帧格式:";
				if(frameinfo[i].RemoteFlag==0)
					tmpstr="数据帧 ";
				else
					tmpstr="远程帧 ";
				str+=tmpstr;
				str+="帧类型:";
				if(frameinfo[i].ExternFlag==0)
					tmpstr="标准帧 ";
				else
					tmpstr="扩展帧 ";
				str+=tmpstr;
				box->InsertString(box->GetCount(),str);
				if(frameinfo[i].RemoteFlag==0)
				{
					str="数据:";
					if(frameinfo[i].DataLen>8)
						frameinfo[i].DataLen=8;
					for(int j=0;j<frameinfo[i].DataLen;j++)
					{
						tmpstr.Format("%02x ",frameinfo[i].Data[j]);
						str+=tmpstr;
					}
					//EnterCriticalSection(&(dlg->m_Section));
					//LeaveCriticalSection(&(dlg->m_Section));
					box->InsertString(box->GetCount(),str);
				}				
			}
			box->SetCurSel(box->GetCount()-1);
		}
	}
	return 0;
}

void CTestDlg::OnMenuRefresh() 
{
	// TODO: Add your command handler code here
}
