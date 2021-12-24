; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMJ095View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mj095.h"
LastPage=0

ClassCount=8
Class1=CMainFrame
Class2=CMJ095App
Class3=CAboutDlg
Class4=CMJ095Doc
Class5=CMJ095View

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class6=CDlgHistogram
Resource3=IDD_DIALOGBAR (English (U.S.))
Resource4=IDD_IDD_HISTOGRAM_DIALOG
Class7=IDD_HISTOGRAM
Class8=LINEDIALOG
Resource5=IDD_LINDIALOG

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=CMainFrame

[CLS:CMJ095App]
Type=0
BaseClass=CWinApp
HeaderFile=MJ095.h
ImplementationFile=MJ095.cpp
LastObject=CMJ095App

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=MJ095.cpp
ImplementationFile=MJ095.cpp
LastObject=CAboutDlg
Filter=D
VirtualFilter=dWC

[CLS:CMJ095Doc]
Type=0
BaseClass=CDocument
HeaderFile=MJ095Doc.h
ImplementationFile=MJ095Doc.cpp
LastObject=CMJ095Doc

[CLS:CMJ095View]
Type=0
BaseClass=CScrollView
HeaderFile=MJ095View.h
ImplementationFile=MJ095View.cpp
LastObject=ID_GRAD
Filter=C
VirtualFilter=VWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=CAboutDlg
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_GRAY
Command10=ID_Histogram
Command11=ID_LINE
Command12=ID_EQUALIZATION
Command13=ID_FOURIER
Command14=ID_IFOURIER
Command15=ID_FASTFOURIER
Command16=ID_IFASTFOURIER
Command17=ID_AVG
Command18=ID_MID
Command19=ID_GRAD
Command20=ID_RAPLAS
CommandCount=20

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:CDlgHistogram]
Type=0
HeaderFile=DlgHistogram.h
ImplementationFile=DlgHistogram.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgHistogram
VirtualFilter=dWC

[DLG:IDD_DIALOGBAR (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_IDD_HISTOGRAM_DIALOG]
Type=1
Class=IDD_HISTOGRAM
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:IDD_HISTOGRAM]
Type=0
HeaderFile=IDD_HISTOGRAM.h
ImplementationFile=IDD_HISTOGRAM.cpp
BaseClass=CDialog
Filter=D
LastObject=IDD_HISTOGRAM
VirtualFilter=dWC

[DLG:IDD_LINDIALOG]
Type=1
Class=LINEDIALOG
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308864
Control7=IDC_STATIC,static,1342308352

[CLS:LINEDIALOG]
Type=0
HeaderFile=LINEDIALOG.h
ImplementationFile=LINEDIALOG.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_ABOUT
VirtualFilter=dWC

