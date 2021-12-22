// MJ095Doc.h : interface of the CMJ095Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MJ095DOC_H__ABC28256_8092_457A_A91A_F4D02538461C__INCLUDED_)
#define AFX_MJ095DOC_H__ABC28256_8092_457A_A91A_F4D02538461C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMJ095Doc : public CDocument
{
protected: // create from serialization only
	CMJ095Doc();
	DECLARE_DYNCREATE(CMJ095Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMJ095Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMJ095Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMJ095Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MJ095DOC_H__ABC28256_8092_457A_A91A_F4D02538461C__INCLUDED_)
