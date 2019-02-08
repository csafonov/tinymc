// tmcdbgWDlg.cpp : implementation file
//
/*
   Copyright (C) Shmuel Safonov 2009-2012 All rights reserved.
   Any usage of this file must be according to TMC License.
*/

#include "stdafx.h"

#include <afxcview.h>


	#include "tmcdbgW.h"
	#include "SplitWnd.h" 
	#include "tmcdbgWDlg.h"
#ifdef HAS_PLOT_DLL
#include "cplot.h"
#endif

#include "tmcdebugger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define VERT_SHIFT_PANES 50

//class CTmcMatDoc : public CDocument
//{
//
//
//};


/////////////////////////////////////////////////////////////////////////////
// CTmcdbgWDlg dialog

CTmcdbgWDlg::CTmcdbgWDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTmcdbgWDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTmcdbgWDlg)
	m_Addr = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTmcdbgWDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTmcdbgWDlg)
	DDX_Text(pDX, IDC_EDIT_ADDR, m_Addr);
	DDV_MaxChars(pDX, m_Addr, 100);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTmcdbgWDlg, CDialog)
	//{{AFX_MSG_MAP(CTmcdbgWDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PRINT, OnButtonPrint)
	ON_BN_CLICKED(IDC_BUTTON_PLOT, OnButtonPlot)
	ON_WM_SIZE()
	ON_WM_CANCELMODE()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, OnButtonRefresh)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CTmcdbgWDlg::OnBnClickedButtonImport)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTmcdbgWDlg message handlers

BOOL CTmcdbgWDlg::OnInitDialog()
{
	wchar_t tTitle[] = {0x6708,0};

	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	this->SetWindowTextW(tTitle);

	CRect wrect;
	GetClientRect(&wrect);
	m_wndSplitter.InitSplitter(this,wrect.right/6,wrect.right/8,wrect.right/2,
		wrect.right,wrect.bottom,VERT_SHIFT_PANES);

	OnBnClickedButtonImport();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTmcdbgWDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTmcdbgWDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



//HTREEITEM VarRoot;




void CTmcdbgWDlg::OnButtonPrint() 
{// add matrix to TreeView

	UpdateData(TRUE);
	if (ConnectTmc()<0)
		return;
	
	m_wndSplitter.OnAddAddr((LPCTSTR)m_Addr);
}

BOOL CTmcdbgWDlg::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	m_wndSplitter.ClearListMat();
	GetMyTreeCtrl()->DestroyWindow();
	//try
	//{
	return CDialog::DestroyWindow();
	//}
	//catch (...)
	//{
	//return FALSE;
	//}
}



//const double xData[]={1,2,3,4,5};
//const double yData[]={1,4,9,16,4};
long f=0;

void CTmcdbgWDlg::OnButtonPlot() 
{
	// TODO: Add your control notification handler code here
#ifdef HAS_PLOT_DLL
	HTREEITEM ti;
	LPARAM x;
tmsMatrix *m ;
double *times;

	ti = GetMyTreeCtrl()->GetSelectedItem();

	//ti = ((CTreeCtrl*)GetDlgItem(IDC_TREEMAT))->HitTest(NULL);

	//NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	//ti  = pNMTreeView->itemNew.hItem;
	if (ti != NULL)
	{
		x = (LPARAM)GetItemMatrix(ti);
		if (x != NULL)
		{
			m = (tmsMatrix *)(void*)x;
			if (_tmcGetType(m) == TYPE_MATRIX)
			{
				times = (double*)malloc(sizeof(double) * _tmcNumElem(m));
				for (long k=0;k<_tmcNumElem(m);k++)
				{
					times[k]=k+1;
				}
				Plot(times , m->value.complx.rData , _tmcNumElem(m) , RGB(255,0,0) ,"M" );
				SetCurrFigure(++f);
				if (_tmcHasIm(m))
				{
					Plot(times , m->value.complx.iData , _tmcNumElem(m) , RGB(0,255,0) ,"M");
					SetCurrFigure(++f);
				}
				free(times);
			}
			//	long SetCurrFigure(long fig);

		}
	}
#endif
}
int hoho;
BOOL CTmcdbgWDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
		if ((int)wParam== this->m_wndSplitter.eID )
		{
			hoho = 1;


		}
	return CDialog::OnNotify(wParam, lParam, pResult);
}

void CTmcdbgWDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	RECT wrect;
		GetClientRect(&wrect);
		CRect rect(0,VERT_SHIFT_PANES,wrect.right,wrect.bottom);
		if (::IsWindow(m_wndSplitter))
		m_wndSplitter.MoveWindow(&rect);



}

void CTmcdbgWDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}



void CTmcdbgWDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	m_wndSplitter.ClearListMat();
	GetMyEditCtrl()->SetWindowText(L"");

}

void CTmcdbgWDlg::OnButtonRefresh() 
{
	// TODO: Add your control notification handler code here
// 1. must remember selection

	m_wndSplitter.OnRefresh();
}









void CTmcdbgWDlg::OnBnClickedButtonImport()
{
//	LPCTSTR wstr;

	m_wndSplitter.GetCallStack();
	int sel =GetFncListCtrl()->GetSelectionMark();
	m_wndSplitter.OnSelectFnc(sel);

	//CString w_str = GetMyFncListCtrl()->GetItemText(sel,0);
	//wstr = (LPCTSTR)w_str;
//
//
//	GetLocalVars4Fnc(wstr); 
}


void CTmcdbgWDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	m_wndSplitter.ClearFncListMat();
	m_wndSplitter.ClearAllListMat();
	m_wndSplitter.ClearListMat();

	CDialog::OnClose();
}
