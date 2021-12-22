// MJ095Doc.cpp : implementation of the CMJ095Doc class
//

#include "stdafx.h"
#include "MJ095.h"

#include "MJ095Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMJ095Doc

IMPLEMENT_DYNCREATE(CMJ095Doc, CDocument)

BEGIN_MESSAGE_MAP(CMJ095Doc, CDocument)
	//{{AFX_MSG_MAP(CMJ095Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMJ095Doc construction/destruction

CMJ095Doc::CMJ095Doc()
{
	// TODO: add one-time construction code here

}

CMJ095Doc::~CMJ095Doc()
{
}

BOOL CMJ095Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMJ095Doc serialization

void CMJ095Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMJ095Doc diagnostics

#ifdef _DEBUG
void CMJ095Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMJ095Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMJ095Doc commands
BOOL loadBmpFile(char* BmpFileName);
BOOL CMJ095Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	loadBmpFile((char*)lpszPathName);
	return TRUE;
}
