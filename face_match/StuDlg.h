#if !defined(AFX_STUDLG_H__A9926652_5DF7_405A_9CFC_C81C1C580D24__INCLUDED_)
#define AFX_STUDLG_H__A9926652_5DF7_405A_9CFC_C81C1C580D24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StuDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStuDlg dialog

class CStuDlg : public CDialog
{
// Construction
public:
	CStuDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStuDlg)
	enum { IDD = IDD_STABLE };
	CString	m_stuid;
	CString	m_stuname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStuDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STUDLG_H__A9926652_5DF7_405A_9CFC_C81C1C580D24__INCLUDED_)
