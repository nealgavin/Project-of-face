// imagematch.cpp : implementation file
//

#include "stdafx.h"
#include "imagestitch.h"
#include "imagematch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// imagematch dialog


imagematch::imagematch(CWnd* pParent /*=NULL*/)
	: CDialog(imagematch::IDD, pParent)
{
	//{{AFX_DATA_INIT(imagematch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void imagematch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(imagematch)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(imagematch, CDialog)
	//{{AFX_MSG_MAP(imagematch)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// imagematch message handlers
