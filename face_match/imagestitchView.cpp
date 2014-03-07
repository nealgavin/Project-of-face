// imagestitchView.cpp : implementation of the CImagestitchView class
//

#include "stdafx.h"
#include "imagestitch.h"

#include "imagestitchDoc.h"
#include "imagestitchView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImagestitchView

IMPLEMENT_DYNCREATE(CImagestitchView, CScrollView)

BEGIN_MESSAGE_MAP(CImagestitchView, CScrollView)
	//{{AFX_MSG_MAP(CImagestitchView)
	ON_COMMAND(ID_feature_match, Onfeaturematch)
	ON_COMMAND(ID_image_match, Onimagematch)
	ON_COMMAND(ID_image_full, Onimagefull)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImagestitchView construction/destruction

CImagestitchView::CImagestitchView()
{
	// TODO: add construction code here

}

CImagestitchView::~CImagestitchView()
{
}

BOOL CImagestitchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImagestitchView drawing

void CImagestitchView::OnDraw(CDC* pDC)
{
	CImagestitchDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CImagestitchView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CImagestitchView printing

BOOL CImagestitchView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImagestitchView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImagestitchView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CImagestitchView diagnostics

#ifdef _DEBUG
void CImagestitchView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImagestitchView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImagestitchDoc* CImagestitchView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImagestitchDoc)));
	return (CImagestitchDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImagestitchView message handlers

void CImagestitchView::Onfeaturematch() 
{
	// TODO: Add your command handler code here
	featurematch dlg;
	dlg.DoModal();
}


void CImagestitchView::Onimagematch() 
{
	// TODO: Add your command handler code here
	stitchimage dlg;
	dlg.DoModal();
}

void CImagestitchView::Onimagefull() 
{
	// TODO: Add your command handler code here
	imagefull dlg;
	dlg.DoModal();
}
