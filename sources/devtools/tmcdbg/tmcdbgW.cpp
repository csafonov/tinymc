// tmcdbgW.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"



	#include "tmcdbgW.h"
	#include "SplitWnd.h" 
	#include "tmcdbgWDlg.h"
/*
   Copyright (C) Shmuel Safonov 2009-2012 All rights reserved.
   Any usage of this file must be according to TMC License.
*/
#ifdef HAS_PLOT_DLL
#include "cplot.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTmcdbgWApp

BEGIN_MESSAGE_MAP(CTmcdbgWApp, CWinApp)
	//{{AFX_MSG_MAP(CTmcdbgWApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTmcdbgWApp construction

CTmcdbgWApp::CTmcdbgWApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTmcdbgWApp object

CTmcdbgWApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTmcdbgWApp initialization

BOOL CTmcdbgWApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
//#ifdef _AFXDLL
//	Enable3dControls();			// Call this when using MFC in a shared DLL
//#else
//	Enable3dControlsStatic();	// Call this when linking to MFC statically
//#endif	


	// add doc template
	//CDocTemplate* pDocTemplate;
	//pDocTemplate = new CDocTemplate(IDR_TEXTTYPE,
	//	RUNTIME_CLASS(CPadDoc),
	//	RUNTIME_CLASS(CPadFrame),
	//	RUNTIME_CLASS(CPadView));
	//pDocTemplate->SetServerInfo(
	//	IDR_TEXTTYPE_EMBEDDED, IDR_TEXTTYPE_INPLACE,
	//	RUNTIME_CLASS(CInPlaceFrame));
	//AddDocTemplate(pDocTemplate);


	InitTmc();

	CTmcdbgWDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
		FreeTmc();
	}
//long CloseAll();
#ifdef HAS_PLOT_DLL
	CloseAll();
#endif


	// Since the dialog has been closed, return FALSE so that we exit the
	//  applicat  ion, rather than start the application's message pump.
	return FALSE;
}
