VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   7365
   ClientLeft      =   3330
   ClientTop       =   2445
   ClientWidth     =   8925
   LinkTopic       =   "Form1"
   ScaleHeight     =   7365
   ScaleWidth      =   8925
   Begin VB.Frame Frame3 
      Caption         =   "���������������ӵĿͻ���"
      Height          =   1935
      Left            =   120
      TabIndex        =   18
      Top             =   5280
      Width           =   8655
      Begin VB.Timer Timer2 
         Interval        =   1000
         Left            =   7200
         Top             =   600
      End
      Begin VB.CommandButton Disconn 
         Caption         =   "�Ͽ�����"
         Height          =   495
         Left            =   6360
         TabIndex        =   20
         Top             =   1200
         Width           =   1695
      End
      Begin VB.ListBox ListClient 
         Height          =   1425
         Left            =   120
         TabIndex        =   19
         Top             =   360
         Width           =   6015
      End
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   5520
      TabIndex        =   15
      Text            =   "00000080"
      Top             =   1980
      Width           =   1215
   End
   Begin VB.Timer Timer1 
      Interval        =   1
      Left            =   7920
      Top             =   1920
   End
   Begin VB.TextBox Text4 
      Height          =   285
      Left            =   1200
      TabIndex        =   12
      Text            =   "01 02 03 04 05 06 07 08 "
      Top             =   2475
      Width           =   3855
   End
   Begin VB.ComboBox Combo5 
      Height          =   315
      ItemData        =   "Form1.frx":0000
      Left            =   3360
      List            =   "Form1.frx":000A
      Style           =   2  'Dropdown List
      TabIndex        =   11
      Top             =   1965
      Width           =   1215
   End
   Begin VB.ComboBox Combo4 
      Height          =   315
      ItemData        =   "Form1.frx":001E
      Left            =   1200
      List            =   "Form1.frx":0028
      Style           =   2  'Dropdown List
      TabIndex        =   10
      Top             =   1980
      Width           =   1215
   End
   Begin VB.ComboBox Combo1 
      Height          =   315
      ItemData        =   "Form1.frx":003C
      Left            =   1440
      List            =   "Form1.frx":0058
      Style           =   2  'Dropdown List
      TabIndex        =   9
      Top             =   420
      Width           =   1050
   End
   Begin VB.CommandButton Start 
      Caption         =   "����"
      Height          =   330
      Left            =   6000
      TabIndex        =   1
      Top             =   1080
      Width           =   1005
   End
   Begin VB.Frame Frame1 
      Caption         =   " ��������֡ "
      Height          =   1230
      Left            =   240
      TabIndex        =   0
      Top             =   1680
      Width           =   6855
      Begin VB.CommandButton Command1 
         Caption         =   "����"
         Height          =   330
         Left            =   5400
         TabIndex        =   6
         Top             =   720
         Width           =   870
      End
      Begin VB.Label Label7 
         Caption         =   "���ݣ�"
         Height          =   240
         Left            =   240
         TabIndex        =   5
         Top             =   840
         Width           =   555
      End
      Begin VB.Label Label6 
         Caption         =   "֡ID��"
         Height          =   195
         Left            =   4680
         TabIndex        =   4
         Top             =   360
         Width           =   585
      End
      Begin VB.Label Label5 
         Caption         =   "֡��ʽ��"
         Height          =   195
         Left            =   2400
         TabIndex        =   3
         Top             =   360
         Width           =   765
      End
      Begin VB.Label Label4 
         Caption         =   "֡���ͣ�"
         Height          =   195
         Left            =   240
         TabIndex        =   2
         Top             =   360
         Width           =   810
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "�豸����"
      Height          =   1335
      Left            =   240
      TabIndex        =   7
      Top             =   120
      Width           =   6855
      Begin VB.TextBox TextServerPort 
         Height          =   285
         Left            =   1560
         TabIndex        =   17
         Text            =   "4000"
         Top             =   840
         Width           =   1215
      End
      Begin VB.Label Label1 
         Caption         =   "�������˿�"
         Height          =   375
         Left            =   240
         TabIndex        =   16
         Top             =   720
         Width           =   1095
      End
      Begin VB.Label Label9 
         Caption         =   "�豸�����ţ�"
         Height          =   255
         Left            =   240
         TabIndex        =   8
         Top             =   360
         Width           =   1095
      End
   End
   Begin VB.Frame Frame6 
      Caption         =   "��Ϣ"
      Height          =   2175
      Left            =   120
      TabIndex        =   13
      Top             =   3000
      Width           =   8655
      Begin VB.ListBox List1 
         Height          =   1815
         Left            =   120
         TabIndex        =   14
         Top             =   240
         Width           =   8415
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim m_devtype As Long
Dim m_devind As Long
Dim m_bStarted As Long
Dim m_cannum As Long
Dim m_client As REMOTE_CLIENT


