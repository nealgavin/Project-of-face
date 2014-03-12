// StuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imagestitch.h"
#include "StuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStuDlg dialog


CStuDlg::CStuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStuDlg)
	m_stuid = _T("");
	m_stuname = _T("");
	//}}AFX_DATA_INIT
}


void CStuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStuDlg)
	DDX_Text(pDX, IDC_EDIT1, m_stuid);
	DDX_Text(pDX, IDC_EDIT2, m_stuname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStuDlg, CDialog)
	//{{AFX_MSG_MAP(CStuDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStuDlg message handlers
