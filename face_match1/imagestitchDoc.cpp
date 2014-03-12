// imagestitchDoc.cpp : implementation of the CImagestitchDoc class
//

#include "stdafx.h"
#include "imagestitch.h"

#include "imagestitchDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImagestitchDoc

IMPLEMENT_DYNCREATE(CImagestitchDoc, CDocument)

BEGIN_MESSAGE_MAP(CImagestitchDoc, CDocument)
	//{{AFX_MSG_MAP(CImagestitchDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImagestitchDoc construction/destruction

CImagestitchDoc::CImagestitchDoc()
{
	// TODO: add one-time construction code here

}

CImagestitchDoc::~CImagestitchDoc()
{
}

BOOL CImagestitchDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CImagestitchDoc serialization

void CImagestitchDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CImagestitchDoc diagnostics

#ifdef _DEBUG
void CImagestitchDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImagestitchDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImagestitchDoc commands
