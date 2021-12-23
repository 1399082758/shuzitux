#if !defined(AFX_LINEDIALOG_H__3E6F913B_5988_4D25_B7D5_46B1F47805D9__INCLUDED_)
#define AFX_LINEDIALOG_H__3E6F913B_5988_4D25_B7D5_46B1F47805D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LINEDIALOG.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LINEDIALOG dialog

class LINEDIALOG : public CDialog
{
// Construction
public:
	LINEDIALOG(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(LINEDIALOG)
	enum { IDD = IDD_LINDIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LINEDIALOG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LINEDIALOG)
	afx_msg void OnLine();
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINEDIALOG_H__3E6F913B_5988_4D25_B7D5_46B1F47805D9__INCLUDED_)