Private Sub Command1_Click()
'�������ݰ�
    If m_bStarted = 0 Then
        MsgBox ("���ȴ��豸")
        Exit Sub
    End If
    
    Dim SendType, frameformat, frametype As Byte
    Dim ID As Long
    Dim data(7) As Byte
    Dim frameinfo As VCI_CAN_OBJ
    Dim str As String
    
    frameformat = Combo5.ListIndex
    frametype = Combo4.ListIndex
    str = "&H"
    str = str + Text1.Text
    ID = Val(str)
    str = Text4.Text
    strdata = " "
    i = 0
    For i = 0 To 7
       strdata = Left(str, 2)
       If Len(strdata) = 0 Then
          Exit For
       End If
       str = Right(str, Len(str) - 3)
       data(i) = Val("&H" + strdata)
    Next
    
    frameinfo.DataLen = i
    frameinfo.ExternFlag = frametype
    frameinfo.RemoteFlag = frameformat
    frameinfo.ID = ID
    For j = 0 To i - 1
        frameinfo.data(j) = data(j)
    Next
    If VCI_Transmit(m_devtype, m_devind, m_cannum, frameinfo, 1) <> 1 Then
        MsgBox ("��������ʧ��")
    Else
        List1.AddItem "�������ݳɹ�", List1.ListCount
    End If

End Sub

Private Sub getdata(szip As String, desiparr() As Byte)
    For i = 0 To Len(szip) - 1
        desiparr(i) = Asc(Mid(szip, i + 1, 1))
    Next
    desiparr(Len(szip)) = 0
End Sub


Private Sub Disconn_Click()
    Dim DisCon As REMOTE_CLIENT
    DisCon.iIndex = ListClient.ListIndex
    If VCI_GetReference(m_devtype, m_devind, 0, 6, DisCon) = 1 Then
        VCI_SetReference m_devtype, m_devind, 0, 7, DisCon
    End If
    
End Sub

Private Sub Form_Load()
    m_devtype = 17 'CANET-TCP���ͺ�
    m_cannum = 0
    m_bStarted = 0
    Combo1.ListIndex = 0
    Combo4.ListIndex = 0
    Combo5.ListIndex = 0
End Sub

Private Sub Form_Unload(Cancel As Integer)
    If m_bStarted = 1 Then
        m_bStarted = 0
        VCI_CloseDevice m_devtype, m_devind
        Timer2.Enabled = False
    End If
End Sub





Private Sub Start_Click()
    Dim index As Long
    Dim cannum As Long
    Dim srcport As Long
    Dim iTcpType As Long
    Dim iTmp As Long
    
    iTcpType = 1 'server type
    
    If m_bStarted = 1 Then
        m_bStarted = 0
        Start.Caption = "����"
        VCI_CloseDevice m_devtype, m_devind
        Exit Sub
    End If
        
    srcport = Val(TextServerPort.Text)
    If TextServerPort.Text = "0" Then
        MsgBox ("�˿ںŲ���Ϊ0��")
        Exit Sub
    End If
        
    
    
    If Combo1.ListIndex <> -1 Then
        index = Combo1.ListIndex
        cannum = 0
        
              
        If VCI_OpenDevice(m_devtype, index, 0) <> 1 Then
            MsgBox ("���豸����!!!!")
        Else
            VCI_SetReference m_devtype, index, 0, 4, iTcpType
            VCI_SetReference m_devtype, index, 0, 2, srcport

            If VCI_StartCAN(m_devtype, index, 0) <> 1 Then
                MsgBox ("���豸����...")
                Exit Sub
            End If

            Timer2.Enabled = True
            m_bStarted = 1
            m_devind = index
            m_cannum = 0
            Start.Caption = "�Ͽ�"
        End If
    End If
