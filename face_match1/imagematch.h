#if !defined(AFX_IMAGEMATCH_H__595689AB_F9C1_4E0A_AA17_4D18D6A9821C__INCLUDED_)
#define AFX_IMAGEMATCH_H__595689AB_F9C1_4E0A_AA17_4D18D6A9821C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// imagematch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// imagematch dialog

class imagematch : public CDialog
{
// Construction
public:
	imagematch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(imagematch)
	enum { IDD = IDD_imagematch };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(imagematch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(imagematch)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEMATCH_H__595689AB_F9C1_4E0A_AA17_4D18D6A9821C__INCLUDED_)
