// MJ095.h : main header file for the MJ095 application
//

#if !defined(AFX_MJ095_H__907A36B8_1BE2_41AA_9DF1_21A44AD51D59__INCLUDED_)
#define AFX_MJ095_H__907A36B8_1BE2_41AA_9DF1_21A44AD51D59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMJ095App:
// See MJ095.cpp for the implementation of this class
//

class CMJ095App : public CWinApp
{
public:
	CMJ095App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMJ095App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMJ095App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MJ095_H__907A36B8_1BE2_41AA_9DF1_21A44AD51D59__INCLUDED_)
