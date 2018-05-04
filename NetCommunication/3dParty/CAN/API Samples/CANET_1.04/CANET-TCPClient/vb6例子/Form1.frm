VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1 TCP Client"
   ClientHeight    =   6570
   ClientLeft      =   3330
   ClientTop       =   2445
   ClientWidth     =   8910
   LinkTopic       =   "Form1"
   ScaleHeight     =   6570
   ScaleWidth      =   8910
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   5400
      TabIndex        =   15
      Text            =   "00000080"
      Top             =   2820
      Width           =   1215
   End
   Begin VB.Timer Timer1 
      Interval        =   1
      Left            =   7920
      Top             =   1920
   End
   Begin VB.TextBox Text4 
      Height          =   285
      Left            =   930
      TabIndex        =   12
      Text            =   "01 02 03 04 05 06 07 08 "
      Top             =   3315
      Width           =   3855
   End
   Begin VB.ComboBox Combo5 
      Height          =   315
      ItemData        =   "Form1.frx":0000
      Left            =   3240
      List            =   "Form1.frx":000A
      Style           =   2  'Dropdown List
      TabIndex        =   11
      Top             =   2805
      Width           =   1215
   End
   Begin VB.ComboBox Combo4 
      Height          =   315
      ItemData        =   "Form1.frx":001E
      Left            =   1080
      List            =   "Form1.frx":0028
      Style           =   2  'Dropdown List
      TabIndex        =   10
      Top             =   2820
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
   Begin VB.CommandButton Connect 
      Caption         =   "连接"
      Height          =   330
      Left            =   3120
      TabIndex        =   1
      Top             =   430
      Width           =   1005
   End
   Begin VB.Frame Frame1 
      Caption         =   " 发送数据帧 "
      Height          =   1230
      Left            =   120
      TabIndex        =   0
      Top             =   2520
      Width           =   6855
      Begin VB.CommandButton Command1 
         Caption         =   "发送"
         Height          =   330
         Left            =   4920
         TabIndex        =   6
         Top             =   760
         Width           =   870
      End
      Begin VB.Label Label7 
         Caption         =   "数据："
         Height          =   240
         Left            =   240
         TabIndex        =   5
         Top             =   840
         Width           =   555
      End
      Begin VB.Label Label6 
         Caption         =   "帧ID："
         Height          =   195
         Left            =   4680
         TabIndex        =   4
         Top             =   360
         Width           =   585
      End
      Begin VB.Label Label5 
         Caption         =   "帧格式："
         Height          =   195
         Left            =   2400
         TabIndex        =   3
         Top             =   360
         Width           =   765
      End
      Begin VB.Label Label4 
         Caption         =   "帧类型："
         Height          =   195
         Left            =   240
         TabIndex        =   2
         Top             =   360
         Width           =   810
      End
   End
   Begin VB.Frame Frame2 
      Caption         =   "设备参数"
      Height          =   2295
      Left            =   120
      TabIndex        =   7
      Top             =   120
      Width           =   6855
      Begin VB.Frame Frame3 
         Caption         =   " CANETE设置 "
         Height          =   1335
         Left            =   120
         TabIndex        =   16
         Top             =   840
         Width           =   6615
         Begin VB.TextBox Caneteport 
            Height          =   285
            Left            =   2640
            TabIndex        =   20
            Text            =   "4000"
            Top             =   720
            Width           =   2055
         End
         Begin VB.TextBox Caneteip 
            Height          =   285
            Left            =   2640
            TabIndex        =   18
            Text            =   "192.168.0.28"
            Top             =   320
            Width           =   2055
         End
         Begin VB.Label Label2 
            Caption         =   "CANETE端口："
            Height          =   255
            Left            =   1265
            TabIndex        =   19
            Top             =   800
            Width           =   1215
         End
         Begin VB.Label Label1 
            Caption         =   "CANETE IP地址："
            Height          =   255
            Left            =   1080
            TabIndex        =   17
            Top             =   360
            Width           =   1455
         End
      End
      Begin VB.Label Label9 
         Caption         =   "设备索引号："
         Height          =   255
         Left            =   240
         TabIndex        =   8
         Top             =   360
         Width           =   1095
      End
   End
   Begin VB.Frame Frame6 
      Caption         =   "信息"
      Height          =   2535
      Left            =   120
      TabIndex        =   13
      Top             =   3840
      Width           =   8655
      Begin VB.ListBox List1 
         Height          =   2205
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
Dim m_connect As Byte
Dim m_devind As Long
Dim m_cannum As Long


