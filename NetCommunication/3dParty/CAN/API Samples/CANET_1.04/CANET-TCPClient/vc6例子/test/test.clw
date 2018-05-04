; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "test.h"

ClassCount=3
Class1=CTestApp
Class2=CTestDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_TEST_DIALOG
Resource4=IDR_MENU1

[CLS:CTestApp]
Type=0
HeaderFile=test.h
ImplementationFile=test.cpp
Filter=N

[CLS:CTestDlg]
Type=0
HeaderFile=testDlg.h
ImplementationFile=testDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CTestDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=testDlg.h
ImplementationFile=testDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_TEST_DIALOG]
Type=1
Class=CTestDlg
ControlCount=21
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_COMBO_INDEX,combobox,1344339971
Control4=IDC_BUTTON_CONNECT,button,1342242817
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO_SENDFRAMETYPE,combobox,1344339971
Control7=IDC_STATIC,static,1342308352
Control8=IDC_COMBO_SENDFRAMEFORMAT,combobox,1344339971
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_SENDFRAMEID,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_SENDDATA,edit,1350631552
Control13=IDC_BUTTON_SEND,button,1342242816
Control14=IDC_STATIC,button,1342177287
Control15=IDC_LIST_INFO,listbox,1352728835
Control16=IDC_STATIC,button,1342177287
Control17=IDC_STATIC,button,1342177287
Control18=IDC_STATIC,static,1342308352
Control19=IDC_IPADDRESS_DESIP,SysIPAddress32,1342242816
Control20=IDC_STATIC,static,1342308352
Control21=IDC_EDIT_DESPORT,edit,1350631552

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_MENU_REFRESH
CommandCount=1

