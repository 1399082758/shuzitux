// MJ095View.h : interface of the CMJ095View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MJ095VIEW_H__A66E8D5E_28DD_40CA_BC2F_4FCA37B7E68A__INCLUDED_)
#define AFX_MJ095VIEW_H__A66E8D5E_28DD_40CA_BC2F_4FCA37B7E68A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMJ095View : public CScrollView
{
protected: // create from serialization only
	CMJ095View();
	DECLARE_DYNCREATE(CMJ095View)

// Attributes
public:
	CMJ095Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMJ095View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMJ095View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMJ095View)
	afx_msg void OnGray();
	afx_msg void OnUpdateGray(CCmdUI* pCmdUI);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHistogram();
	afx_msg void OnUpdateHistogram(CCmdUI* pCmdUI);
	afx_msg void OnLine();
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnEqualization();
	afx_msg void OnUpdateEqualization(CCmdUI* pCmdUI);
	afx_msg void OnFourier();
	afx_msg void OnUpdateFourier(CCmdUI* pCmdUI);
	afx_msg void OnIfourier();
	afx_msg void OnUpdateIfourier(CCmdUI* pCmdUI);
	afx_msg void OnIfastfourier();
	afx_msg void OnUpdateIfastfourier(CCmdUI* pCmdUI);
	afx_msg void OnFastfourier();
	afx_msg void OnUpdateFastfourier(CCmdUI* pCmdUI);
	afx_msg void OnAvg();
	afx_msg void OnUpdateAvg(CCmdUI* pCmdUI);
	afx_msg void OnRaplas();
	afx_msg void OnUpdateRaplas(CCmdUI* pCmdUI);
	afx_msg void OnMid();
	afx_msg void OnUpdateMid(CCmdUI* pCmdUI);
	afx_msg void OnGrad();
	afx_msg void OnUpdateGrad(CCmdUI* pCmdUI);
	afx_msg void OnFilter();
	afx_msg void OnUpdateFilter(CCmdUI* pCmdUI);
	afx_msg void OnBlpf();
	afx_msg void OnUpdateBlpf(CCmdUI* pCmdUI);
	afx_msg void OnGlpf();
	afx_msg void OnUpdateGlpf(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MJ095View.cpp
inline CMJ095Doc* CMJ095View::GetDocument()
   { return (CMJ095Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MJ095VIEW_H__A66E8D5E_28DD_40CA_BC2F_4FCA37B7E68A__INCLUDED_)
