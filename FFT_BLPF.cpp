// FFT_BLPF.cpp : implementation file
//

#include "stdafx.h"
#include "mj095.h"
#include "FFT_BLPF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FFT_BLPF dialog


FFT_BLPF::FFT_BLPF(CWnd* pParent /*=NULL*/)
	: CDialog(FFT_BLPF::IDD, pParent)
{
	//{{AFX_DATA_INIT(FFT_BLPF)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void FFT_BLPF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FFT_BLPF)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FFT_BLPF, CDialog)
	//{{AFX_MSG_MAP(FFT_BLPF)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FFT_BLPF message handlers
void FFT_BLPFF(int D);
void FFT_BLPF::OnOK() 
{
	// TODO: Add extra validation here
	int  edit1;
	edit1 = GetDlgItemInt(IDC_EDIT1);
	FFT_BLPFF(edit1);
	CDialog::OnOK();
}
