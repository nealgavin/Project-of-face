// CourseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "imagestitch.h"
#include "CourseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCourseDlg dialog


CCourseDlg::CCourseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCourseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCourseDlg)
	m_courseid = _T("");
	m_coursename = _T("");
	m_teacherid = _T("");
	//}}AFX_DATA_INIT
}


void CCourseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCourseDlg)
	DDX_Text(pDX, IDC_EDIT1, m_courseid);
	DDX_Text(pDX, IDC_EDIT2, m_coursename);
	DDX_Text(pDX, IDC_EDIT3, m_teacherid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCourseDlg, CDialog)
	//{{AFX_MSG_MAP(CCourseDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCourseDlg message handlers
