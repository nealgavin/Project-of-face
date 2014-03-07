// AddDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imagestitch.h"
#include "AddDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddDlg dialog


CAddDlg::CAddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddDlg)
	m_stuid = _T("");
	m_index = _T("");
	//}}AFX_DATA_INIT
}


void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddDlg)
	DDX_Text(pDX, IDC_EDIT1, m_stuid);
	DDX_Text(pDX, IDC_EDIT2, m_index);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddDlg, CDialog)
	//{{AFX_MSG_MAP(CAddDlg)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddDlg message handlers

void CAddDlg::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
