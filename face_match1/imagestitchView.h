// imagestitchView.h : interface of the CImagestitchView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGESTITCHVIEW_H__2012F684_6E70_4B60_A9CE_3EFE2C6A9DD6__INCLUDED_)
#define AFX_IMAGESTITCHVIEW_H__2012F684_6E70_4B60_A9CE_3EFE2C6A9DD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "featurematch.h"
//#include "imagematch.h"
#include "stitchimage.h"
#include "imagefull.h"

class CImagestitchView : public CScrollView
{
protected: // create from serialization only
	CImagestitchView();
	DECLARE_DYNCREATE(CImagestitchView)

// Attributes
public:
	CImagestitchDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImagestitchView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImagestitchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImagestitchView)
	afx_msg void Onfeaturematch();
	afx_msg void Onimagematch();
	afx_msg void Onimagefull();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in imagestitchView.cpp
inline CImagestitchDoc* CImagestitchView::GetDocument()
   { return (CImagestitchDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGESTITCHVIEW_H__2012F684_6E70_4B60_A9CE_3EFE2C6A9DD6__INCLUDED_)
