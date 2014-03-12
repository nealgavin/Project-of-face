// imagestitchDoc.h : interface of the CImagestitchDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGESTITCHDOC_H__6726D4B0_BFCA_4F3C_9201_2E74B13D4BB4__INCLUDED_)
#define AFX_IMAGESTITCHDOC_H__6726D4B0_BFCA_4F3C_9201_2E74B13D4BB4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CImagestitchDoc : public CDocument
{
protected: // create from serialization only
	CImagestitchDoc();
	DECLARE_DYNCREATE(CImagestitchDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImagestitchDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImagestitchDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImagestitchDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGESTITCHDOC_H__6726D4B0_BFCA_4F3C_9201_2E74B13D4BB4__INCLUDED_)
