// FFT_GLPF.cpp : implementation file
//

#include "stdafx.h"
#include "mj095.h"
#include "FFT_GLPF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FFT_GLPF dialog


FFT_GLPF::FFT_GLPF(CWnd* pParent /*=NULL*/)
	: CDialog(FFT_GLPF::IDD, pParent)
{
	//{{AFX_DATA_INIT(FFT_GLPF)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void FFT_GLPF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FFT_GLPF)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FFT_GLPF, CDialog)
	//{{AFX_MSG_MAP(FFT_GLPF)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FFT_GLPF message handlers
void FFT_GLPFF(int D);
void FFT_GLPF::OnOK() 
{
	// TODO: Add extra validation here
	int  edit1;
	edit1 = GetDlgItemInt(IDC_EDIT1);
	FFT_GLPFF(edit1);
	CDialog::OnOK();
}
