#if !defined(AFX_FFT_FILTER_H__C500C028_760D_47BF_9521_A1DAA3C3D392__INCLUDED_)
#define AFX_FFT_FILTER_H__C500C028_760D_47BF_9521_A1DAA3C3D392__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FFT_FILTER.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FFT_FILTER dialog

class FFT_FILTER : public CDialog
{
// Construction
public:
	FFT_FILTER(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FFT_FILTER)
	enum { IDD = IDD_FFT_FILTER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FFT_FILTER)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FFT_FILTER)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FFT_FILTER_H__C500C028_760D_47BF_9521_A1DAA3C3D392__INCLUDED_)
