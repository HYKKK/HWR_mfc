; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWriteDownDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WriteDown.h"

ClassCount=5
Class1=CWriteDownApp
Class2=CWriteDownDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDD_WRITEDOWN_DIALOG
Class4=CInputWnd
Class5=CInputDlg
Resource3=IDR_MAINMENU

[CLS:CWriteDownApp]
Type=0
HeaderFile=WriteDown.h
ImplementationFile=WriteDown.cpp
Filter=N

[CLS:CWriteDownDlg]
Type=0
HeaderFile=WriteDownDlg.h
ImplementationFile=WriteDownDlg.cpp
Filter=W
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDM_ABOUT

[CLS:CAboutDlg]
Type=0
HeaderFile=WriteDownDlg.h
ImplementationFile=WriteDownDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=17
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342308480
Control5=IDC_STATIC,static,1342308480
Control6=IDC_STATIC,static,1342308480
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342308480
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,static,1342308480
Control11=IDC_STATIC,static,1342308480
Control12=IDC_STATIC,button,1342177287
Control13=IDC_STATIC,static,1342308480
Control14=IDC_STATIC,static,1342308480
Control15=IDC_STATIC,static,1342308480
Control16=IDC_STATIC,static,1342308480
Control17=IDC_STATIC,static,1342308480

[DLG:IDD_WRITEDOWN_DIALOG]
Type=1
Class=CWriteDownDlg
ControlCount=9
Control1=IDC_RECOGNIZE,button,1342242817
Control2=IDC_CLEAR,button,1342242816
Control3=IDC_PATTERN,edit,1344274436
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,button,1342177287
Control6=IDC_LEARN,button,1342242816
Control7=IDC_STATIC,static,1342177294
Control8=IDC_SAVE,button,1342242816
Control9=IDC_STATIC,button,1342177287

[CLS:CInputWnd]
Type=0
HeaderFile=InputWnd.h
ImplementationFile=InputWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CInputWnd

[CLS:CInputDlg]
Type=0
HeaderFile=InputDlg.h
ImplementationFile=InputDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CInputDlg
VirtualFilter=dWC

[MNU:IDR_MAINMENU]
Type=1
Class=?
Command1=IDM_SAVE
Command2=IDM_EXIT
Command3=IDM_RECOGNIZE
Command4=IDM_LEARN
Command5=IDM_CLEAR
Command6=IDM_ABOUT
CommandCount=6

