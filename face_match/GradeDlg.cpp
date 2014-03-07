// GradeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imagestitch.h"
#include "GradeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGradeDlg dialog


CGradeDlg::CGradeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGradeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGradeDlg)
	m_gradeid = _T("");
	m_classid = _T("");
	m_classname = _T("");
	m_gradename = _T("");
	//}}AFX_DATA_INIT
}


void CGradeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGradeDlg)
	DDX_Text(pDX, IDC_EDIT1, m_gradeid);
	DDX_Text(pDX, IDC_EDIT2, m_classid);
	DDX_Text(pDX, IDC_EDIT5, m_classname);
	DDX_Text(pDX, IDC_EDIT6, m_gradename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGradeDlg, CDialog)
	//{{AFX_MSG_MAP(CGradeDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGradeDlg message handlers
