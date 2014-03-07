#if !defined(AFX_MYSQLDLG_H__394B7929_B1CB_485A_A72A_CA55FC6CE3FC__INCLUDED_)
#define AFX_MYSQLDLG_H__394B7929_B1CB_485A_A72A_CA55FC6CE3FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MysqlDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMysqlDlg dialog

class CMysqlDlg : public CDialog
{
// Construction
public:
	CMysqlDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMysqlDlg)
	enum { IDD = IDD_MYSQL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMysqlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMysqlDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSQLDLG_H__394B7929_B1CB_485A_A72A_CA55FC6CE3FC__INCLUDED_)
