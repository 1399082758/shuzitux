#if !defined(AFX_IDD_HISTOGRAM_H__1F4FDAC5_4931_4608_92DF_4A86D000C08E__INCLUDED_)
#define AFX_IDD_HISTOGRAM_H__1F4FDAC5_4931_4608_92DF_4A86D000C08E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IDD_HISTOGRAM.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// IDD_HISTOGRAM dialog

class IDD_HISTOGRAM : public CDialog
{
// Construction
public:
	IDD_HISTOGRAM(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(IDD_HISTOGRAM)
	enum { IDD = IDD_IDD_HISTOGRAM_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(IDD_HISTOGRAM)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(IDD_HISTOGRAM)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDD_HISTOGRAM_H__1F4FDAC5_4931_4608_92DF_4A86D000C08E__INCLUDED_)
