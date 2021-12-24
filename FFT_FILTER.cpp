// FFT_FILTER.cpp : implementation file
//

#include "stdafx.h"
#include "mj095.h"
#include "FFT_FILTER.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FFT_FILTER dialog


FFT_FILTER::FFT_FILTER(CWnd* pParent /*=NULL*/)
	: CDialog(FFT_FILTER::IDD, pParent)
{
	//{{AFX_DATA_INIT(FFT_FILTER)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void FFT_FILTER::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FFT_FILTER)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FFT_FILTER, CDialog)
	//{{AFX_MSG_MAP(FFT_FILTER)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
void FFT_Filter(int D);
/////////////////////////////////////////////////////////////////////////////
// FFT_FILTER message handlers

void FFT_FILTER::OnOK() 
{
	// TODO: Add extra validation here
	int  edit1;
	edit1 = GetDlgItemInt(IDC_EDIT1);
	FFT_Filter(edit1);
	CDialog::OnOK();
}
