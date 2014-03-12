#if !defined(AFX_GRADEDLG_H__6B083E64_CBFE_4762_9123_0187F0146237__INCLUDED_)
#define AFX_GRADEDLG_H__6B083E64_CBFE_4762_9123_0187F0146237__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GradeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGradeDlg dialog

class CGradeDlg : public CDialog
{
// Construction
public:
	CGradeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGradeDlg)
	enum { IDD = IDD_GRADE };
	CString	m_gradeid;
	CString	m_classid;
	CString	m_classname;
	CString	m_gradename;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGradeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGradeDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRADEDLG_H__6B083E64_CBFE_4762_9123_0187F0146237__INCLUDED_)
