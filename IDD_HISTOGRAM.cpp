// IDD_HISTOGRAM.cpp : implementation file
//

#include "stdafx.h"
#include "mj095.h"
#include "IDD_HISTOGRAM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// IDD_HISTOGRAM dialog


IDD_HISTOGRAM::IDD_HISTOGRAM(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_HISTOGRAM::IDD, pParent)
{
	//{{AFX_DATA_INIT(IDD_HISTOGRAM)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void IDD_HISTOGRAM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(IDD_HISTOGRAM)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(IDD_HISTOGRAM, CDialog)
	//{{AFX_MSG_MAP(IDD_HISTOGRAM)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// IDD_HISTOGRAM message handlers

extern DWORD H[256];
extern DWORD H_R[256];
extern DWORD H_G[256];
extern DWORD H_B[256];
void Histogram();
BOOL IDD_HISTOGRAM::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	Histogram();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
bool if_gray();
void IDD_HISTOGRAM::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	dc.Rectangle(20,20,277,221);//lefttop,rightdown  [H200   W256]   上左
	if(!if_gray())
	{
	dc.Rectangle(300,20,557,221);//lefttop,rightdown  [H200   W256]   上右
	dc.Rectangle(20,250,277,451);//lefttop,rightdown  [H200   W256]   下左
	dc.Rectangle(300,250,557,451);//lefttop,rightdown  [H200   W256]   下右}
	}
	int i;
	DWORD max=0;
	for(i=0;i<256;i++)    //虽然各个颜色分量最大值可能不一样，但是为了统一化便于比较，将标准化的最大值设为各通道的最大值
	{
		if(H[i]>max)
			max=H[i];
		if(H_R[i]>max)
			max=H_R[i];
		if(H_G[i]>max)
			max=H_G[i];
		if(H_B[i]>max)
			max=H_B[i];
	}

	CPen aPen[4]; // 4 种颜色笔
	CPen* poldPen;
	aPen[0].CreatePen(PS_SOLID ,1,COLORREF(0x000000));
	aPen[1].CreatePen(PS_SOLID ,1,COLORREF(0xff0000));
	aPen[2].CreatePen(PS_SOLID ,1,COLORREF(0x00ff00));
	aPen[3].CreatePen(PS_SOLID ,1,COLORREF(0x0000ff));

	poldPen = dc.SelectObject(&aPen[0]); // 选择画笔
	for(i=0;i<256;i++)
	{
		
		dc.MoveTo(i+20,220);   //起点
		dc.LineTo(i+20,220-(int)(H[i]*200/max));  //终点
	}
	poldPen = dc.SelectObject(&aPen[3]); // 选择画笔
	for(i=0;i<256;i++)
	{
		dc.MoveTo(i+300,220);   //起点
		dc.LineTo(i+300,220-(int)(H_R[i]*200/max));  //终点

	}
	poldPen = dc.SelectObject(&aPen[2]); // 选择画笔
	for(i=0;i<256;i++)
	{
		
		dc.MoveTo(i+20,450);   //起点
		dc.LineTo(i+20,450-(int)(H_G[i]*200/max));  //终点
	}
	poldPen = dc.SelectObject(&aPen[1]); // 选择画笔
	for(i=0;i<256;i++)
	{
		dc.MoveTo(i+300,450);   //起点
		dc.LineTo(i+300,450-(int)(H_B[i]*200/max));  //终点
	}
	// Do not call CDialog::OnPaint() for painting messages
}