End Sub

Private Sub Timer1_Timer()
    Timer1.Enabled = False
    Dim ErrInfo As VCI_ERR_INFO
    
    If m_bStarted = 0 Then
        Timer1.Enabled = True
        Exit Sub
    End If

    Dim length As Long
    Dim frameinfo(49) As VCI_CAN_OBJ
    Dim str As String
    
    length = VCI_Receive(m_devtype, m_devind, m_cannum, frameinfo(0), 50, 10)
    If length <= 0 Then
        VCI_ReadErrInfo m_devtype, m_devind, m_cannum, ErrInfo 'ע�⣺���û�ж��������������ô˺�������ȡ����ǰ�Ĵ����룬
                                                               'ǧ����ʡ����һ������ʹ����ܲ���֪����������ʲô��
        Timer1.Enabled = True
        Exit Sub
    End If
    
    For i = 0 To length - 1
        str = "���յ�����֡:  "
        If frameinfo(i).TimeFlag = 0 Then
            tmpstr = "ʱ���ʶ:��  "
        Else
            tmpstr = "ʱ���ʶ:0x" + Hex(frameinfo(i).TimeStamp)
        End If
        str = str + tmpstr
        tmpstr = "  ֡ID:0x" + Hex(frameinfo(i).ID)
        str = str + tmpstr
        str = str + "  ֡��ʽ:"
        If frameinfo(i).RemoteFlag = 0 Then
            tmpstr = "����֡ "
        Else
            tmpstr = "Զ��֡ "
        End If
        str = str + tmpstr
        str = str + "  ֡����:"
        If frameinfo(i).ExternFlag = 0 Then
            tmpstr = "��׼֡ "
        Else
            tmpstr = "��չ֡ "
        End If
        str = str + tmpstr
        List1.AddItem str, List1.ListCount
        If frameinfo(i).RemoteFlag = 0 Then
            str = "  ����:"
            If frameinfo(i).DataLen > 8 Then
                frameinfo(i).DataLen = 8
            End If
            For j = 0 To frameinfo(i).DataLen - 1
                tmpstr = Hex(frameinfo(i).data(j)) + " "
                str = str + tmpstr
            Next
            List1.AddItem str, List1.ListCount
        End If
    Next
    Timer1.Enabled = True
End Sub

Private Sub Timer2_Timer()
    Dim iSel As Long
    Dim iCount As Long
    Dim i As Long
    Dim strTmp As String
    
    Dim inta As Integer
    Dim dataa As Byte
    Dim tmp As String
    
    If m_bStarted = 0 Then
        Timer2.Enabled = False
        Exit Sub
    End If
    
    
    iSel = ListClient.ListIndex
    ListClient.Clear
    
    VCI_GetReference m_devtype, m_devind, 0, 5, iCount
    
    If iCount = 0 Then
        Exit Sub
    End If
    
    For i = 0 To iCount - 1
        m_client.iIndex = i
        VCI_GetReference m_devtype, m_devind, 0, 6, m_client
        strTmp = StrConv(m_client.szip, vbUnicode)
        inta = InStr(strTmp, Chr$(0))
        strTmp = Left(strTmp, inta - 1)
        strTmp = "IP:" & strTmp & "  Port:" & str(m_client.port)
        ListClient.AddItem strTmp, i
    Next
        
    If iSel < iCount Then
        ListClient.ListIndex = iSel
    End If
    
    
    
End Sub