Private Sub Command1_Click()
    If m_connect = 0 Then
        MsgBox ("请先打开设备")
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
        MsgBox ("发送数据失败")
    Else
        List1.AddItem "发送数据成功", List1.ListCount
    End If

End Sub

Private Sub getdata(szip As String, desiparr() As Byte)
    For i = 0 To Len(szip) - 1
        desiparr(i) = Asc(Mid(szip, i + 1, 1))
    Next
    desiparr(Len(szip)) = 0
End Sub

Private Sub Connect_Click()
    Dim index As Long
    Dim cannum As Long
    Dim srcport As Long
    Dim szdesip As String
    Dim desiparr(50) As Byte
    Dim desport As Long
    
    If m_connect = 1 Then
        m_connect = 0
        Connect.Caption = "连接"
        VCI_CloseDevice m_devtype, m_devind
        Exit Sub
    End If
        
    
    If Combo1.ListIndex <> -1 Then
        index = Combo1.ListIndex
        cannum = 0
        srcport = 0
              
        If VCI_OpenDevice(m_devtype, index, srcport) <> 1 Then
            MsgBox ("打开设备错误")
        Else
            szdesip = Caneteip.Text
            getdata szdesip, desiparr
            VCI_SetReference m_devtype, index, 0, 0, desiparr(0)
            desport = Val(Caneteport.Text)
            VCI_SetReference m_devtype, index, 0, 1, desport

            If VCI_StartCAN(m_devtype, index, 0) <> 1 Then
                MsgBox ("打开设备错误")
                Exit Sub
            End If

            m_connect = 1
            m_devind = index
            m_cannum = 0
            Connect.Caption = "断开"
        End If
    End If
    
End Sub

Private Sub Form_Load()
    m_devtype = 17 'CANET-TCP类型号
    m_connect = 0
    m_cannum = 0
    Combo1.ListIndex = 0
    Combo4.ListIndex = 0
    Combo5.ListIndex = 0
End Sub

Private Sub Form_Unload(Cancel As Integer)
    If m_connect = 1 Then
        m_connect = 0
        VCI_CloseDevice m_devtype, m_devind
    End If
End Sub





Private Sub Timer1_Timer()
    Timer1.Enabled = False
    Dim ErrInfo As VCI_ERR_INFO
    
    If m_connect = 0 Then
        Timer1.Enabled = True
        Exit Sub
    End If

    Dim length As Long
    Dim frameinfo(49) As VCI_CAN_OBJ
    Dim str As String
    
    length = VCI_Receive(m_devtype, m_devind, m_cannum, frameinfo(0), 50, 10)
    If length <= 0 Then
        VCI_ReadErrInfo m_devtype, m_devind, m_cannum, ErrInfo '注意：如果没有读到数据则必须调用此函数来读取出当前的错误码，
                                                               '千万不能省略这一步（即使你可能不想知道错误码是什么）
        Timer1.Enabled = True
        Exit Sub
    End If
    
    For i = 0 To length - 1
        str = "接收到数据帧:  "
        If frameinfo(i).TimeFlag = 0 Then
            tmpstr = "时间标识:无  "
        Else
            tmpstr = "时间标识:0x" + Hex(frameinfo(i).TimeStamp)
        End If
        str = str + tmpstr
        tmpstr = "  帧ID:0x" + Hex(frameinfo(i).ID)
        str = str + tmpstr
        str = str + "  帧格式:"
        If frameinfo(i).RemoteFlag = 0 Then
            tmpstr = "数据帧 "
        Else
            tmpstr = "远程帧 "
        End If
        str = str + tmpstr
        str = str + "  帧类型:"
        If frameinfo(i).ExternFlag = 0 Then
            tmpstr = "标准帧 "
        Else
            tmpstr = "扩展帧 "
        End If
        str = str + tmpstr
        List1.AddItem str, List1.ListCount
        If frameinfo(i).RemoteFlag = 0 Then
            str = "  数据:"
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
