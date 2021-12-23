// MJ095View.cpp : implementation of the CMJ095View class
//

#include "stdafx.h"
#include "MJ095.h"

#include "MJ095Doc.h"
#include "MJ095View.h"
#include "IDD_HISTOGRAM.h"
#include "LINEDIALOG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMJ095View

IMPLEMENT_DYNCREATE(CMJ095View, CScrollView)

BEGIN_MESSAGE_MAP(CMJ095View, CScrollView)
	//{{AFX_MSG_MAP(CMJ095View)
	ON_COMMAND(ID_GRAY, OnGray)
	ON_UPDATE_COMMAND_UI(ID_GRAY, OnUpdateGray)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_Histogram, OnHistogram)
	ON_UPDATE_COMMAND_UI(ID_Histogram, OnUpdateHistogram)
	ON_COMMAND(ID_LINE, OnLine)
	ON_UPDATE_COMMAND_UI(ID_LINE, OnUpdateLine)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMJ095View construction/destruction

CMJ095View::CMJ095View()
{
	// TODO: add construction code here

}

CMJ095View::~CMJ095View()
{
}

BOOL CMJ095View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMJ095View drawing

extern BITMAPINFO* lpBitsInfo;

void CMJ095View::OnDraw(CDC* pDC)
{
	CMJ095Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (NULL == lpBitsInfo)
		return;
	LPVOID lpBits = (LPVOID)&lpBitsInfo->bmiColors[lpBitsInfo->bmiHeader.biClrUsed];

	StretchDIBits( 
	pDC->GetSafeHdc(),
	0, 0, lpBitsInfo->bmiHeader.biWidth,lpBitsInfo->bmiHeader.biHeight,
	0, 0, lpBitsInfo->bmiHeader.biWidth,lpBitsInfo->bmiHeader.biHeight,
	lpBits, // bitmap bits 
	lpBitsInfo, // bitmap data 
	DIB_RGB_COLORS, // usage options 
	SRCCOPY // raster operation code 
);

}

void CMJ095View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CMJ095View printing

BOOL CMJ095View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMJ095View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMJ095View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMJ095View diagnostics

#ifdef _DEBUG
void CMJ095View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMJ095View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMJ095Doc* CMJ095View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMJ095Doc)));
	return (CMJ095Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMJ095View message handlers
void gray();

void CMJ095View::OnGray() 
{
	// TODO: Add your command handler code here
	gray();
	Invalidate();
}

void CMJ095View::OnUpdateGray(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo != NULL && 24 == lpBitsInfo->bmiHeader.biBitCount);
}

void pixel(int i,int j, char* rgb);
void CMJ095View::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	char xy[100];
	memset(xy,0,100);
	sprintf(xy,"x:%d y:%d  ",point.x,point.y);

	//记录颜色值
	char rgb[100];
	memset(rgb,0,100);
	pixel(point.y,point.x,rgb);

	//坐标与颜色合并
	strcat(xy,rgb);

	//在状态栏显示
	((CFrameWnd*)GetParent())->SetMessageText(xy);

	CScrollView::OnMouseMove(nFlags, point);
}

	

void CMJ095View::OnHistogram() 
{
	// TODO: Add your command handler code here
	IDD_HISTOGRAM dlg;
	dlg.DoModal();
}

void CMJ095View::OnUpdateHistogram(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo!=NULL && 2 < lpBitsInfo->bmiHeader.biBitCount);
}
void linear(int a,int b);

void CMJ095View::OnLine() 
{
	// TODO: Add your command handler code here
	LINEDIALOG dia;
	dia.DoModal();
	Invalidate();
}

void CMJ095View::OnUpdateLine(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(lpBitsInfo!=NULL && 2 < lpBitsInfo->bmiHeader.biBitCount);
}
