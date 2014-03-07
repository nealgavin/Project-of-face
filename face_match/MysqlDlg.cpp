// MysqlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imagestitch.h"
#include "MysqlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMysqlDlg dialog


CMysqlDlg::CMysqlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMysqlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMysqlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMysqlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMysqlDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMysqlDlg, CDialog)
	//{{AFX_MSG_MAP(CMysqlDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMysqlDlg message handlers
