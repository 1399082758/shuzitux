// LINEDIALOG.cpp : implementation file
//

#include "stdafx.h"
#include "mj095.h"
#include "LINEDIALOG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LINEDIALOG dialog


LINEDIALOG::LINEDIALOG(CWnd* pParent /*=NULL*/)
	: CDialog(LINEDIALOG::IDD, pParent)
{
	//{{AFX_DATA_INIT(LINEDIALOG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void LINEDIALOG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LINEDIALOG)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LINEDIALOG, CDialog)
	//{{AFX_MSG_MAP(LINEDIALOG)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LINEDIALOG message handlers
void linear(int a,int b);

void LINEDIALOG::OnOK() 
{
	// TODO: Add extra validation here
	int  edit1,edit2;
	edit1 = GetDlgItemInt(IDC_EDIT2);
	edit2 = GetDlgItemInt(IDC_EDIT1);
	linear(edit1,edit2);
	CDialog::OnOK();
}
