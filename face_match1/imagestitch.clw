; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=imagefull
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "imagestitch.h"
LastPage=0

ClassCount=16
Class1=CImagestitchApp
Class2=CImagestitchDoc
Class3=CImagestitchView
Class4=CMainFrame
Class7=featurematch

ResourceCount=7
Resource1=IDR_IMAGESTYPE
Resource2=IDD_STABLE
Class5=CChildFrame
Class6=CAboutDlg
Class8=imagematch
Class9=stitchimage
Class10=imagefull
Resource3=IDD_fullimage
Class11=CAddDlg
Resource4=IDR_MAINFRAME
Class12=CStuDlg
Resource5=IDD_ADD
Class13=CCourseDlg
Resource6=IDD_COURSE
Class14=CGradeDlg
Class15=CMysqlDlg
Class16=CCapDlg
Resource7=IDD_GRADE

[CLS:CImagestitchApp]
Type=0
HeaderFile=imagestitch.h
ImplementationFile=imagestitch.cpp
Filter=N

[CLS:CImagestitchDoc]
Type=0
HeaderFile=imagestitchDoc.h
ImplementationFile=imagestitchDoc.cpp
Filter=N

[CLS:CImagestitchView]
Type=0
HeaderFile=imagestitchView.h
ImplementationFile=imagestitchView.cpp
Filter=C
LastObject=CImagestitchView
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=imagestitch.cpp
ImplementationFile=imagestitch.cpp
Filter=D

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_IMAGESTYPE]
Type=1
Class=CImagestitchView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=ID_WINDOW_NEW
Command18=ID_WINDOW_CASCADE
Command19=ID_WINDOW_TILE_HORZ
Command20=ID_WINDOW_ARRANGE
Command21=ID_APP_ABOUT
Command22=ID_image_full
CommandCount=22

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
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

[CLS:featurematch]
Type=0
HeaderFile=featurematch.h
ImplementationFile=featurematch.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_step5

[CLS:imagematch]
Type=0
HeaderFile=imagematch.h
ImplementationFile=imagematch.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_ABOUT

[CLS:stitchimage]
Type=0
HeaderFile=stitchimage.h
ImplementationFile=stitchimage.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_siftstitch

[DLG:IDD_fullimage]
Type=1
Class=imagefull
ControlCount=23
Control1=IDC_openimage2,button,1342242816
Control2=IDC_openimage1,button,1342242816
Control3=IDC_openimage6,button,1342242816
Control4=IDC_stitchfullimage,button,1342242816
Control5=IDC_BUTTON1,button,1342242816
Control6=IDC_BUTTON3,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,button,1342177287
Control10=IDC_BUTTON4,button,1342242816
Control11=IDC_BUTTON6,button,1342242816
Control12=IDC_BUTTON7,button,1342242816
Control13=IDC_BUTTON8,button,1342242816
Control14=IDC_STATIC,button,1342177287
Control15=IDC_BUTTON9,button,1342242816
Control16=IDC_ShowImg1,static,1342177287
Control17=IDC_ShowImg2,static,1342177287
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_ShowImg3,static,1342177287
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_LIST,listbox,1352728835

[CLS:imagefull]
Type=0
HeaderFile=imagefull.h
ImplementationFile=imagefull.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_ABOUT
VirtualFilter=dWC

[DLG:IDD_ADD]
Type=1
Class=CAddDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_EDIT2,edit,1350631552

[CLS:CAddDlg]
Type=0
HeaderFile=AddDlg.h
ImplementationFile=AddDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAddDlg
VirtualFilter=dWC

[DLG:IDD_STABLE]
Type=1
Class=CStuDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT1,edit,1350631552
Control6=IDC_EDIT2,edit,1350631552

[CLS:CStuDlg]
Type=0
HeaderFile=StuDlg.h
ImplementationFile=StuDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CStuDlg
VirtualFilter=dWC

[DLG:IDD_COURSE]
Type=1
Class=CCourseDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT1,edit,1350631552
Control7=IDC_EDIT2,edit,1350631552
Control8=IDC_EDIT3,edit,1350631552

[CLS:CCourseDlg]
Type=0
HeaderFile=CourseDlg.h
ImplementationFile=CourseDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[DLG:IDD_GRADE]
Type=1
Class=CGradeDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT1,edit,1350631552
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_EDIT5,edit,1350631552
Control10=IDC_EDIT6,edit,1350631552

[CLS:CGradeDlg]
Type=0
HeaderFile=GradeDlg.h
ImplementationFile=GradeDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CGradeDlg

[CLS:CCapDlg]
Type=0
HeaderFile=CapDlg.h
ImplementationFile=CapDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[CLS:CMysqlDlg]
Type=0
HeaderFile=MysqlDlg.h
ImplementationFile=MysqlDlg.cpp
BaseClass=CDialog
Filter=D

