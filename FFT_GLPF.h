#if !defined(AFX_FFT_GLPF_H__72A8CFE2_5DFA_4DE2_99B2_6D6DDD42D8CF__INCLUDED_)
#define AFX_FFT_GLPF_H__72A8CFE2_5DFA_4DE2_99B2_6D6DDD42D8CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FFT_GLPF.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FFT_GLPF dialog

class FFT_GLPF : public CDialog
{
// Construction
public:
	FFT_GLPF(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FFT_GLPF)
	enum { IDD = IDD_FFT_GLPF };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FFT_GLPF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FFT_GLPF)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FFT_GLPF_H__72A8CFE2_5DFA_4DE2_99B2_6D6DDD42D8CF__INCLUDED_)
