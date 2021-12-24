#if !defined(AFX_FFT_BLPF_H__8A162CB5_E633_4424_8600_2F0A625FDD5A__INCLUDED_)
#define AFX_FFT_BLPF_H__8A162CB5_E633_4424_8600_2F0A625FDD5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FFT_BLPF.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FFT_BLPF dialog

class FFT_BLPF : public CDialog
{
// Construction
public:
	FFT_BLPF(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FFT_BLPF)
	enum { IDD = IDD_FFT_BLPF };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FFT_BLPF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FFT_BLPF)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FFT_BLPF_H__8A162CB5_E633_4424_8600_2F0A625FDD5A__INCLUDED_)
